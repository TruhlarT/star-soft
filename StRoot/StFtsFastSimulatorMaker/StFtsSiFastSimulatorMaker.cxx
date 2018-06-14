#include "StFtsSiFastSimulatorMaker.h"
#include "St_base/StMessMgr.h"
#include "StEvent/StEvent.h"
#include "StEvent/StRnDHitCollection.h"
#include "StEvent/StRnDHit.h"
#include "tables/St_g2t_fts_hit_Table.h"
#include "TString.h"
#include "TVector3.h"
#include "TGeoManager.h"
#include "TCernLib.h"
#include "crossLine.h"

constexpr float PI     = atan2(0.0, -1.0);
constexpr float SQRT12 = sqrt(12.0);
constexpr float SQRT6  = sqrt(6.0);
const float Sensor_Width = 6.2;//6.0
const float Sensor_Height[] = {2.2, 4.2, 6.2};//
//https://www.star.bnl.gov/protected/heavy/xgn1992/FTS/layout/
const int   NSISK = 3;
const int   NColumn [] = {6, 8, 10};
const int   NRow[] = {12, 12, 14};
const int   NSensorType[3][14] =
{
   {1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, -1, -1},
   {2, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 2, -1, -1},
   {2, 2, 2, 1, 1, 0, 0, 0, 0, 1, 1, 2, 2, 2},
};
const int   NSTRIP       = 1024;//1024
const float Strip_Width  = 60.e-4;//58.e-4
// const float Strip_Width  = 60.5e-4;//58.6
const float stereo =  2 * TMath::Pi() / 8. / 6; //7.5 degree

std::vector<stripPos_t> strip_MapsA[3];//3 sensors [width 2.2, 4.2, 6.2] // 2 type [back]
std::vector<stripPos_t> strip_MapsB[3];//3 sensors [width 2.2, 4.2, 6.2] // 2 type [front]


//================
//
//sTGC

const bool  verbose    = false;
const bool  merge_hits = true;

const float fudge_error = 1.0;

const float OCTANT_WIDTH_PHI        = PI / 4;
const float OCTANT_GLOBAL_PHI_MIN[] = { -PI / 8, PI / 8, 3 * PI / 8, 5 * PI / 8, 7 * PI / 8, 9 * PI / 8, 11 * PI / 8, 13 * PI / 8};
const float OCTANT_GLOBAL_PHI_MAX[] = {       PI / 8, 3 * PI / 8, 5 * PI / 8, 7 * PI / 8, 9 * PI / 8, 11 * PI / 8, 13 * PI / 8, 15 * PI / 8};

float OCTANT_XMIN[] = {  6.0f,  6.0f,  6.0f,  6.0f,  6.0f,  6.0f }; // octant size in each disk...
float OCTANT_XMAX[] = { 42.0f, 42.0f, 66.0f, 66.0f, 66.0f, 66.0f };

const float PAD_WIDTH    = 6.0f;
const float STRIP_WIDTH  = 0.3f;   // must divide nicly into 6cm
const float WIRE_SPACING = 0.15f;  // ditto

// helper functions

int globalToOctant(const float& xglobal,  /* input */
                   const float& yglobal, /* input */
                   const float& stereo,  /* input */
                   float& xoctant,       /* output */
                   float& yoctant        /* output */)
{

   //
   // takes as input a stereo angle, which is subtracted the phibin boundaries
   //

   // Get global phi and map it between the min and max octant boundaries
   float phi_global = TMath::ATan2(yglobal, xglobal);

   while (phi_global <  OCTANT_GLOBAL_PHI_MIN[0] - stereo) phi_global += 2 * PI;
   while (phi_global >= OCTANT_GLOBAL_PHI_MAX[7] - stereo) phi_global -= 2 * PI;

   // Find which octant we are in
   int octant = 0;
   for (octant = 0; octant < 7; octant++)
   {
      float phi_min = OCTANT_GLOBAL_PHI_MIN[octant] - stereo;
      float phi_max = OCTANT_GLOBAL_PHI_MAX[octant] - stereo;
      //      std::cout << octant << " mn=" << phi_min << " mx=" << phi_max << " phig=" << phi_global << std::endl;
      if (phi_global >= phi_min && phi_global < phi_max) break;

   }

   float phi_local = phi_global - octant * OCTANT_WIDTH_PHI + stereo;
   //  float rot_angle = phi_local  - phi_global;
   float rot_angle = - octant * OCTANT_WIDTH_PHI + stereo;

   xoctant = xglobal * TMath::Cos(rot_angle) - yglobal * TMath::Sin(rot_angle);
   yoctant = xglobal * TMath::Sin(rot_angle) + yglobal * TMath::Cos(rot_angle);

   return octant;
}

int octantToGlobal(const float& xoctant,   /* input */
                   const float& yoctant, /* input */
                   const int&    octant, /* input */
                   const float&  stereo, /* input */
                   float& xglobal,       /* output */
                   float& yglobal        /* output */,
                   float* Ematrix = 0    /* optional error matrix in triangular form */
                  )
{

   // Get local phi
   float phi_local = TMath::ATan2(yglobal, xglobal);

   // rotation angle back to global
   float rot_angle = octant * OCTANT_WIDTH_PHI - stereo;

   xglobal = xoctant * TMath::Cos(rot_angle) - yoctant * TMath::Sin(rot_angle);
   yglobal = xoctant * TMath::Sin(rot_angle) + yoctant * TMath::Cos(rot_angle);

   if (Ematrix)
   {
      float Eout[3];
      float R[] = { float(TMath::Cos(rot_angle)), float(-TMath::Sin(rot_angle)),
                    float(TMath::Sin(rot_angle)), float(TMath::Cos(rot_angle))
                  };

      TCL::trasat(R, Ematrix, Eout, 2, 2);

      Ematrix[0] = Eout[0];
      Ematrix[1] = Eout[1];
      Ematrix[2] = Eout[2];

   }


   return octant;

}
//_____________________________________________________________________________________
StFtsSiFastSimulatorMaker::StFtsSiFastSimulatorMaker(const char* name) : StMaker(name),
   fOut(0),
   h2LocalXY(0),
   h2LocalSmearedXY(0),
   h2LocalDeltaXY(0),
   h3LocalDeltaXYDisk(0),
   mStereo(2 * TMath::Pi() / 8 / 6),
   mEnable(
{
   true, true, true, true, true, true, true, true, true, true, true, true
}),
mPointHits(false),
mAmbiguity(true),
mStripWidth(0.3),
mWireSpacing(0.15),
mWindow(3.0),
mStagger(0.0),
mConstEta(false)
{

}
//_____________________________________________________________________________________
int StFtsSiFastSimulatorMaker::Init()
{

   for (int iSensor = 0; iSensor < 3 ; iSensor++)
   {
      cout << iSensor << " th SensorA : " << "#STRIPs " << int(Sensor_Width / Strip_Width) << endl;
      for (int i = 0; i < int(Sensor_Width / Strip_Width); i++)
      {
         //for back strip, they are vertical stand
         //this is the strip position in the local coordinate, (0.0, 0.0) located at the middle of the sensor
         float tmpx1 = Strip_Width * (0.5 + i) - 0.5 * Sensor_Width;
         float tmpx2 = tmpx1;
         float tmpy1 = -0.5 * Sensor_Height[iSensor];
         float tmpy2 = -1 * tmpy1;
         stripPos_t tmp;
         tmp.iPN = 0; // back //vertical
         tmp.x1 = tmpx1;
         tmp.y1 = tmpy1;
         tmp.x2 = tmpx2;
         tmp.y2 = tmpy2;
         strip_MapsA[iSensor].push_back(tmp);
      }
   };

   for (int iSensor = 0; iSensor < 3 ; iSensor++)
   {
      float Extend_Width = Sensor_Width + Sensor_Height[iSensor] * TMath::Tan(stereo);
      cout << iSensor << " th SensorB : " << "#STRIPs " << int(Extend_Width / Strip_Width) << endl;
      for (int i = 0; i < int(Extend_Width / Strip_Width); i++)
      {
         //for front strip, they are rotate 7.5 degree
         //this point stay at the same position as the back strip
         //this is the strip position in the local coordinate, (0.0, 0.0) located at the middle of the sensor
         float tmpx2 = Strip_Width * (0.5 + i) - 0.5 * Sensor_Width;
         float tmpx1 = tmpx2 - Sensor_Height[iSensor] * TMath::Tan(stereo);
         float tmpy2 = 0.5 * Sensor_Height[iSensor];
         float tmpy1 = -1 * tmpy2;

         stripPos_t tmp;
         tmp.iPN = 1; // front// stereo 7.5 degree
         tmp.x1 = tmpx1;
         tmp.y1 = tmpy1;
         tmp.x2 = tmpx2;
         tmp.y2 = tmpy2;
         strip_MapsB[iSensor].push_back(tmp);
      }
   };

   //====================================
   //
   //check each individual strip position
   //
   for (int iSensor = 0; iSensor < 3 ; iSensor++)
   {
      // cout << iSensor << "th sensorA strip size : " << strip_MapsA[iSensor].size() << endl;
      for (int i = 0; i < strip_MapsA[iSensor].size(); i++)
      {
         // cout << i << "th strip : " << strip_MapsA[iSensor][i].iPN << " "
         //      << strip_MapsA[iSensor][i].x1 << " "
         //      << strip_MapsA[iSensor][i].y1 << " "
         //      << strip_MapsA[iSensor][i].x2 << " "
         //      << strip_MapsA[iSensor][i].y2 << " " << endl;
      }

      // cout << iSensor << "th sensorB strip size : " << strip_MapsB[iSensor].size() << endl;
      for (int i = 0; i < strip_MapsB[iSensor].size(); i++)
      {
         // cout << i << "th strip : " << strip_MapsB[iSensor][i].iPN << " "
         //      << strip_MapsB[iSensor][i].x1 << " "
         //      << strip_MapsB[iSensor][i].y1 << " "
         //      << strip_MapsB[iSensor][i].x2 << " "
         //      << strip_MapsB[iSensor][i].y2 << " " << endl;
      }
   }

   //====================================
   //
   //check each individual crossed points position
   //
   if (0) // for check
   {
      for (int iSensor = 0; iSensor < 3 ; iSensor++)
      {

         // cout << iSensor << "th sensorA strip size : " << strip_MapsA[iSensor].size() << endl;
         for (int i = 0; i < strip_MapsA[iSensor].size(); i++)
         {

            Point a, b;
            a.x = strip_MapsA[iSensor][i].x1;
            a.y = strip_MapsA[iSensor][i].y1;
            b.x = strip_MapsA[iSensor][i].x2;
            b.y = strip_MapsA[iSensor][i].y2;

            // cout << iSensor << "th sensorB strip size : " << strip_MapsB[iSensor].size() << endl;
            for (int j = 0; j < strip_MapsB[iSensor].size(); j++)
            {

               Point c, d;
               c.x = strip_MapsB[iSensor][j].x1;
               c.y = strip_MapsB[iSensor][j].y1;
               d.x = strip_MapsB[iSensor][j].x2;
               d.y = strip_MapsB[iSensor][j].y2;

               cout <<  " point a : " << "(" << a.x << " , " << a.y << ")" << " , point b : " << "(" << b.x << " , " << b.y << ")" << endl;
               cout <<  " point c : " << "(" << c.x << " , " << c.y << ")" << " , point d : " << "(" << d.x << " , " << d.y << ")" << endl;

               Point p;
               int cross = ab_cross_cd(a, b, c, d, p);
               if (cross == 1)
               {
                  cout << " CROSSED POINT 1 in the middle, ..." << endl;
                  cout << "p = " << p.x << " , " << p.y << endl;
               }

               if (cross == 0)
               {
                  cout << " CROSSED POINT 0 at the end,  ..." << endl;
                  cout << "p = " << p.x << " , " << p.y << endl;
               }

               if (cross == -1)
               {
                  cout << " CROSSED POINT -1   ..." << endl;
                  cout << "p = " << p.x << " , " << p.y << endl;
               }

               if (cross < 0) continue;

               if (p.x < -0.5 * Sensor_Width || p.x > 0.5 * Sensor_Width || p.y < -0.5 * Sensor_Height[iSensor] || p.y > 0.5 * Sensor_Height[iSensor])
               {
                  cout << "CROSSED POINT out of sensor range" << endl;
                  cout << "cross point : " << p.x << " , " << p.y << endl;
                  continue;
               }

               // cout << "cross point : "<< p.x << " , " << p.y << endl;

            }
         }

      }
   }

   fOut = new TFile("FastSimu.QA.root", "RECREATE");
   AddHist(h2LocalXY = new TH2F("h2LocalXY", ";localX; localY",   800, -4.0, 4.0, 800, -4.0, 4.0));
   AddHist(h2LocalSmearedXY = new TH2F("h2LocalSmearedXY", ";localSmearedX; localSmearedY",   800, -4.0, 4.0, 800, -4.0, 4.0));
   AddHist(h2LocalDeltaXY = new TH2F("h2LocalDeltaXY", ";localDeltaX; localDeltaY",   1000, -0.1, 0.1, 1000, -0.1, 0.1));
   AddHist(h3LocalDeltaXYDisk = new TH3F("h3LocalDeltaXYDisk", ";localDeltaX; localDeltaY; Disk",   1000, -0.1, 0.1, 1000, -0.1, 0.1, 3, 0, 3));

   return StMaker::Init();
}
//_____________________________________________________________________________________
int StFtsSiFastSimulatorMaker::Make()
{


  LOG_INFO << "Make" << endm;

  //  return kStOK;

   // Get the existing StEvent, or add one locally if it doesn't exist.
  StEvent* event = static_cast<StEvent*>(GetInputDS("StEvent"));
   if (!event)
   {
      event = new StEvent;
      AddData(event);
      LOG_DEBUG << "Creating StEvent" << endm; 
   }

   // Get the RnD hit collection, and create if it doesn't already exist
   // StRnDHitCollection* collection =  event->rndHitCollection();
   // if ( 0 == collection ) {
   //   event -> setRnDHitCollection( collection = new StRnDHitCollection() );
   //   LOG_DEBUG << "Creating StRnDHitCollection for FTS" << endm;
   // }

   if (0 == event->rndHitCollection())
   {
      event -> setRnDHitCollection(new StRnDHitCollection());
      LOG_INFO << "Creating StRnDHitCollection for FTS" << endm;
   }

   // Verify the existence of the geometry, and initialize if it is missing
   if (0 == gGeoManager)
   {
      GetDataBase("VmcGeometry");
   }

   //fillStripDisk(event);
   //fillThinGapChambers(event);

   StRnDHitCollection* x1rndCollection = event->rndHitCollection();
   const StSPtrVecRnDHit& x1hits = x1rndCollection->hits();
   cout<<"x1nhits== "<<x1hits.size()<<endl;
   fillStripDisk(event);

   StRnDHitCollection* x2rndCollection = event->rndHitCollection();
   const StSPtrVecRnDHit& x2hits = x2rndCollection->hits();
   cout<<"x2nhits== "<<x2hits.size()<<endl;
   fillThinGapChambers(event);

   StRnDHitCollection* x3rndCollection = event->rndHitCollection();
   const StSPtrVecRnDHit& x3hits = x3rndCollection->hits();
   cout<<"x3nhits== "<<x3hits.size()<<endl;

   return kStOK;
}
//_____________________________________________________________________________________
void StFtsSiFastSimulatorMaker::Clear(const Option_t* opts)
{

}
//_____________________________________________________________________________________
int  StFtsSiFastSimulatorMaker::Finish()
{
   fOut->cd();
   h2LocalXY->Write();
   h2LocalSmearedXY->Write();
   h2LocalDeltaXY->Write();
   h3LocalDeltaXYDisk->Write();
   fOut->Close();
   return kStOK;
}
//_____________________________________________________________________________________
void StFtsSiFastSimulatorMaker::fillStripDisk(StEvent *event)
{

   StRnDHitCollection* collection =  event->rndHitCollection();
   if (0 == collection)
   {
      event -> setRnDHitCollection(collection = new StRnDHitCollection());
      LOG_DEBUG << "Creating StRnDHitCollection for FTS" << endm;
   }

   // Read the g2t table
   St_g2t_fts_hit* hitTable = static_cast<St_g2t_fts_hit*>(GetDataSet("g2t_fts_hit"));
   if (!hitTable)
   {
      LOG_DEBUG << "g2t_fts_hit table is empty" << endm;
      return ;  // Nothing to do
   }  // if

   const int nHits = hitTable->GetNRows();
   const g2t_fts_hit_st* hit = hitTable->GetTable();
   LOG_INFO << "g2t_fts_hit table has " << nHits << " hits" << endm;

   // Set the current path to the struck sensor and obtain transformation matrix
   const char* plane_names[]  = { "FSTA", "FSTB", "FSTC" };
   const char* sensor_names[] = { "FSIA", "FSIB", "FSIC" };

   //
   // Loop over all hits and functional on each of them
   //

   // std::vector<int> DiskA_Maps[2][72]; //diskA// 12 * 6 =  72 sensors
   // std::vector<int> DiskB_Maps[2][96]; //diskA// 12 * 8 =  96 sensors
   // std::vector<int> DiskC_Maps[2][140];//diskA// 14 *10 = 140 sensors
   std::vector<int> Disk_Maps[3][2][140]; //3 disk// 2 type sensors //14 *10 = 140 sensors
   std::vector<int> track_p_Maps[3][2][140]; //
   // std::vector<float> PosZ_Maps[3][140];    //
   std::vector<TVector3> Pos_Maps[3][2][140]; // very very slow....
   std::vector<long long> Key_Maps[3][2][140]; //
   // std::vector<int> Volume_Maps[3][140]; //

   if (1)// this is the real hits loop
   {
      for (int i = 0; i < nHits; i++)
      {

         hit = (g2t_fts_hit_st *)hitTable->At(i);
         // Protect against null hits
         LOG_INFO << " Fill hit = " << hit << endm;
         if (0 == hit) continue;

         // Decode volume ID -- return if not the right subsystem --
         int volume_id = hit -> volume_id;
	 //         LOG_INFO << "volume_id = " << volume_id << endm;

         int t = hit -> track_p;// Pointer to parent track
         // cout << "track_p = " << t <<endl;

         int subsystem = volume_id / 10000;
         if (1 != subsystem)     continue;
         int plane     = (volume_id % 10000) / 1000;
         if (plane < 1 || plane > 3) continue;
         int sensor    = (volume_id %  1000);

         // Set the current path to the struck sensor and obtain transformation matrix
         {
            TString sensor_path = Form("/HALL_1/CAVE_1/FTSM_1/%s_1/%s_%i", plane_names[plane - 1], sensor_names[plane - 1], sensor);
            gGeoManager->cd(sensor_path);
         }
         const TGeoHMatrix* transform = gGeoManager->GetCurrentMatrix();

         float xhit = hit->x[0];
         float yhit = hit->x[1];
         float zhit = hit->x[2];
         double xlocal[] = { hit->x[0], hit->x[1], hit->x[2] }; // good only to single precision
         double xglobal[] = { 0, 0, 0 };

         transform->LocalToMaster(xlocal, xglobal);

         h2LocalXY -> Fill(hit->x[0], hit->x[1]);

         // Print out the volume id, sensor, plane and local / global coordinates

         LOG_INFO << Form("[%i %i %i]: (%f, %f, %f) (%f, %f, %f)",
                          volume_id, sensor, plane, xlocal[0], xlocal[1], xlocal[2], xglobal[0], xglobal[1], xglobal[2])
                  << endm;

         //
         // Find corresponding Row/Column/SensorType
         //

         int row  = (sensor - 1) / NColumn[plane - 1] + 1; //-1 for index// start from 1
         int column = (sensor - 1) % NColumn[plane - 1] + 1; //start from 1
         cout << " Plane :" << plane
              << " , Row : " << row  << " , NRow[plane-1] : " << NRow[plane - 1]
              << " , Column : " << column << " , NColumn[plane-1] : " << NColumn[plane - 1]
              << " , NSensorType[plane-1][row-1] : " << NSensorType[plane - 1][row - 1]
              << endl;

         if (row > NRow[plane - 1])
         {
            cout << "ERROR : Row is Wrong ... " << ", row : " << row << "  > NRow[" << plane - 1 << "] : " << NRow[plane - 1]  << endl;
            continue;
         }
         if (column > NColumn[plane - 1])
         {
            cout << "ERROR : Column is Wrong ..." << ", column : " << column << " >  NColumn[" << plane - 1 << "] : " << NColumn[plane - 1] << endl;
            continue;
         }
         int sensortype = NSensorType[plane - 1][row - 1];
         if (sensortype < 0)
         {
            cout << "ERROR : Senso Type is Wrong ..." << "sensortype : " << sensortype << " , NSensorType[" << plane - 1 << "][" << row - 1 << "] : " << NSensorType[plane - 1][row - 1] << endl;
            continue;
         }

         //
         // BEGIN Fast Simulation Here
         //

         //
         // Find the strips positions // index
         //

         //for back strip, they are vertical stand
         int Index_A = -1;
         // for(int j = 0; j< strip_MapsA[sensortype].size(); j++)
         int tmpJ = (xhit + 0.5 * Sensor_Width) / Strip_Width - 10;//enlarge the search range
         for (int j = tmpJ ; j < strip_MapsA[sensortype].size(); j++)
         {
            if (xhit > strip_MapsA[sensortype][j].x1 && xhit < strip_MapsA[sensortype][j + 1].x1)
            {
               if (xhit < 0.5 * (strip_MapsA[sensortype][j].x1 + strip_MapsA[sensortype][j + 1].x1))
               {
                  Index_A = j;  // cout << "hit on "<< j << "th Astrip "<< endl;
               }
               else
               {
                  Index_A = j + 1; // cout << "hit on "<< j+1 << "th Astrip "<< endl;
               }
               break;
            }
            // cout << " j = "<< j << endl;
         }
         if(Index_A == -1) Index_A = strip_MapsA[sensortype].size() -1;

         //for front strip, they are rotate 7.5 degree
         int Index_B = -1;
         // for(int j = 0; j< strip_MapsB[sensortype].size(); j++)
         float xhitsmall = xhit - (yhit + 0.5 * Sensor_Height[sensortype]) * TMath::Tan(stereo);
         float xhitlarge = xhit + (0.5 * Sensor_Height[sensortype] - yhit) * TMath::Tan(stereo);
         int tmpK = (xhitlarge + 0.5 * Sensor_Width) / Strip_Width - 10; //enlarge the search range
         for (int j = tmpK ; j < strip_MapsB[sensortype].size(); j++)
         {
            if (xhitlarge > strip_MapsB[sensortype][j].x2 && xhitlarge < strip_MapsB[sensortype][j + 1].x2)
            {
               if (xhitlarge < 0.5 * (strip_MapsB[sensortype][j].x2 + strip_MapsB[sensortype][j + 1].x2))
               {
                  Index_B = j; // cout << "hit on "<< j << "th Bstrip "<< endl;
               }
               else
               {
                  Index_B = j + 1; // cout << "hit on "<< j+1 << "th Bstrip "<< endl;
               }
               break;
            }
            // cout << " j = "<< j << endl;
         }
         if(Index_B == -1) Index_B = strip_MapsB[sensortype].size() -1;

         //for front strip, they are rotate 7.5 degree
         int Index_C = -1;
         int tmpJJ = (xhitsmall + 0.5 * Sensor_Width + Sensor_Height[sensortype] * TMath::Tan(stereo)) / Strip_Width - 10; //enlarge the search range
         for (int j = tmpJJ ; j < strip_MapsB[sensortype].size(); j++)
         {
            if (xhitsmall > strip_MapsB[sensortype][j].x1 && xhitsmall < strip_MapsB[sensortype][j + 1].x1)
            {
               if (xhitsmall < 0.5 * (strip_MapsB[sensortype][j].x1 + strip_MapsB[sensortype][j + 1].x1))
               {
                  Index_C = j; // cout << "hit on "<< j << "th Bstrip "<< endl;
               }
               else
               {
                  Index_C = j + 1; // cout << "hit on "<< j+1 << "th Bstrip "<< endl;
               }
               break;
            }
            // cout << " j = "<< j << endl;
         }
         if(Index_C == -1) Index_C = strip_MapsB[sensortype].size() -1;

         if (Index_B != Index_C)
         {
            cout << "ERROR:  Index for front strip are not synchronize ..."  << Index_B << " != " << Index_C << endl;
            return;
         }

         //=======
         //
         // some of the stripB are half strips. those are combined for read-out. The first Index and the first ectended index are combined.
         //
         int Index_D = -1;
         int tmpIndex = int(Sensor_Height[sensortype] * TMath::Tan(stereo) / Strip_Width);
         int IndexN = int(Sensor_Width / Strip_Width);
         if (Index_B <  tmpIndex)
         {
            Index_D = Index_B + IndexN;
         }
         else if (Index_B >= IndexN)
         {
            Index_D = Index_B - IndexN;
         }

         if (((Index_D != -1) && (Index_D < 0)) || (Index_D > int(strip_MapsB[sensortype].size())))
         {
            // cout << "Index_D : " << Index_D << " , sensortype : " << sensortype << " , strip_MapsB[sensortype].size() = " << strip_MapsB[sensortype].size() << endl;
            cout << "ERROR:  Index for front strip Index_D are not synchronize with Index_B ..."  << Index_D << " != " << Index_B << endl;
         }

         //==============

         long long key_stripA =
            plane   /* 1-3  */           +
            sensor  /* 1-140  */ * 10    +
            Index_A /* 1024 */   * 10000 ;

         long long key_stripB =
            plane   /* 1-3  */           +
            sensor  /* 1-140  */ * 10    +
            Index_B /* 1024 */   * 10000 ;

         long long key_stripD = -1;
         if (Index_D > -1 && Index_D < strip_MapsB[sensortype].size())
         {
            key_stripD =
               plane   /* 1-3  */           +
               sensor  /* 1-140  */ * 10    +
               Index_D /* 1024 */   * 10000 ;
         }

         Disk_Maps[plane - 1][0][sensor-1].push_back(Index_A);
         Disk_Maps[plane - 1][1][sensor-1].push_back(Index_B);
         track_p_Maps[plane - 1][0][sensor-1].push_back(t);
         track_p_Maps[plane - 1][1][sensor-1].push_back(t);
         // PosZ_Maps[plane-1][sensor-1].push_back(zhit);
         TVector3 posVect(xhit, yhit, zhit);
         Pos_Maps[plane - 1][0][sensor-1].push_back(posVect);
         Pos_Maps[plane - 1][1][sensor-1].push_back(posVect);
         Key_Maps[plane - 1][0][sensor-1].push_back(key_stripA);
         Key_Maps[plane - 1][1][sensor-1].push_back(key_stripB);
         // Volume_Maps[plane-1][sensor-1].push_back(volume_id);

         if (Index_D > -1 && Index_D < strip_MapsB[sensortype].size())
         {
            Disk_Maps[plane - 1][1][sensor-1].push_back(Index_D);
            track_p_Maps[plane - 1][1][sensor-1].push_back(-1);//sign as fake hit here
            Pos_Maps[plane - 1][1][sensor-1].push_back(posVect);
            Key_Maps[plane - 1][1][sensor-1].push_back(key_stripD);
         }

      }
   }

   if (0) //manuly input hits// for testing
   {
      // //normal test
      // const int N = 1;
      // int T[N] = {1 };
      // int Plane[N] = {1 };
      // int Sensor[N] = {1};
      // float Xhit[N] = {0.1};
      // float Yhit[N] = {0.1};
      // float Zhit[N] = {0.};

      // //test half strips
      // const int N = 1;
      // int T[N] = {1 };
      // int Plane[N] = {1 };
      // int Sensor[N] = {1};
      // float Xhit[N] = {3.08};
      // float Yhit[N] = {-0.5};
      // float Zhit[N] = {0.};

      // //normal test with two hits
      // const int N = 2;
      // int T[N] = {1 , 2 };
      // int Plane[N] = {1, 1};
      // int Sensor[N] = {1, 1};
      // float Xhit[N] = {0.1, 0.11};
      // float Yhit[N] = {0.1, 0.11};
      // float Zhit[N] = {0., 0.};

      // //test half strips
      const int N = 3;
      int T[N] = {1 , 2, 3 };
      int Plane[N] = {1, 1, 1};
      int Sensor[N] = {1, 1, 1};
      float Xhit[N] = {3.08, 0.11, -3.0};
      float Yhit[N] = { -0.5, 0.11, 0.8};
      float Zhit[N] = {0., 0.};

      for (int i = 0; i < N; i++)
      {

         int t = T[i];

         int subsystem = 1;
         if (1 != subsystem)     continue;
         int plane     = Plane[i];
         if (plane < 1 || plane > 3) continue;
         int sensor    =  Sensor[i];

         // Set the current path to the struck sensor and obtain transformation matrix
         {
            TString sensor_path = Form("/HALL_1/CAVE_1/FTSM_1/%s_1/%s_%i", plane_names[plane - 1], sensor_names[plane - 1], sensor);
            gGeoManager->cd(sensor_path);
         }
         const TGeoHMatrix* transform = gGeoManager->GetCurrentMatrix();

         float xhit = Xhit[i];
         float yhit = Yhit[i];
         float zhit = Zhit[i];
         double xlocal[] = { xhit, yhit, zhit}; // good only to single precision
         double xglobal[] = { 0, 0, 0 };

         transform->LocalToMaster(xlocal, xglobal);

         h2LocalXY -> Fill(xhit, yhit);

         // Print out the volume id, sensor, plane and local / global coordinates

         LOG_INFO << Form("[%i %i]: (%f, %f, %f) (%f, %f, %f)",
                          sensor, plane, xlocal[0], xlocal[1], xlocal[2], xglobal[0], xglobal[1], xglobal[2])
                  << endm;

         //
         // Find corresponding Row/Column/SensorType
         //

         int row  = (sensor - 1) / NColumn[plane - 1] + 1; //-1 for index// start from 1
         int column = (sensor - 1) % NColumn[plane - 1] + 1; //start from 1
         cout << " Plane :" << plane
              << " , Row : " << row  << " , NRow[plane-1] : " << NRow[plane - 1]
              << " , Column : " << column << " , NColumn[plane-1] : " << NColumn[plane - 1]
              << " , NSensorType[plane-1][row-1] : " << NSensorType[plane - 1][row - 1]
              << endl;

         if (row > NRow[plane - 1])
         {
            cout << "ERROR : Row is Wrong ... " << ", row : " << row << "  > NRow[" << plane - 1 << "] : " << NRow[plane - 1]  << endl;
            continue;
         }
         if (column > NColumn[plane - 1])
         {
            cout << "ERROR : Column is Wrong ..." << ", column : " << column << " >  NColumn[" << plane - 1 << "] : " << NColumn[plane - 1] << endl;
            continue;
         }
         int sensortype = NSensorType[plane - 1][row - 1];
         if (sensortype < 0)
         {
            cout << "ERROR : Senso Type is Wrong ..." << "sensortype : " << sensortype << " , NSensorType[" << plane - 1 << "][" << row - 1 << "] : " << NSensorType[plane - 1][row - 1] << endl;
            continue;
         }

         //
         // BEGIN Fast Simulation Here
         //

         //
         // Find the strips positions // index
         //

         //for back strip, they are vertical stand
         int Index_A;
         // for(int j = 0; j< strip_MapsA[sensortype].size(); j++)
         int tmpJ = (xhit + 0.5 * Sensor_Width) / Strip_Width - 10;//enlarge the search range
         for (int j = tmpJ ; j < strip_MapsA[sensortype].size(); j++)
         {
            if (xhit > strip_MapsA[sensortype][j].x1 && xhit < strip_MapsA[sensortype][j + 1].x1)
            {
               if (xhit < 0.5 * (strip_MapsA[sensortype][j].x1 + strip_MapsA[sensortype][j + 1].x1))
               {
                  Index_A = j;  // cout << "hit on "<< j << "th Astrip "<< endl;
               }
               else
               {
                  Index_A = j + 1; // cout << "hit on "<< j+1 << "th Astrip "<< endl;
               }
               break;
            }
            // cout << " j = "<< j << endl;
         }

         //for front strip, they are rotate 7.5 degree
         int Index_B;
         // for(int j = 0; j< strip_MapsB[sensortype].size(); j++)
         float xhitsmall = xhit - (yhit + 0.5 * Sensor_Height[sensortype]) * TMath::Tan(stereo);
         float xhitlarge = xhit + (0.5 * Sensor_Height[sensortype] - yhit) * TMath::Tan(stereo);
         int tmpK = (xhitlarge + 0.5 * Sensor_Width) / Strip_Width - 10; //enlarge the search range
         for (int j = tmpK ; j < strip_MapsB[sensortype].size(); j++)
         {
            if (xhitlarge > strip_MapsB[sensortype][j].x2 && xhitlarge < strip_MapsB[sensortype][j + 1].x2)
            {
               if (xhitlarge < 0.5 * (strip_MapsB[sensortype][j].x2 + strip_MapsB[sensortype][j + 1].x2))
               {
                  Index_B = j; // cout << "hit on "<< j << "th Bstrip "<< endl;
               }
               else
               {
                  Index_B = j + 1; // cout << "hit on "<< j+1 << "th Bstrip "<< endl;
               }
               break;
            }
            // cout << " j = "<< j << endl;
         }

         //for front strip, they are rotate 7.5 degree
         int Index_C;
         int tmpJJ = (xhitsmall + 0.5 * Sensor_Width + Sensor_Height[sensortype] * TMath::Tan(stereo)) / Strip_Width - 10; //enlarge the search range
         for (int j = tmpJJ ; j < strip_MapsB[sensortype].size(); j++)
         {
            if (xhitsmall > strip_MapsB[sensortype][j].x1 && xhitsmall < strip_MapsB[sensortype][j + 1].x1)
            {
               if (xhitsmall < 0.5 * (strip_MapsB[sensortype][j].x1 + strip_MapsB[sensortype][j + 1].x1))
               {
                  Index_C = j; // cout << "hit on "<< j << "th Bstrip "<< endl;
               }
               else
               {
                  Index_C = j + 1; // cout << "hit on "<< j+1 << "th Bstrip "<< endl;
               }
               break;
            }
            // cout << " j = "<< j << endl;
         }

         if (Index_B != Index_C)
         {
            cout << "ERROR:  Index for front strip are not synchronize ..."  << Index_B << " != " << Index_C << endl;
            return;
         }

         //=======
         //
         // some of the stripB are half strips. those are combined for read-out. The first Index and the first ectended index are combined.
         //
         int Index_D = -1;
         int tmpIndex = int(Sensor_Height[sensortype] * TMath::Tan(stereo) / Strip_Width);
         int IndexN = int(Sensor_Width / Strip_Width);
         if (Index_B <  tmpIndex)
         {
            Index_D = Index_B + IndexN;
         }
         else if (Index_B >= IndexN)
         {
            Index_D = Index_B - IndexN;
         }

         if (((Index_D != -1) && (Index_D < 0)) || (Index_D > int(strip_MapsB[sensortype].size())))
         {
            // cout << "Index_D : " << Index_D << " , sensortype : " << sensortype << " , strip_MapsB[sensortype].size() = " << strip_MapsB[sensortype].size() << endl;
            cout << "ERROR:  Index for front strip Index_D are not synchronize with Index_B ..."  << Index_D << " != " << Index_B << endl;
         }

         //==============

         long long key_stripA =
            plane   /* 1-3  */           +
            sensor  /* 1-140  */ * 10    +
            Index_A /* 1024 */   * 10000 ;

         long long key_stripB =
            plane   /* 1-3  */           +
            sensor  /* 1-140  */ * 10    +
            Index_B /* 1024 */   * 10000 ;

         long long key_stripD = -1;
         if (Index_D > -1 && Index_D < strip_MapsB[sensortype].size())
         {
            key_stripD =
               plane   /* 1-3  */           +
               sensor  /* 1-140  */ * 10    +
               Index_D /* 1024 */   * 10000 ;
         }

         Disk_Maps[plane - 1][0][sensor].push_back(Index_A);
         Disk_Maps[plane - 1][1][sensor].push_back(Index_B);
         track_p_Maps[plane - 1][0][sensor].push_back(t);
         track_p_Maps[plane - 1][1][sensor].push_back(t);
         // PosZ_Maps[plane-1][sensor].push_back(zhit);
         TVector3 posVect(xhit, yhit, zhit);
         Pos_Maps[plane - 1][0][sensor].push_back(posVect);
         Pos_Maps[plane - 1][1][sensor].push_back(posVect);
         Key_Maps[plane - 1][0][sensor].push_back(key_stripA);
         Key_Maps[plane - 1][1][sensor].push_back(key_stripB);
         // Volume_Maps[plane-1][sensor].push_back(volume_id);

         if (Index_D > -1 && Index_D < strip_MapsB[sensortype].size())
         {
            Disk_Maps[plane - 1][1][sensor].push_back(Index_D);
            track_p_Maps[plane - 1][1][sensor].push_back(-1);//sign as fake hit here
            Pos_Maps[plane - 1][1][sensor].push_back(posVect);
            Key_Maps[plane - 1][1][sensor].push_back(key_stripD);
         }

      }
   }

   StPtrVecRnDHit hits;

   for (int iD = 0; iD < 3; iD++) //iDisk
   {

      for (int iS = 0; iS < 140; iS++) //iSensor
      {

         if (iS >= NColumn[iD] * NRow[iD])
         {
            continue;
            // cout << "ERROR : Sensor Index is out of Range..." << endl;
            // return;
         }

         int row  = iS / NColumn[iD] + 1;//-1 for index// start from 1
         if (row > NRow[iD])
         {
            cout << "ERROR: wrong row ..." << row << " > " << NRow[iD]
                 << " iD : " << iD << " , iS : " << iS << " , NColumn[iD] :  " << NColumn[iD] << endl;
            continue;
         }
         int column = iS % NColumn[iD] + 1;//start from 1
         if (column > NColumn[iD])
         {
            cout << "ERROR: wrong column ..." << column << " > " << NColumn[iD]
                 << " iD : " << iD << " , iS : " << iS << " , NColumn[iD] :  " << NColumn[iD] << endl;
            continue;
         };
         int sensortype = NSensorType[iD][row - 1];
         if (sensortype < 0)
         {
            cout << "ERROR: wrong sensortype..." << sensortype << " < 0" << endl;
            continue;
         };

         int N_A = Disk_Maps[iD][0][iS].size();
         int N_B = Disk_Maps[iD][1][iS].size();

         if (N_A || N_B)
         {
            cout << "iD = " << iD
                 << " , iS = " << iS
                 << " , N_A = " << N_A << " , N_B = " << N_B
                 << endl;
         }

         // Set the current path to the struck sensor and obtain transformation matrix
         {
            TString sensor_path = Form("/HALL_1/CAVE_1/FTSM_1/%s_1/%s_%i", plane_names[iD], sensor_names[iD], iS + 1);
            gGeoManager->cd(sensor_path);
         }
         const TGeoHMatrix* transform = gGeoManager->GetCurrentMatrix();


         for (int iA = 0; iA < N_A; iA++)
         {
            int Index_A = Disk_Maps[iD][0][iS][iA];
            // cout << "Index_A = " <<  Index_A << endl;
            // cout << " strip A position x1,y1: : "  << strip_MapsA[sensortype][Index_A].x1 << " : " << strip_MapsA[sensortype][Index_A].y1
            //      << " , x2,y2: : " << strip_MapsA[sensortype][Index_A].x2 << " : " << strip_MapsA[sensortype][Index_A].y2
            //      << endl;

            Point a, b;
            a.x = strip_MapsA[sensortype][Index_A].x1;
            a.y = strip_MapsA[sensortype][Index_A].y1;
            b.x = strip_MapsA[sensortype][Index_A].x2;
            b.y = strip_MapsA[sensortype][Index_A].y2;
            // cout <<  " point a : " <<"("<< a.x << " , "<< a.y<< ")" << " , point b : " <<"("<< b.x << " , "<< b.y<< ")" << endl;

            long long key_stripA = Key_Maps[iD][0][iS][iA];
            int tA = track_p_Maps[iD][0][iS][iA];

            // float zhit = PosZ_Maps[iD][iS][iA];
            TVector3 posVectA = Pos_Maps[iD][0][iS][iA];//original pisition
            // cout << " posA = " << posVectA.x() << " , " << posVectA.y() << " , " << posVectA.z() << endl;

            for (int iB = 0; iB < N_B; iB++)
            {
               int Index_B = Disk_Maps[iD][1][iS][iB];
               // cout << "Index_B = " <<  Index_B << endl;
               // cout << " strip B position x1,y1: : "  << strip_MapsB[sensortype][Index_B].x1 << " : " << strip_MapsB[sensortype][Index_B].y1
               //      << " , x2,y2: : " << strip_MapsB[sensortype][Index_B].x2 << " : " << strip_MapsB[sensortype][Index_B].y2
               //      << endl;

               Point c, d;
               c.x = strip_MapsB[sensortype][Index_B].x1;
               c.y = strip_MapsB[sensortype][Index_B].y1;
               d.x = strip_MapsB[sensortype][Index_B].x2;
               d.y = strip_MapsB[sensortype][Index_B].y2;
               // cout <<  " point c : " <<"("<< c.x << " , "<< c.y<< ")" << " , point d : " <<"("<< d.x << " , "<< d.y<< ")" << endl;

               int tB = track_p_Maps[iD][1][iS][iB];
               long long key_stripB = Key_Maps[iD][1][iS][iB];

               TVector3 posVectB = Pos_Maps[iD][1][iS][iB];//original pisition
               // cout << " posB = " << posVectB.x() << " , " << posVectB.y() << " , " << posVectB.z() << endl;

               if (posVectA.z() - posVectB.z() > 0.06 * 2)
               {
                  cout << "ERROR : Z location is not synchronize ... " << posVectA.z() << " : " << posVectB.z()  << endl;
                  continue;
               }

               Point p;
               int cross = ab_cross_cd(a, b, c, d, p);
               if (cross == 1)
               {
                  cout << " CROSSED POINT 1 in the middle, ..." << endl;
                  cout << "p = " << p.x << " , " << p.y << endl;
               }

               if (cross == 0)
               {
                  cout << " CROSSED POINT 0 atthe end,  ..." << endl;
                  cout << "p = " << p.x << " , " << p.y << endl;
               }

               if (cross != 1) continue;

               if (p.x < -0.5 * Sensor_Width || p.x > 0.5 * Sensor_Width || p.y < -0.5 * Sensor_Height[sensortype] || p.y > 0.5 * Sensor_Height[sensortype])
               {
                  cout << "CROSSED POINT out of sensor range" << endl;
                  cout << "cross point : " << p.x << " , " << p.y << endl;
                  continue;
               }

               h2LocalSmearedXY-> Fill(p.x, p.y);

               StRnDHit *ahit = new StRnDHit();
               ahit->setDetectorId(kFtsId);

               double xlocal[] = { p.x, p.y, posVectA.z()};//smeared pisition // local
               double xglobal[] = { 0, 0, 0 };// smeared position // global
               transform->LocalToMaster(xlocal, xglobal);

               // ahit->setPosition(  {p.x, p.y, posVectA.z()} );//local position
               ahit->setPosition({xglobal[0], xglobal[1], xglobal[2]});   //global position

               // ahit->setPositionError( { 0.5*Strip_Width, 0.5*Strip_Width/TMath::Tan(stereo), 0.03 } );
               double dx = Strip_Width / SQRT12;
               double dy = Strip_Width / SQRT6 / TMath::Tan(stereo);
               ahit->setPositionError({ dx, dy, 0.03 * 2. / SQRT12 });

               float Eout[3];
               float Ematrix[] = { dx * dx, 0., dy * dy };
               float rot_angle = 0.;
               float R[] = { float(TMath::Cos(rot_angle)), float(-TMath::Sin(rot_angle)),
                             float(TMath::Sin(rot_angle)), float(TMath::Cos(rot_angle))
                           };

               TCL::trasat(R, Ematrix, Eout, 2, 2);
               cout << " Ematrix[] : " << Eout[0] << " " << Eout[1] << " " << Eout[2] << endl;
               float Eg[] =
               {
                  Eout[0], Eout[1], 0.0f,
                  Eout[1], Eout[2], 0.0f,
                  0.0f, 0.0f, 0.03f
               };
               ahit->setErrorMatrix(Eg);

               ahit -> setDouble0(posVectA.x()); //? local original//from stipA
               ahit -> setDouble1(posVectA.y());
               ahit -> setDouble2(p.x);          //? local smeared x
               ahit -> setDouble3(p.y);
               ahit -> setLayer(iD + 1);         //  disk
               ahit -> setLadder(iS + 1);        //  sensor
               ahit -> setWafer(key_stripA);     //? from stripA
               if (tA == tB)
               {
                  ahit -> setIdTruth(tA, 100);  //??

                  h2LocalDeltaXY-> Fill(posVectA.x() - p.x, posVectA.y() - p.y);
                  h3LocalDeltaXYDisk-> Fill(posVectA.x() - p.x, posVectA.y() - p.y, iD);
               }
               else
               {
                  ahit -> setIdTruth(0, 0);  //??
               }

               if (fabs(posVectA.x() - posVectB.x()) < 1e-5)
               {
                  // cout << "posVectA.x : " << posVectA.x()  << " , posVectB.x : "<< posVectB.x()
                  // << " , idTruth : " << ahit->idTruth() << " , qaTruth :" << ahit->qaTruth() << endl;
                  if (ahit->qaTruth() != 100)
                  {
                     cout << "ERROR : truthID is WRONG .... " << endl;
                     continue;
                  }
               }
               cout << "posVectA.x : " << posVectA.x()  << " , posVectB.x : " << posVectB.x()
                    << " , idTruth : " << ahit->idTruth() << " , qaTruth :" << ahit->qaTruth() << endl;

               cout << " PRINT : org (" << posVectA.x() << " , "  << posVectA.y() << " ) "
                    << "smeared ( " << p.x << " , " << p.y << ")" << endl;

               hits.push_back(ahit);
            }

         }

      }

   }

   //
   // Normalize ID truth amd addd to hit collection
   //
   StRnDHitCollection* ftscollection = event->rndHitCollection();
   int nftshit = hits.size();
   // Loop over hits and digitize
   for (int i = 0; i < nftshit; i++)
   {
      //hack! do digitization here, or more realistic smearing
      ftscollection->addHit(hits[i]);
   }


}

//_____________________________________________________________________________________

void StFtsSiFastSimulatorMaker::fillThinGapChambers(StEvent *event)
{
   // Read the g2t table
   St_g2t_fts_hit* hitTable = static_cast<St_g2t_fts_hit*>(GetDataSet("g2t_fts_hit"));
   if (!hitTable)
   {
      LOG_INFO << "g2t_fts_hit table is empty" << endm;
      return;  // Nothing to do
   }  // if

   // TODO Get the primary vertex from the event record.
   float xv = 0.;
   float yv = 0.;
   float zv = 0.;

   // Stereo angle added at each detector plane
   float stereo = mStereo; // 2*TMath::Pi() / 8 / 6;

   // hash tables to store hits in strips and wires / fast lookup for handling multiple hits
   std::map<long long, StRnDHit*> strip_hits;
   std::map<long long, StRnDHit*> wire_hits;
   std::map<long long, StRnDHit*> point_hits;



   // struct FtsHit
   // {
   //   float xlocal;
   //   float ylocal;
   //   float exlocal;
   //   float eylocal;
   //   int   disk;
   //   int   octant;
   //   int   column;
   //   int   padrow;
   //   bool  isstrip;
   //   int   idtruth;
   //   float  Etruth;
   //   float  Esum;
   // };


   // wheel octants columns pads hits
   std::array< std::array< std::array< std::array< std::vector<StRnDHit*>, 10>, 3>, 8>, 6> strip_hits_bank;
   std::array< std::array< std::array< std::array< std::vector<StRnDHit*>, 10>, 3>, 8>, 6> wire_hits_bank;
   std::array< std::array< std::array< std::array< std::vector<StRnDHit*>, 10>, 3>, 8>, 6> strip_hits_vec;
   std::array< std::array< std::array< std::array< std::vector<StRnDHit*>, 10>, 3>, 8>, 6> wire_hits_vec;

   std::array< std::vector<StRnDHit*>, 6 > point_hits_by_wheel;

   // Prepare to loop over all hits
   const int nhits           = hitTable->GetNRows();
   const g2t_fts_hit_st* hit = hitTable->GetTable();
   LOG_INFO <<"nhits= "<<nhits<<endm;

   for (int i = 0; i < nhits;  i++)
   {
      hit = (g2t_fts_hit_st *)hitTable->At(i);
      if (0 == hit) continue;

      float xhit = hit->x[0];
      float yhit = hit->x[1];
      float zhit = hit->x[2];
      int   disk = hit->volume_id;
   LOG_INFO <<"volume_id="<<disk<<endm;
      if (disk > 12) continue;  // skip Si disks

      LOG_INFO << "wheel hit " << disk << " x=" << xhit << " y=" << yhit << " z=" << zhit << endl;

      //if (false == mEnable[disk - 1]) continue; // disk switched off

      float alph = mStereo * (disk - 7);         // stereo angle at this sation

      int octant = -1; // octant number
      int pad    = -1; // pad row number    (in X)
      int col    = -2; // pad column number (in Y)
      int strip  = -1; // strip number
      int wire   = -1; // wire number

      float xoctant    = 0.;
      float yoctant    = 0.;
      float phi_octant = 0.;

      //
      // Rotate hit into octant coordinate system
      //

      octant     = globalToOctant(xhit, yhit, alph, xoctant, yoctant);
      phi_octant = TMath::ATan2(yoctant, xoctant);


      // hGlobalYX->Fill( xhit, yhit );
      // hOctantYX->Fill( xoctant, yoctant );



      //
      // Ensure we are within the x limits of the octant
      //
      if (xoctant < OCTANT_XMIN[disk - 7]) continue;
      if (xoctant > OCTANT_XMAX[disk - 7]) continue;


      //
      // Shift origin to the lower edge of the octant
      //
      float xshift = xoctant - OCTANT_XMIN[disk - 7];
      float yshift = yoctant;

      //
      // Find padrow and column
      //
      pad = xshift / PAD_WIDTH;
      col = 1;
      if (phi_octant >  PI / 12) col = 2;
      if (phi_octant < -PI / 12) col = 0;

// LOG_INFO << Form("    pad=%02d col=%02d",pad,col) << endm;


      // Position relative to the start of the pad
      float xpad = xshift - float(pad) * PAD_WIDTH;

      // Position of the center of the pad in global coords
      float xpad_center = (0.5 + float(pad)) * PAD_WIDTH + OCTANT_XMIN[disk - 7];
      // Position of the low edge of the pad in global coords
      float xpad_low    = (float(pad)) * PAD_WIDTH + OCTANT_XMIN[disk - 7];

      //////////////////////////////////////////////////////////////////////////////////
      //
      // Find the wire position and uncertainty
      //
      //////////////////////////////////////////////////////////////////////////////////

      // Calculate the x position of the wire and its error (easy)

      float xwire  = (0.5 + float(pad)) * PAD_WIDTH;   // middle of the pad rel. to octant start
      float exwire = PAD_WIDTH / SQRT12;

      // Wire x position in local global coordinates
      xwire += OCTANT_XMIN[disk - 7];

      // Stop placing wires beyond the smaller pad width.

      float ylow  = -TMath::Tan(PI / 8) * xpad_low;
      float yhigh = +TMath::Tan(PI / 8) * xpad_low;

      float ywire  = 0;
      float eywire = mWireSpacing / SQRT12;

      // Compute a wire number, and the wire position
      wire = (yoctant - ylow) / mWireSpacing;
      ywire = (float(wire) + 0.50) * mWireSpacing + ylow;

      // Check that wire is in allowed range of phi
      float phi_wire = TMath::ATan2(ywire, xwire);
      if (phi_wire > -PI / 8 && phi_wire < PI / 8)
      {

         // ywire can't be below low, but can be above high... wont be instrumented here, so...

         float xwire_global, ywire_global;

         float Ewire[] = {exwire * exwire,
                          0.,             eywire * eywire
                         };

         assert(0 < eywire);
         assert(0 < exwire);

         // hOctantWireYX -> Fill( xwire, ywire );
         //
         // hWirePullsX  -> Fill( (xwire-xoctant) / exwire, float(disk-7) );
         // hWirePullsY  -> Fill( (ywire-yoctant) / eywire, float(disk-7) );
         // hWireDeltasX -> Fill( (xwire-xoctant)         , float(disk-7) );
         // hWireDeltasY -> Fill( (ywire-yoctant)         , float(disk-7) );

         octantToGlobal(xwire, ywire, octant, alph, xwire_global, ywire_global, Ewire);

         //    long long wire_key = wire + 1000*col + 10000*pad + 100000*octant;

         long long wire_key =
            disk           + /// 1-12 /
            octant * 100    + /// 0-7  /
            pad    * 1000   + /// 0-5  /
            col    * 10000  + /// 0-2  /
            wire   * 100000 ; /// large /

         StRnDHit *wire_hit = wire_hits[ wire_key ];
         if (0 == wire_hit)
         {
            wire_hit = wire_hits[wire_key] = new StRnDHit();
            wire_hits_vec[ disk - 7 ][ octant ][ col ][ pad ].push_back(wire_hit);
         }
         else
         {
            float zold = wire_hit->position()[2] + 0.1f;
            if (TMath::Abs(zold - zhit) > 0.1)
            {
               LOG_WARN << "Wrong wheel for double hit wire: zold=" << zold << " znew=" << zhit << endm;
               LOG_WARN << disk << endm;
               LOG_WARN << octant << endm;
               LOG_WARN << pad << endm;
               LOG_WARN << wire << endm;
               LOG_WARN << wire_key << endm;
            }
         }

         wire_hit -> setLayer(disk);
         wire_hit -> setLadder(wire);
         wire_hit -> setWafer(octant);

         wire_hit -> setDetectorId(kFtsId);
         wire_hit -> setPosition({xwire_global, ywire_global, zhit - 0.1f });
         wire_hit -> setPositionError({ exwire, eywire, 0.1f });

         wire_hit -> setDouble0(xhit);
         wire_hit -> setDouble1(yhit);
         wire_hit -> setDouble2(xwire);
         wire_hit -> setDouble3(ywire);

         wire_hit -> setIdTruth(hit->track_p,  wire_hit -> qaTruth() + 1);

         float Ewire_global[] = { Ewire[0], Ewire[1], 0.0f,
                                  Ewire[1], Ewire[2], 0.0f,
                                  0.0f,     0.0f,     0.1f
                                };

         wire_hit -> setErrorMatrix(Ewire_global);


         //    wire_hits_vec[ octant ][ col ][ pad ].push_back( wire_hit );


      }

      //     wire_hit -> Print();


      //////////////////////////////////////////////////////////////////////////////////
      //
      // Find the strip position and uncertainty
      //
      //////////////////////////////////////////////////////////////////////////////////

      //
      // strip number hit in the pad / x and y of the strip
      //
      strip = xpad / mStripWidth;

      // Position of the strip relative to the pad boundary
      float  xstrip = (0.5 + float(strip)) * mStripWidth;

      // Shift strip back to octant coordinates.  x is shifted.  y should remain the same
      xstrip += float(pad) * PAD_WIDTH + OCTANT_XMIN[disk - 7];


      // Width of the octant at the strip
      float dyoctant = 2.0 * xstrip * TMath::Tan(PI / 8);

      // Place y at the center of each column
      float ystrip  = float(1 - col) * dyoctant / 3;

      // This is the strip's error matrix in octant local system
      float dystrip = dyoctant / 3;
      float dxstrip = mStripWidth;
      float Estrip[] = { dxstrip*dxstrip / 12, 0., dystrip*dystrip / 12 };

      // Rotate back to the global system
      float xstrip_global;
      float ystrip_global;

      // hOctantStripYX -> Fill( xstrip, ystrip );

      // hStripPullsX -> Fill( (xstrip-xoctant) / dxstrip * SQRT12, float(disk-7) );
      // hStripPullsY -> Fill( (ystrip-yoctant) / dystrip * SQRT12, float(disk-7) );

      // hStripDeltasX -> Fill( (xstrip-xoctant)                   , float(disk-7) );
      // hStripDeltasY -> Fill( (ystrip-yoctant)                   , float(disk-7) );

      octantToGlobal(xstrip, ystrip, octant, alph, xstrip_global, ystrip_global, Estrip);

      // long long key_strip = strip + 1000*pad + 100000*col + 10000000*octant + 10000000000*disk;

      long long key_strip =
         disk           + // 1-12 /
         octant * 100    + // 0-7  /
         pad    * 1000   + // 0-5  /
         col    * 10000  + // 0-2  /
         strip  * 100000 ; // large /

      StRnDHit *strip_hit = strip_hits[ key_strip ];
      if (0 == strip_hit)
      {
         strip_hit = strip_hits[key_strip] = new StRnDHit();
         strip_hits_vec[ disk - 7 ][ octant ][ col ][ pad ].push_back(strip_hit);
      }
      else
      {
         float zold = strip_hit->position()[2] - 0.1f;
         if (TMath::Abs(zold - zhit) > 0.1)
         {
            LOG_WARN << "Wrong wheel for double hit strip: zold=" << zold << " znew=" << zhit << endm;
            LOG_WARN << disk << endm;
            LOG_WARN << octant << endm;
            LOG_WARN << pad << endm;
            LOG_WARN << strip << endm;
            LOG_WARN << key_strip << endm;
         }
      }


      strip_hit -> setLayer(disk);       // disk mapped to layer
      strip_hit -> setLadder(strip);     // indicates a strip
      strip_hit -> setWafer(octant);     // octant number

      strip_hit -> setDetectorId(kFtsId);
      strip_hit -> setPosition({ xstrip_global, ystrip_global, zhit + 0.1f });
      strip_hit -> setPositionError({ dxstrip / SQRT12, dystrip / SQRT12, 0.1f });

      strip_hit -> setDouble0(xhit);
      strip_hit -> setDouble1(yhit);
      strip_hit -> setDouble2(xstrip);
      strip_hit -> setDouble3(ystrip);

      strip_hit -> setIdTruth(hit->track_p,  strip_hit -> qaTruth() + 1);

      float Estrip_global[] = { Estrip[0], Estrip[1], 0.0f,
                                Estrip[1], Estrip[2], 0.0f,
                                0.0f,      0.0f,      0.1f
                              };

      strip_hit -> setErrorMatrix(Estrip_global);

      // strip_hit -> Print();

      // strip_hits_vec[ octant ][ col ][ pad ].push_back( strip_hit );


      //#ifdef __NO_AMBIGUITY__
      if (0 == mAmbiguity)
      {
         if (mPointHits)     // combine xstrip and ywire into single point
         {

            LOG_INFO << " x: xoctant=" << xoctant
                     << "    xstrip=" << xstrip
                     << " y: yoctant=" << yoctant
                     << "    ywire=" << ywire
                     << endm;

            float  x = xstrip;
            float  y = ywire;
            float dx = mStripWidth  / SQRT12;
            float dy = mWireSpacing / SQRT12;

            float Ept[] = { dx * dx, 0., dy * dy }; // returns from octantToGlobal a 2x2 triangular packed mtx

            float xg, yg;

            // hPointsPullsX -> Fill(float(( x - xoctant ) /dx),float(disk-7));
            // hPointsPullsY -> Fill(float(( y - yoctant ) /dy),float(disk-7));

            octantToGlobal(x, y, octant, alph, xg, yg, Ept);

            float Eg[] =
            {
               Ept[0], Ept[1], 0.f,
               Ept[1], Ept[2], 0.f,
               0.f, 0, 0.f, 0.1
            };


            //
            // NOTE -- not sure at all that this logic is correct... but maybe we
            // don't use it... combinatorics look like thay are handled below...
            //
            StRnDHit *ahit = point_hits[ key_strip ];
            if (0 == ahit) ahit = point_hits[key_strip] = new StRnDHit();

            ahit->setPosition({ xg, yg, zhit });
            ahit->setPositionError({ dx, dy, 0.1 });

            ahit->setErrorMatrix(Eg);

            ahit -> setDouble0(xhit);
            ahit -> setDouble1(yhit);
            ahit -> setDouble2(xstrip);
            ahit -> setDouble3(ystrip);
            ahit -> setLayer(disk);       // disk mapped to layer
            ahit -> setLadder(3);         // indicates a point
            ahit -> setWafer(octant);     // octant number

            ahit -> setIdTruth(hit->track_p, 0);

         }
      }
      //#endif

   }



   //
   // Normalize ID truth amd addd to hit collection
   //
   StRnDHitCollection* ftscollection = event->rndHitCollection();

   if (0 == mPointHits)     // writeout wire and strip hits individually
   {
  cout<<" zzzzzz1 "<<endl;

      for (auto& iter : strip_hits)
      {
         auto* hit = iter.second;
         hit->setDetectorId(kFtsId);
         int id = hit->idTruth();
         int qa = 100 / hit->qaTruth();
         hit->setIdTruth(id, qa);
         if (verbose) hit->Print();
         ftscollection->addHit(hit);
      }
      for (auto& iter : wire_hits)
      {
  cout<<" zzzzzz2 "<<endl;
         auto* hit = iter.second;
         hit->setDetectorId(kFtsId);
         int id = hit->idTruth();
         int qa = 100 / hit->qaTruth();
         hit->setIdTruth(id, qa);
         if (verbose) hit->Print();
         ftscollection->addHit(hit);
      }

   }
   //#ifdef __NO_AMBIGUITY__
   else if (0 == mAmbiguity)   // pad-like hits
   {
  cout<<" zzzzzz3 "<<endl;
      for (auto& iter : point_hits)
      {
         auto* hit = iter.second;
         assert(hit);
         if (verbose) hit->Print();
         ftscollection->addHit(hit);
      }
   }


   // Points have been generated
   if (0 == mAmbiguity)
   {
      return;
   }

   //#else
   //
   // handle combinatoric hits in pads (no
   //
   for (int wheel = 0; wheel < 6; wheel++)
      for (int octant = 0; octant < 8; octant++)
         for (int column = 0; column < 3; column++)
            for (int row = 0; row < 10; row++)
            {

               const auto& strips = strip_hits_vec[wheel][octant][column][row];
               const auto& wires  =  wire_hits_vec[wheel][octant][column][row];

               for (auto* shit : strips)
                  for (auto* whit : wires)
                  {

                     StThreeVectorF spos = shit->position(); // strip position
                     StThreeVectorF wpos = whit->position(); // wire position
                     StThreeVectorF serr = shit->positionError(); // strip error
                     StThreeVectorF werr = whit->positionError(); // wire error

                     //
                     // x & y position before rotation to global
                     //
                     float x = shit->double2();
                     float y = whit->double3();
                     //          float z = (spos[2]+wpos[2])*0.5;
                     float zw = wpos[2];
                     float zs = spos[2];
                     if (TMath::Abs(zw - zs) > 1.0)
                     {
                        LOG_INFO << "Strip and wire from different z locations WTF? " << zw << " " << zs << " " << whit->layer() << " " << shit->layer() << endm;
                        shit->Print();
                        whit->Print();
                        continue; // sweep under da rug...
                     }
                     float z = (zw + zs) * 0.5;


                     float ex = serr[0] * fudge_error;
                     float ey = werr[1] * fudge_error;
                     float ez = 1.0;

                     float Ematrix[] =
                     {
                        ex * ex ,
                        0.0f  , ey*ey
                     };

                     float xg, yg;
                     octantToGlobal(x, y, octant, mStereo * wheel, xg, yg, Ematrix);

                     float Eglobal[] =
                     {
                        Ematrix[0], Ematrix[1], 0.0f,
                        Ematrix[1], Ematrix[2], 0.0f,
                        0.0f      , 0.0f      , ez*ez
                     };


                     int strip = shit->ladder();
                     int wire  = whit->ladder();


                     StRnDHit *ahit = new StRnDHit();

                     //
                     // Encode detector IDs for offline QA
                     //
                     ahit->setLayer(wheel + 7);
                     ahit->setLadder(octant);   // strip number
                     ahit->setWafer(10 * row + column);  // wire number
                     ahit->setExtraByte2(strip);
                     ahit->setExtraByte3(wire);

                     ahit->setPosition({ xg, yg, z });
                     ahit->setPositionError({ ex, ey, ez });
                     ahit->setErrorMatrix(Eglobal);

                     if (shit->idTruth() == whit->idTruth())
                     {
                        ahit->setIdTruth(shit->idTruth(), 100);
                     }
                     else
                     {
                        ahit->setIdTruth(0, 0);
                     }

                     ahit->setExtraByte0(shit->idTruth());
                     ahit->setExtraByte1(whit->idTruth());



                     point_hits_by_wheel[ wheel ].push_back(ahit);

                     //          ftscollection->addHit(ahit);
                     //          ahit->Print();

                  }


            }

   float window = mWindow; // accept all

   std::map< StRnDHit*, int > point_accumulator;

   //
   // Vertex filtering of hits in each station
   //

   int wheel1[] = { 1, 2, 3, 4, 5, 6 };
   int wheel2[] = { 2, 1, 4, 3, 6, 5 };

   int hit_count_total = 0;
   for (int i = 0; i < 6; i++)
   {

      for (auto& hit1 : point_hits_by_wheel[ wheel1[i] ])
      {
         hit_count_total++;

         // hit already added
         if (0 != point_accumulator[ hit1 ]) continue;

         float xh1 = hit1->position()[0];
         float yh1 = hit1->position()[1];
         float zh1 = hit1->position()[2];

         float dx1 = hit1->covariantMatrix()(1, 1);
         float dy1 = hit1->covariantMatrix()(2, 2);

         float dxdz = (xh1 - xv) / (zh1 - zv); // slope in x from vtx
         float dydz = (yh1 - yv) / (zh1 - zv); // slope in y from vtx

         for (auto& hit2 : point_hits_by_wheel[ wheel2[i] ])
         {

            float xh2 = hit2->position()[0];
            float yh2 = hit2->position()[1];
            float zh2 = hit2->position()[2];

            float xpred = dxdz * (zh2 - zv);   // str8 line from first to second plane
            float ypred = dydz * (zh2 - zv);   // str8 line from first to second plane

            if (TMath::Abs(xpred - xh2) > window * dx1) continue;
            if (TMath::Abs(ypred - yh2) > window * dy1) continue;

            // add both hits to the accumulator and keep looking for other
            // hits in this window.
            point_accumulator[ hit1 ]++;
            point_accumulator[ hit2 ]++;

         }
      }

   }

   LOG_INFO << "______________________________________________________________" << endm;
   //    LOG_INFO << "Filtered hits" << endm;

   LOG_INFO << "Total FTS silicon hits: " << ftscollection->numberOfHits() << endm;
   LOG_INFO << "Total FTS wheel hits: " << hit_count_total << endm;
   int hit_count_filt = 0;
   for (auto& iter : point_accumulator)
   {
      hit_count_filt++;
      ftscollection->addHit(iter.first);

   };


   LOG_INFO << "Filtered FTS wheel htis:  " << hit_count_filt << endm;
   LOG_INFO << "Total FTS: " << ftscollection->numberOfHits() << endm;


   //#endif


};


