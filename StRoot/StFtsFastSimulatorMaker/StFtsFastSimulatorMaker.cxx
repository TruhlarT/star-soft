#if 0 
// $Id: StFtsFastSimulatorMaker.cxx,v 1.1.2.3 2018/06/07 16:18:49 jwebb Exp $                                            
//                                                                                                                     
// $Log: StFtsFastSimulatorMaker.cxx,v $
// Revision 1.1.2.3  2018/06/07 16:18:49  jwebb
// Note-- code may not have been previously checked in.
//
// This version comments out the class (#if 0 ... #endif), so that it does not
// interfere with Guannan's StFtsSiFastSimulatorMaker.  Old code is preserved
// for now, but want to move on to the newer Si disk code.
//
// Revision 1.1.2.1  2018/03/15 19:38:11  jwebb
//
// Initial checkin of StFtsFastSimulatorMaker.
//
// Revision 1.15  2016/12/06 21:45:52  jwebb
// Add pseudo point finder
//
// Revision 1.14  2016/12/06 19:25:41  jwebb
// Rewrite of sTGC wheels.
//
// Revision 1.13  2016/12/01 14:17:29  jwebb
// Added stereo angle and option to merge(or not) hits to same channel.
//
// Revision 1.12  2016/11/30 16:31:12  jwebb
// Both strips and wires can be out of acceptance.
//
// Revision 1.11  2016/11/30 16:27:54  jwebb
// Added detector ID.  Modified sTGC wheel dimensions for new geom.
//
// Revision 1.10  2016/11/28 22:52:04  jwebb
// Added QA / fixed errors
//
// Revision 1.9  2016/11/23 16:43:29  jwebb
// Refactor to use RnD hits, so as to not introduce additional dependencies into StEvent
//
// Revision 1.8  2016/11/23 16:06:07  jwebb
// Add thin gap chamber digitization to the simulator.  This version hardcodes the z-positions of the detectors.
//
// Revision 1.7  2015/11/25 22:18:32  jwebb
// Code to raster the position of the disks.
//
// Revision 1.6  2015/11/24 19:01:37  jwebb
// Rename hit collection in StEvent (required so that hits are saved into StEvent).  Improve hit ID truth.
//
// Revision 1.5  2015/11/13 18:44:10  jwebb
// IdTruth for FTS.
//
// Revision 1.4  2015/11/06 00:00:59  jwebb
// ... and same fix, just found all the places it needed to be made.
//
// Revision 1.3  2015/11/05 23:22:36  jwebb
// Added last two discs to the simulator.  Fixed bug where disk 6 was overflowing memory location and being dropped.
//
// Revision 1.2  2015/10/20 21:48:57  jwebb
// Updated FTS simulator to allow runtime configuration of pixels divisions.
//
// Revision 1.1  2015/10/16 15:22:50  jwebb
// Offline area established for STAR upgrades

#include "StFtsFastSimulatorMaker/StFtsFastSimulatorMaker.h"
#include "St_base/StMessMgr.h"
#include "StEvent/StEvent.h"
//#include "StEvent/StFtsHitCollection.h"
//#include "StEvent/StFtsHit.h"
#include "StEvent/StRnDHitCollection.h"
#include "StEvent/StRnDHit.h"
#include "tables/St_g2t_fts_hit_Table.h"
#include "StThreeVectorF.hh"
#include <array>
#include "TCanvas.h"
#include "TH2F.h"
#include "TLine.h" 
#include "TVector3.h"
#include "TCernLib.h"
#include "TString.h"
#include <array>

TCanvas *canvas = 0;
StMatrixF  Hack1to6(const StHit *stHit);

constexpr float PI     = atan2(0.0,-1.0);
constexpr float SQRT12 = sqrt(12.0);


const float OCTANT_WIDTH_PHI        = PI/4;
const float OCTANT_GLOBAL_PHI_MIN[] = {-PI/8, PI/8, 3*PI/8, 5*PI/8, 7*PI/8, 9*PI/8, 11*PI/8, 13*PI/8};
const float OCTANT_GLOBAL_PHI_MAX[] = {       PI/8, 3*PI/8, 5*PI/8, 7*PI/8, 9*PI/8, 11*PI/8, 13*PI/8, 15*PI/8};

const float OCTANT_XMIN[] = {  6.0f,  6.0f,  6.0f,  6.0f,  6.0f,  6.0f }; // octant size in each disk... 
const float OCTANT_XMAX[] = { 42.0f, 42.0f, 66.0f, 66.0f, 66.0f, 66.0f };

const float PAD_WIDTH    = 6.0f;
const float STRIP_WIDTH  = 0.3f;   // must divide nicly into 6cm
const float WIRE_SPACING = 0.15f;  // ditto


// helper functions

int globalToOctant( const float& xglobal, /* input */ 
		    const float& yglobal, /* input */ 
		    const float& stereo,  /* input */ 
		    float& xoctant,       /* output */ 
		    float& yoctant        /* output */ )
{
  
  //
  // takes as input a stereo angle, which is subtracted the phibin boundaries
  //

  // Get global phi and map it between the min and max octant boundaries
  float phi_global = TMath::ATan2( yglobal, xglobal );

  while ( phi_global <  OCTANT_GLOBAL_PHI_MIN[0]-stereo ) phi_global += 2*PI;
  while ( phi_global >= OCTANT_GLOBAL_PHI_MAX[7]-stereo ) phi_global -= 2*PI;

  // Find which octant we are in
  int octant = 0;
  for ( octant=0; octant<7; octant++ )
    {
      float phi_min = OCTANT_GLOBAL_PHI_MIN[octant]-stereo;
      float phi_max = OCTANT_GLOBAL_PHI_MAX[octant]-stereo;
      //      std::cout << octant << " mn=" << phi_min << " mx=" << phi_max << " phig=" << phi_global << std::endl;
      if ( phi_global >= phi_min && phi_global < phi_max ) break;
      
    } 
  
  float phi_local = phi_global - octant*OCTANT_WIDTH_PHI + stereo;
  //  float rot_angle = phi_local  - phi_global;
  float rot_angle = - octant*OCTANT_WIDTH_PHI + stereo;
  
  xoctant = xglobal * TMath::Cos( rot_angle ) - yglobal * TMath::Sin( rot_angle );
  yoctant = xglobal * TMath::Sin( rot_angle ) + yglobal * TMath::Cos( rot_angle );

  return octant;
}

int octantToGlobal ( const float& xoctant, /* input */ 
		     const float& yoctant, /* input */ 
		     const int&    octant, /* input */ 
		     const float&  stereo, /* input */ 
		     float& xglobal,       /* output */ 
		     float& yglobal        /* output */,
		     float* Ematrix=0      /* optional error matrix in triangular form */
		     )
{

  // Get local phi 
  float phi_local = TMath::ATan2( yglobal, xglobal );

  // rotation angle back to global
  float rot_angle = octant * OCTANT_WIDTH_PHI - stereo;

  xglobal = xoctant * TMath::Cos( rot_angle ) - yoctant * TMath::Sin( rot_angle );
  yglobal = xoctant * TMath::Sin( rot_angle ) + yoctant * TMath::Cos( rot_angle );

  if ( Ematrix ) 
    {
      float Eout[3];
      float R[] = { float(TMath::Cos( rot_angle )), float(-TMath::Sin( rot_angle )),
		    float(TMath::Sin( rot_angle )), float( TMath::Cos( rot_angle )) };

      TCL::trasat( R, Ematrix, Eout, 2, 2 );

      Ematrix[0]=Eout[0];
      Ematrix[1]=Eout[1];
      Ematrix[2]=Eout[2];
							  
    }


  return octant;
  
}
// int octantToPad( const float& xoctant,  /* input */ 
// 		 const float& yoctant,  /* input */
// 		 const int&   disk,     /* input 7-12 */
// 		 float& xpad,
// 		 float& ypad ) {
//   float xmn = OCTANT_XMIN[disk-7];
//   float xmx = OCTANT_XMAX[disk-7];
//   if ( xoctant > xmx ) return -1;
//   xpad = xoctant - xmn;
//   ypad = yoctant;
// }
	     

#if 0
struct __unit_test {

  __unit_test() 
  {
    float xin[] = { -10, -10, -10,  0,  0, +10, +10, +10 };
    float yin[] = { -10,  0, +10, -10, +10, -10,  0, +10 };
    float xout, yout, stereo =     -2.0 * TMath::DegToRad();
    float xgl, ygl;

    for ( int i=0;i<8;i++ )
      {
	int oct = globalToOctant( xin[i],yin[i],stereo,xout,yout );
	std::cout << "G to L: " 
		  << Form( "xgl=%8.4f ", xin[i] )
		  << Form( "ygl=%8.4f ", yin[i] )
		  << Form( "xlo=%8.4f ", xout )
		  << Form( "ylo=%8.4f ", yout )
		  << Form( "octant=%i ", oct )
		  << std::endl;


	float E[] = { 1.0, 0., 0. };


	int xxx = octantToGlobal( xout, yout, oct ,stereo, xgl,ygl, E );
	std::cout << "L to G: " 
		  << Form( "xlo=%8.4f ", xout )
		  << Form( "ylo=%8.4f ", yout )
		  << Form( "xgl=%8.4f ", xgl )
		  << Form( "ygl=%8.4f ", ygl )
		  << Form( "octant=%i ", oct )
		  << Form( "  [%8.4f  %8.4f][%8.4f %8.4f] ", E[0], E[1], E[1], E[2] )
		  << std::endl;

	std::cout << "diff: "
		  << Form( "xdiff=%8.4f ", xin[i] - xgl )
		  << Form( "ydiff=%8.4f ", yin[i] - ygl )
		  << std::endl << std::endl;

      }


  };

} __unit_test__;
#endif



const bool  verbose    = false; 
const bool  merge_hits = true;

StFtsFastSimulatorMaker::StFtsFastSimulatorMaker(const Char_t* name) 
  : StMaker(name),
    mNumR(64),
    mNumPHI(128),
    mNumSEC(12),
    mRaster(0),
    hGlobalYX(0),
    hOctantYX(0),
    hOctantWireYX(0),
    hOctantStripYX(0),
    hWireDeltasX(0),
    hWireDeltasY(0),
    hStripDeltasX(0),
    hStripDeltasY(0),
    hWirePullsX(0),
    hWirePullsY(0),
    hStripPullsX(0),
    hStripPullsY(0),
    hPointsPullsX(0),
    hPointsPullsY(0),
    mPointHits(false)
{}

int StFtsFastSimulatorMaker::Init()
{

  AddHist( hGlobalYX = new TH2F("hGlobalYX","Global hits before segmentation", 151,-75.5,75.5, 151,-75.5,75.5) );
  AddHist( hOctantYX = new TH2F("hOctantYX","Octant hits before segmentation", 151,-75.5,75.5, 151,-75.5,75.5) );

  AddHist( hOctantStripYX = new TH2F("hOctantStripYX", "Octant hits with strip segmentation", 141,-0.25,70.25, 141,-35.25,35.25));
  AddHist( hOctantWireYX  = new TH2F("hOctantWireYX",  "Octant hits with wire segmentation", 141,-0.25,70.25,  141,-35.25,35.25));


  // Book deltas for FTS thin gap chamber wheels
  AddHist( hWireDeltasX  = new TH2F("hWireDeltasX", ";deltaX;sTGC wheel",   81,-4.05,4.05,   7,-0.5,6.5) );
  AddHist( hWireDeltasY  = new TH2F("hWireDeltasY", ";deltaY;sTGC wheel",   81,-4.05,4.05,   7,-0.5,6.5) );

  AddHist( hStripDeltasX = new TH2F("hStripDeltasX",";deltaX;sTGC wheel",   81,-4.05,4.05,   7,-0.5,6.5) );
  AddHist( hStripDeltasY = new TH2F("hStripDeltasY",";deltaY;sTGC wheel",   81,-40.5,40.5,   7,-0.5,6.5) );

  // Book pulls for FTS thin gap chamber wheels
  AddHist( hWirePullsX  = new TH2F("hWirePullsX", ";pullX;sTGC wheel",   81,-4.05,4.05,   7,-0.5,6.5) );
  AddHist( hWirePullsY  = new TH2F("hWirePullsY", ";pullY;sTGC wheel",   81,-4.05,4.05,   7,-0.5,6.5) );

  AddHist( hStripPullsX = new TH2F("hStripPullsX",";pullX;sTGC wheel",   81,-4.05,4.05,   7,-0.5,6.5) );
  AddHist( hStripPullsY = new TH2F("hStripPullsY",";pullY;sTGC wheel",   81,-4.05,4.05,   7,-0.5,6.5) );

  AddHist( hPointsPullsX = new TH2F("hPointsPullsX",";pullX;sTGC wheel",   81,-4.05,4.05,   7,-0.5,6.5) );
  AddHist( hPointsPullsY = new TH2F("hPointsPullsY",";pullY;sTGC wheel",   81,-4.05,4.05,   7,-0.5,6.5) );

  return StMaker::Init();

}


Int_t StFtsFastSimulatorMaker::Make() {
    LOG_DEBUG << "StFtsFastSimulatorMaker::Make" << endm;
    // Get the existing StEvent, or add one if it doesn't exist.
    StEvent* event = static_cast<StEvent*>(GetDataSet("StEvent"));
    if(!event) {        
	event = new StEvent;
	AddData(event);
	LOG_DEBUG << "Creating StEvent" << endm;
    } 
    // // Add an FTS collection to the event if one does not already exist.
    // if (!event->ftsCollection()) {
    // 	event->setFtsCollection(new StFtsHitCollection);
    // 	LOG_DEBUG << "Creating StFtsHitCollection" << endm;
    // }  // if

    if ( 0 == event->rndHitCollection() ) {
      event -> setRnDHitCollection( new StRnDHitCollection() );
      LOG_DEBUG << "Creating StRnDHitCollection for FTS" << endm;      
    }

    // Digitize GEANT FTS hits
    fillSilicon(event);
    //    event->rndHitCollection()->Print();
    fillThinGapChambers(event);

    return kStOk;
}

/* Fill an event with StFtsHits. */
/* This should fill StFtsStrip for realistic simulator and let clustering fill StFtsHit */
/* For now skipping StFtsStrip and clustering, and fill StFtsHits directly here*/



void StFtsFastSimulatorMaker::fillSilicon(StEvent* event) {

  //    StFtsHitCollection * ftscollection = event->ftsCollection();    
  StRnDHitCollection* ftscollection = event->rndHitCollection();

  /*static const*/ const int NDISC=6;    
    //static const int MAXR  =128; // JCW: let's give Stv best shot at this possible...
    //static const int MAXPHI=128*12;      
  /*static const */const int MAXR   = mNumR;
  /*static const */const int MAXPHI = mNumPHI * mNumSEC;

    
    //I guess this should be RSEG[NDISC][MAXR+1] array to give better R segements
    //For now this is just unform R segments regardless of disc 
    //static const float RMIN[NDISC]={ 2.5, 2.5, 2.5, 2.5}; //hack this need to get right numbers
    //static const float RMAX[NDISC]={23.2,23.2,23.2,23.2}; //hack this need to get right numbers
    //    static const float PI=atan2(0.0,-1.0);
    //    static const float SQRT12=sqrt(12.0);
    /*
    Rmin =     2.56505
    Rmax =    11.56986
    Rmin =     3.41994
    Rmax =    15.42592
    Rmin =     4.27484
    Rmax =    19.28199
    Rmin =     5.13010
    Rmax =    23.13971
    */
    static const float RMIN[] = {   2.56505,   3.41994,   4.27484,  5.13010, 5.985, 6.83988 };
    static const float RMAX[] = {  11.56986,  15.42592,  19.28199, 23.13971, 26.99577, 30.84183 };


    // Raster each disk by 1mm, 60 degree offset for every disk
    static       float X0[] = { 0, 0, 0, 0, 0, 0 };
    static       float Y0[] = { 0, 0, 0, 0, 0, 0 }; 
    if ( mRaster > 0 ) for ( int i=0;i<6;i++ )
      {
	X0[i] = mRaster * TMath::Cos( i*60 * TMath::DegToRad() );
	Y0[i] = mRaster * TMath::Sin( i*60 * TMath::DegToRad() );	
      }


     //table to keep pointer to hit for each disc, r & phi strips
     StRnDHit* _map[NDISC][MAXR][MAXPHI];
     double ***enrsum = (double* **)malloc(NDISC*sizeof(double **));
	 double ***enrmax = (double* **)malloc(NDISC*sizeof(double **)); 
	 //memset( _map, 0, NDISC*MAXR*MAXPHI*sizeof(StRnDHit*) );
     //StRnDHit* ***_map = (StRnDHit* ***)malloc(NDISC*sizeof(StRnDHit* **));[NDISC][MAXR][MAXPHI];
	 for( int id=0; id<NDISC; id++){
		 enrsum[id] = (double**)malloc(MAXR*sizeof(double *));
		 enrmax[id] = (double**)malloc(MAXR*sizeof(double *));
		 for(int ir=0; ir<MAXR;ir++){
			 enrsum[id][ir] = (double*)malloc(MAXPHI*sizeof(double));
			 enrmax[id][ir] = (double*)malloc(MAXPHI*sizeof(double));
		 }
	 }

    
     for ( int id=0;id<NDISC;id++) {
     	for ( int ir=0;ir<MAXR;ir++ ) {
     	    for ( int ip=0;ip<MAXPHI;ip++ ) {
     		_map[id][ir][ip]=0;
     		enrsum[id][ir][ip]=0;
     		enrmax[id][ir][ip]=0; 
     	    }
     	}
     }
	
   

    
    // Read the g2t table
    St_g2t_fts_hit* hitTable = static_cast<St_g2t_fts_hit*>(GetDataSet("g2t_fts_hit"));
    if (!hitTable) {
	LOG_INFO << "g2t_fts_hit table is empty" << endm;
	return;  // Nothing to do
    }  // if
    
    const Int_t nHits = hitTable->GetNRows();
    LOG_DEBUG << "g2t_fts_hit table has " << nHits << " hits" << endm;
    const g2t_fts_hit_st* hit = hitTable->GetTable();
    //    StPtrVecFtsHit hits; //temp storage for hits
    StPtrVecRnDHit hits;
    int count = 0; 
    for (Int_t i=0; i < nHits; ++i) {
      hit = (g2t_fts_hit_st *)hitTable->At(i);
	if (hit) {
            int   d = hit->volume_id; 
	    if ( d > 6 ) continue; // skip large disks

	    float e = hit->de;
	    int   t = hit->track_p;

	    float xc = X0[d-1];
	    float yc = Y0[d-1];

	    float x = hit->x[0];
	    float y = hit->x[1];
	    float z = hit->x[2];

	    // rastered
	    float xx = x - xc;
	    float yy = y - yc;

	    float r = sqrt(x*x+y*y);
	    float p = atan2(y,x);  

	    // rastered
	    float rr = sqrt(xx*xx + yy*yy );
	    float pp = atan2( yy, xx );

	    while(p<0.0) p+=2.0*PI; 	    while(p>=2.0*PI) p-=2.0*PI; 
	    while(pp<0.0) pp+=2.0*PI; 	    while(pp>=2.0*PI) pp-=2.0*PI; 

	    // Cuts made on rastered value
	    if(rr<RMIN[d-1] || rr>RMAX[d-1]) continue;

	    // Strip numbers on rastered value
	    int  ir = int( MAXR*(rr-RMIN[d-1])/(RMAX[d-1]-RMIN[d-1]) );
	    int  ip = int( MAXPHI*pp/2.0/PI );
	    if ( MAXR ) assert(ir<MAXR);
	    if ( MAXPHI ) assert(ip<MAXPHI);

	    StRnDHit* ftshit=0;
	    if(_map[d-1][ir][ip]==0){ // New hit

	      if(verbose)	      LOG_INFO << Form("NEW d=%1d xyz=%8.4f %8.4f %8.4f r=%8.4f phi=%8.4f iR=%2d iPhi=%4d dE=%8.4f[MeV] truth=%d",
			       d,x,y,z,r,p,ir,ip,e*1000.0,t) <<endm;
	    count++;
		ftshit = new StRnDHit();
		ftshit->setDetectorId( kFtsId );
		ftshit->setLayer(d);
		float r0=RMIN[d-1] + (ir+0.5)*(RMAX[d-1]-RMIN[d-1])/float(MAXR);
		float p0=(ip+0.5)*2.0*PI/float(MAXPHI);
		float x0=r0*cos(p0) + xc;
		float y0=r0*sin(p0) + yc;
		float dr=(RMAX[d-1]-RMIN[d-1])/float(MAXR)/SQRT12;
		float dp=2.0*PI/float(MAXPHI)/SQRT12;
		float dz=0.2/SQRT12;
		ftshit->setPosition(StThreeVectorF(x0,y0,z));
		ftshit->setPositionError(StThreeVectorF(dr,dp,dz));
#if 0
		float dx = dr*TMath::Cos(pp) - r*dp*TMath::Sin(pp);
		float dy = dr*TMath::Sin(pp) + r*dp*TMath::Cos(pp);

		// Error matrix 
		float E[] = { dx*dx, dx*dy, 0.   ,
			      dx*dy, dy*dy, 0.   ,
			      0.,    0.,    dz*dz};
		

		ftshit->setErrorMatrix( E );
#endif
#if 1
                ftshit->setErrorMatrix(&Hack1to6(ftshit)[0][0]);
#endif

		ftshit->setCharge(e);
		ftshit->setIdTruth(t,100); 
		hits.push_back(ftshit);
		_map[d-1][ir][ip]= ftshit;
		enrsum[d-1][ir][ip]+=e; 		// Add energy to running sum
		enrmax[d-1][ir][ip]=e;                  // Set maximum energy 

	    }else{ // Adding energy to old hit
	      //	    LOG_INFO << Form("ADD d=%1d xyz=%8.4f %8.4f %8.4f r=%8.4f phi=%8.4f iR=%2d iPhi=%4d dE=%8.4f[MeV] truth=%d",
	      //			     d,x,y,z,r,p,ir,ip,e*1000.0,t) <<endm;

 		ftshit = _map[d-1][ir][ip];
		ftshit->setCharge(ftshit->charge() + e);

		// Add energy to running sum
		enrsum[d-1][ir][ip]+=e;
		double& E = enrmax[d-1][ir][ip];
		if ( e > E ) E = e;
		
		// keep idtruth but dilute it...
		t = ftshit->idTruth();

		ftshit->setIdTruth(t, 100* E / enrsum[d-1][ir][ip]);
	    }
	}
    }
    int nftshit=hits.size();
    
    // Loop over hits and digitize
    for(int i=0; i<nftshit; i++){	
	//hack! do digitization here, or more realistic smearing
	ftscollection->addHit(hits[i]);
    }
    if(verbose)    LOG_INFO << Form("Found %d/%d g2t hits in %d cells, created %d hits with ADC>0",count,nHits,nftshit,ftscollection->numberOfHits()) <<endm;
    //    ftscollection->print(1);
	for ( int id=0;id<NDISC;id++) {
		for ( int ir=0;ir<MAXR;ir++ ) {
			free(enrsum[id][ir]);
			free(enrmax[id][ir]); 
		}
	}
	for ( int id=0; id<NDISC;id++){
		free(enrmax[id]);
		free(enrsum[id]);
	}
	free(enrsum);
	free(enrmax);
//	
//	delete *_map;
//	delete enrmax;
//	delete enrsum;

}
//



long long encodeWire ( const int&   disk, 
		       const float& xGlobal, 
		       const float& yGlobal,
		       float& xLocal, 
		       float& yLocal,
                             float& xCenter,
 		             float& yCenter,
		             float& dxCenter, 
  		             float& dyCenter,
			     float& xPull,
			     float& yPull )
{

//  float xLocal, yLocal;

  //
  // min and max xlocal coordinates in each octant
  //
  //ftsref1/2  const float xmin[] = { 7.0,  7.0,  15.0, 15.0,  23.0, 23.0 }; 
  //ftsref1/2 const float xmax[] = { 37.0, 37.0, 75.0, 75.0, 113.0, 113.0 };

  /* ftsref3/4/5 */ const float xmin[] = { 6,6,6,6,6,6 };
  /* ftsref3/4/5 */ const float xmax[] = { 45.5, 45.5, 71.4, 71.4, 71.4, 71.4 };

  //
  // Map into octant local coordinates
  //

  float phiGlobal = TMath::ATan2( xGlobal, yGlobal );


  while ( phiGlobal <=             0. ) phiGlobal += TMath::TwoPi();
  while ( phiGlobal  > TMath::TwoPi() ) phiGlobal -= TMath::TwoPi();

  float rGlobal   = TMath::Sqrt( xGlobal*xGlobal + yGlobal*yGlobal );  

  //
  // Note note note note note -- ioctant may NOT be calculated correctly here
  //   ... octant zero covers [-pi/8,+pi/8] ...
  //
  //   ... so it looks like it is shifted by one half of an octant ...
  //

  int ioctant = 4 * ( phiGlobal ) / TMath::Pi(); // this is the octant number

  float phiLocal  = phiGlobal;

  while ( phiLocal  >  TMath::Pi() / 8.0 ) { phiLocal -= TMath::Pi() / 4.0; }
  while ( phiLocal <= -TMath::Pi() / 8.0 ) { phiLocal += TMath::Pi() / 4.0; }

  xLocal = rGlobal * TMath::Cos( phiLocal );
  yLocal = rGlobal * TMath::Sin( phiLocal );

  //
  // Check that xLocal is w/in the boundaries of the octant
  //
  if ( xLocal < xmin[disk-7] ) return -1;
  if ( xLocal > xmax[disk-7] ) return -2;


  //
  // Map into pad local coordinats and strip number
  //
  int   ipad = ( xLocal - xmin[disk-7] ) / 6.0;
  float xPad =   xLocal - xmin[disk-7]   - 6.0 * float(ipad);

  // Divide the octant into three phi bins... Should be 1, 0, -1
  int   iphi = (12.0 * phiLocal) / TMath::Pi();

  // Wire center in X ...
  float xPadLow = 6.0*ipad + xmin[disk-7]; 
  xCenter  = xPadLow + 3.0;
  dxCenter = 6.0 / SQRT12; 

  // Wire center in Y ...
  float yRowLow = -TMath::Tan( PI/8 ) * xPadLow;
  float yRowHi  = +TMath::Tan( PI/8 ) * xPadLow;
  if ( yLocal > yRowHi || yLocal < yRowLow ) {
     return -1; // Error condition 
  } 

  int iwire = ( yLocal - yRowLow ) / 0.15;
  yCenter = yRowLow + iwire * 0.15 + 0.075;
  dyCenter = 0.15 / SQRT12; 

  // Compute the pullz
  xPull = ( xLocal - xCenter ) / dxCenter;
  yPull = ( yLocal - yCenter ) / dyCenter; 

  // LOG_INFO << " xg="      << xGlobal
  // 	   << " yg="      << yGlobal
  // 	   << " phig="    << phiGlobal*TMath::RadToDeg()
  // 	   << " xl="      << xLocal
  // 	   << " yl="      << yLocal
  // 	   << " phil="    << phiLocal*TMath::RadToDeg()
  // 	   << " xpad="    << xPad
  // 	   << " ioctant=" << ioctant
  // 	   << " ipad="    << ipad
  // 	   << " iphi="    << iphi
  // 	   << " iwire="    << iwire
  // 	   << " xc="      << xCenter
  // 	   << " yc="      << yCenter
  // 	   << endm;

  xLocal = xCenter;
  yLocal = yCenter;
  
  // Now rotate back to global coordinates
  float dPhiToGlobal = ioctant * TMath::Pi() / 4;
  if ( dPhiToGlobal > 0 ) 
    {
      float X = xCenter;
      float Y = yCenter;

      xCenter = X * TMath::Cos(dPhiToGlobal) - Y * TMath::Sin(dPhiToGlobal);
      yCenter = X * TMath::Sin(dPhiToGlobal) + Y * TMath::Cos(dPhiToGlobal);

    }

  return 1000000*disk +  
          100000*ioctant +
           10000*ipad    +
                 iwire;


}

long long encodeStrip( const int&   disk, 
		       const float& xGlobal, 
		       const float& yGlobal,
		       float& xLocal,
		       float& yLocal,
                             float& xCenter,
 		             float& yCenter,
		             float& dxCenter, 
  		             float& dyCenter,
			     float& xPull,
			     float& yPull )
{

//  float xLocal, yLocal;


  //
  // min and max xlocal coordinates in each octant
  //
  //ftsref1/2  const float xmin[] = { 7.0,  7.0,  15.0, 15.0,  23.0, 23.0 }; 
  //ftsref1/2 const float xmax[] = { 37.0, 37.0, 75.0, 75.0, 113.0, 113.0 };

  /* ftsref3/4/5 */ const float xmin[] = { 6,6,6,6,6,6 };
  /* ftsref3/4/5 */ const float xmax[] = { 45.5, 45.5, 71.4, 71.4, 71.4, 71.4 };

  //
  // Map into octant local coordinates
  //

  float phiGlobal = TMath::ATan2( xGlobal, yGlobal );


  while ( phiGlobal <=             0. ) phiGlobal += TMath::TwoPi();
  while ( phiGlobal  > TMath::TwoPi() ) phiGlobal -= TMath::TwoPi();

  float rGlobal   = TMath::Sqrt( xGlobal*xGlobal + yGlobal*yGlobal );  

  int ioctant = 4 * ( phiGlobal ) / TMath::Pi(); // this is the octant number

  float phiLocal  = phiGlobal;

  while ( phiLocal  >  TMath::Pi() / 8.0 ) { phiLocal -= TMath::Pi() / 4.0; }
  while ( phiLocal <= -TMath::Pi() / 8.0 ) { phiLocal += TMath::Pi() / 4.0; }

  xLocal = rGlobal * TMath::Cos( phiLocal );
  yLocal = rGlobal * TMath::Sin( phiLocal );

  //
  // Check that xLocal is w/in the boundaries of the octant
  //
  if ( xLocal < xmin[disk-7] ) return -1;
  if ( xLocal > xmax[disk-7] ) return -2;


  //
  // Map into pad local coordinats and strip number
  //
  int   ipad = ( xLocal - xmin[disk-7] ) / 6.0;
  float xPad =   xLocal - xmin[disk-7]   - 6.0 * float(ipad);

  // Divide the octant into three phi bins... Should be 1, 0, -1
  int   iphi = (12.0 * phiLocal) / TMath::Pi();
  assert( iphi >= -1 );
  assert( iphi <=  1 );

  int   istrip = ( xPad ) / 0.3; // 3mm strip size
  float xStrip = istrip * 0.3 + 0.15;

  xCenter = xStrip + ipad*6.0 + xmin[disk-7];

  // Calculate width in y at xCenter and the X and Y errors
  float yWidth = 2.0 * xCenter * TMath::Tan( TMath::Pi() / 8.0 );

  dxCenter = 0.3        / SQRT12; // 3mm wide strip
  dyCenter = yWidth / 3 / SQRT12; // 1/3rd width of octant
      //Center = yWidth / 10.3923;

  // Finally, the center of the strip in Y
  float YCENTER[] = { -yWidth/3, 0, +yWidth/3 };
  yCenter = YCENTER[iphi+1];
    

  // LOG_INFO << " xg="      << xGlobal
  // 	   << " yg="      << yGlobal
  // 	   << " phig="    << phiGlobal*TMath::RadToDeg()
  // 	   << " xl="      << xLocal
  // 	   << " yl="      << yLocal
  // 	   << " phil="    << phiLocal*TMath::RadToDeg()
  // 	   << " xpad="    << xPad
  // 	   << " ioctant=" << ioctant
  // 	   << " ipad="    << ipad
  // 	   << " iphi="    << iphi
  // 	   << " istr="    << istrip
  // 	   << " xc="      << xCenter
  // 	   << " yc="      << yCenter
  // 	   << endm;


  xPull = ( xLocal - xCenter ) / dxCenter;
  yPull = ( yLocal - yCenter ) / dyCenter;

  xLocal = xCenter;
  yLocal = yCenter;

  // Now rotate back to global coordinates
  float dPhiToGlobal = ioctant * TMath::Pi() / 4;
  if ( dPhiToGlobal > 0 ) 
    {
      float X = xCenter;
      float Y = yCenter;

      xCenter = X * TMath::Cos(dPhiToGlobal) - Y * TMath::Sin(dPhiToGlobal);
      yCenter = X * TMath::Sin(dPhiToGlobal) + Y * TMath::Cos(dPhiToGlobal);

    }

  // Return a hash code 
  return 1000000*disk
    +     100000*ioctant // 8 octants
    +      10000*iphi    // 3 phibins
    +        100*ipad    // 14 pads
    +          1*istrip; // 20 strips

}



void StFtsFastSimulatorMaker::fillThinGapChambers(StEvent *event)
{
    // Read the g2t table
    St_g2t_fts_hit* hitTable = static_cast<St_g2t_fts_hit*>(GetDataSet("g2t_fts_hit"));
    if (!hitTable) {
	LOG_INFO << "g2t_fts_hit table is empty" << endm;
	return;  // Nothing to do
    }  // if

    // Stereo angle added at each detector plane
    const float stereo = 2*TMath::Pi() / 8 / 6;

    // hash tables to store hits in strips and wires / fast lookup for handling multiple hits
    std::map<long long, StRnDHit*> strip_hits;
    std::map<long long, StRnDHit*> wire_hits;
    std::map<long long, StRnDHit*> point_hits;

    
    // Prepare to loop over all hits
    const int nhits           = hitTable->GetNRows();
    const g2t_fts_hit_st* hit = hitTable->GetTable();

    for ( int i=0; i<nhits;  i++ )
      {
	hit = (g2t_fts_hit_st *)hitTable->At(i);    if ( 0==hit ) continue;

	float xhit = hit->x[0];
	float yhit = hit->x[1];
	float zhit = hit->x[2];
	int   disk = hit->volume_id;            if ( disk <=6 ) continue; // skip Si disks

	float alph = stereo * (disk-7);           // stereo angle at this sation

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

	octant     = globalToOctant( xhit, yhit, alph, xoctant, yoctant );
	phi_octant = TMath::ATan2( yoctant, xoctant );


	hGlobalYX->Fill( xhit, yhit );
	hOctantYX->Fill( xoctant, yoctant );



	//
	// Ensure we are within the x limits of the octant
	//
	if ( xoctant < OCTANT_XMIN[disk-7] ) continue;
	if ( xoctant > OCTANT_XMAX[disk-7] ) continue;


	//
	// Shift origin to the lower edge of the octant
	//
	float xshift = xoctant - OCTANT_XMIN[disk-7];
	float yshift = yoctant;

	//
	// Find padrow and column
	//
	pad = xshift / PAD_WIDTH;
	col = 1;
	if ( phi_octant >  PI/12 ) col = 2;
	if ( phi_octant < -PI/12 ) col = 0;

	LOG_INFO << Form("    pad=%02d col=%02d",pad,col) << endm;


	// Position relative to the start of the pad
	float xpad = xshift - float(pad)*PAD_WIDTH;

	// Position of the center of the pad in global coords
	float xpad_center = ( 0.5 + float(pad)) * PAD_WIDTH + OCTANT_XMIN[disk-7];
	// Position of the low edge of the pad in global coords
	float xpad_low    = (       float(pad)) * PAD_WIDTH + OCTANT_XMIN[disk-7];

	//////////////////////////////////////////////////////////////////////////////////
	//
	// Find the wire position and uncertainty
	//
	//////////////////////////////////////////////////////////////////////////////////

	// Calculate the x position of the wire and its error (easy)
	
	float xwire  = ( 0.5 + float(pad) ) * PAD_WIDTH; // middle of the pad rel. to octant start
	float exwire = PAD_WIDTH / SQRT12;

	// Wire x position in local global coordinates
	xwire += OCTANT_XMIN[disk-7];

	// Stop placing wires beyond the smaller pad width.

	float ylow  = -TMath::Tan( PI/8 ) * xpad_low; 
	float yhigh = +TMath::Tan( PI/8 ) * xpad_low;

	float ywire  = 0;
	float eywire = WIRE_SPACING / SQRT12;

	// Compute a wire number, and the wire position
	wire = (yoctant - ylow) / WIRE_SPACING;
	ywire = (float(wire)+0.50)*WIRE_SPACING + ylow;

	// Check that wire is in allowed range of phi
	float phi_wire = TMath::ATan2( ywire, xwire );
	if ( phi_wire > -PI/8 && phi_wire < PI/8 ) 
	  {

	// ywire can't be below low, but can be above high... wont be instrumented here, so...

	  float xwire_global, ywire_global;

	  float Ewire[] = {exwire*exwire, 
			   0.,             eywire*eywire};

	  assert( 0<eywire );
	  assert( 0<exwire );
	  
	  hOctantWireYX -> Fill( xwire, ywire );	   
	  
	  hWirePullsX  -> Fill( (xwire-xoctant) / exwire, float(disk-7) );
	  hWirePullsY  -> Fill( (ywire-yoctant) / eywire, float(disk-7) );
	  hWireDeltasX -> Fill( (xwire-xoctant)         , float(disk-7) );
	  hWireDeltasY -> Fill( (ywire-yoctant)         , float(disk-7) );
	  	  
	  octantToGlobal( xwire, ywire, octant, alph, xwire_global, ywire_global, Ewire );
	  
	  long long wire_key = wire + 1000*col + 10000*pad + 100000*octant;
	  
	  StRnDHit *wire_hit = wire_hits[ wire_key ];
	  if ( 0==wire_hit ) wire_hit = wire_hits[wire_key] = new StRnDHit();
	  
	  wire_hit -> setLayer( disk );
	  wire_hit -> setLadder( 1 );
	  wire_hit -> setWafer( octant );
	  
	  wire_hit -> setDetectorId( kFtsId );
	  wire_hit -> setPosition( {xwire_global, ywire_global, zhit-0.1f } );
	  wire_hit -> setPositionError( { exwire, eywire, 0.1f } );
	  
	  wire_hit -> setDouble0( xhit );
	  wire_hit -> setDouble1( yhit );
	  wire_hit -> setDouble2( xwire );
	  wire_hit -> setDouble3( ywire );
	  
	  wire_hit -> setIdTruth( hit->track_p,  wire_hit -> qaTruth() + 1 );
	
	  float Ewire_global[] = { Ewire[0], Ewire[1], 0.0f,
				 Ewire[1], Ewire[2], 0.0f,
				 0.0f,     0.0f,     0.1f };
	
	  wire_hit -> setErrorMatrix( Ewire_global );


	}

	//	    wire_hit -> Print();

	  
	
	



	//////////////////////////////////////////////////////////////////////////////////
	//
	// Find the strip position and uncertainty
	//
	//////////////////////////////////////////////////////////////////////////////////

	// 
	// strip number hit in the pad / x and y of the strip
	//
	strip = xpad / STRIP_WIDTH;
	
	// Position of the strip relative to the pad boundary
	float  xstrip = ( 0.5 + float(strip)) * STRIP_WIDTH;

	// Shift strip back to octant coordinates.  x is shifted.  y should remain the same
	xstrip += float(pad) * PAD_WIDTH + OCTANT_XMIN[disk-7];
	
	
	// Width of the octant at the strip	
	float dyoctant = 2.0 * xstrip * TMath::Tan( PI/8 );
	
	// Place y at the center of each column
	float ystrip  = float(1-col) * dyoctant / 3;

	// This is the strip's error matrix in octant local system
	float dystrip = dyoctant / 3;
	float dxstrip = STRIP_WIDTH;	       
	float Estrip[] = { dxstrip*dxstrip/12, 0., dystrip*dystrip/12 };

	// Rotate back to the global system
	float xstrip_global;
	float ystrip_global;

	hOctantStripYX -> Fill( xstrip, ystrip );
	
	hStripPullsX -> Fill( (xstrip-xoctant) / dxstrip * SQRT12, float(disk-7) );
	hStripPullsY -> Fill( (ystrip-yoctant) / dystrip * SQRT12, float(disk-7) );

	hStripDeltasX -> Fill( (xstrip-xoctant)                   , float(disk-7) );
	hStripDeltasY -> Fill( (ystrip-yoctant)                   , float(disk-7) );

	octantToGlobal( xstrip, ystrip, octant, alph, xstrip_global, ystrip_global, Estrip );
	
	long long key_strip = strip + 100*pad + 1000*col + 10000*octant + 100000*disk;

	StRnDHit *strip_hit = strip_hits[ key_strip ];
	if ( 0 == strip_hit ) strip_hit = strip_hits[key_strip] = new StRnDHit();

	strip_hit -> setLayer  (   disk ); // disk mapped to layer
	strip_hit -> setLadder (      0 ); // indicates a strip
	strip_hit -> setWafer  ( octant ); // octant number
	
	strip_hit -> setDetectorId( kFtsId );
	strip_hit -> setPosition( { xstrip_global, ystrip_global, zhit+0.1f } );
	strip_hit -> setPositionError ( { dxstrip/SQRT12, dystrip/SQRT12, 0.1f } );

	strip_hit -> setDouble0( xhit );
	strip_hit -> setDouble1( yhit );
	strip_hit -> setDouble2( xstrip );
	strip_hit -> setDouble3( ystrip );

	strip_hit -> setIdTruth( hit->track_p,  strip_hit -> qaTruth() + 1 );

	float Estrip_global[] = { Estrip[0], Estrip[1], 0.0f,
				  Estrip[1], Estrip[2], 0.0f,
				  0.0f,      0.0f,      0.1f };

	strip_hit -> setErrorMatrix( Estrip_global );

	//	strip_hit -> Print();
       
	if ( mPointHits ) { // combine xstrip and ywire into single point


	  LOG_INFO << " x: xoctant=" << xoctant
		   << "    xstrip=" << xstrip
		   << " y: yoctant=" << yoctant
		   << "    ywire=" << ywire
		   << endm;

	  float  x = xstrip;
	  float  y = ywire;
	  float dx = STRIP_WIDTH  / SQRT12;
	  float dy = WIRE_SPACING / SQRT12;
	  
	  float Ept[] ={ dx*dx, 0., dy*dy }; // returns from octantToGlobal a 2x2 triangular packed mtx

	  float xg, yg;

	  hPointsPullsX -> Fill(float(( x - xoctant ) /dx),float(disk-7));
	  hPointsPullsY -> Fill(float(( y - yoctant ) /dy),float(disk-7));

	  octantToGlobal( x, y, octant, alph, xg, yg, Ept );

	  float Eg[] = {
	    Ept[0], Ept[1], 0.f,
	    Ept[1], Ept[2], 0.f,
	    0.f,0,0.f, 0.1
	  };

	  StRnDHit *ahit = point_hits[ key_strip ];
	  if ( 0==ahit ) ahit = point_hits[key_strip] = new StRnDHit();

	  ahit->setPosition( { xg, yg, zhit } );
	  ahit->setPositionError( { dx, dy, 0.1 } );

	  ahit->setErrorMatrix( Eg ); 

	  ahit -> setDouble0( xhit );
	  ahit -> setDouble1( yhit );
	  ahit -> setDouble2( xstrip );
	  ahit -> setDouble3( ystrip );
	  ahit -> setLayer  (   disk ); // disk mapped to layer
	  ahit -> setLadder (      3 ); // indicates a point
	  ahit -> setWafer  ( octant ); // octant number

	  ahit -> setIdTruth( hit->track_p, 0 );
	  
	}
	
      }


    //
    // Normalize ID truth amd addd to hit collection
    //
    StRnDHitCollection* ftscollection = event->rndHitCollection();

    if ( 0 == mPointHits ) { // writeout wire and strip hits individually

      for ( auto& iter : strip_hits ) {
	auto* hit=iter.second;
	hit->setDetectorId( kFtsId );
	int id = hit->idTruth();
	int qa = 100 / hit->qaTruth();
	hit->setIdTruth( id, qa );
	if ( verbose ) hit->Print();
	ftscollection->addHit( hit );
      }
      for ( auto& iter : wire_hits ) {
	auto* hit=iter.second;
	hit->setDetectorId( kFtsId );
	int id = hit->idTruth();
	int qa = 100 / hit->qaTruth();
	hit->setIdTruth( id, qa );
	if ( verbose ) hit->Print();
	ftscollection->addHit( hit );
      }

    }
    else { // pointmaker-style hits
      for ( auto& iter : point_hits ) {
	auto* hit = iter.second;
	assert(hit); if (verbose) hit->Print();
	ftscollection->addHit(hit);
      }
    }


};

#if 0
void StFtsFastSimulatorMaker::fillThinGapChambers(StEvent *event)
{
    // Read the g2t table
    St_g2t_fts_hit* hitTable = static_cast<St_g2t_fts_hit*>(GetDataSet("g2t_fts_hit"));
    if (!hitTable) {
	LOG_INFO << "g2t_fts_hit table is empty" << endm;
	return;  // Nothing to do
    }  // if


    const float stereo = 2*TMath::Pi() / 8 / 6;

    
    std::map<long long, StRnDHit*> strip_hits;
    std::map<long long, StRnDHit*> wire_hits;

    const Int_t nHits = hitTable->GetNRows();
    LOG_DEBUG << "g2t_fts_hit table has " << nHits << " hits" << endm;
    const g2t_fts_hit_st* hit = hitTable->GetTable();
    //    StPtrVecFtsHit hits; //temp storage for hits    
    int count = 0; 
    for (Int_t i=0; i < nHits; ++i) {
      hit = (g2t_fts_hit_st *)hitTable->At(i);
	if (hit) {
            int   d = hit->volume_id; 
	    if ( d <= 6 ) continue; // skip small disks

	    float xhit = hit->x[0];
	    float yhit = hit->x[1];
	    float zhit = hit->x[2];

	    float xstrip, ystrip, exstrip, eystrip;
	    float xwire, ywire, exwire, eywire;

	    float xspull, yspull, xwpull, ywpull ; 
	    float xslocal, yslocal, xwlocal, ywlocal; 

	    //
	    // Rotate gloabl hits by stereo angle
	    //
	    float alpha = stereo * (d-7);

	    float xstereo = xhit * TMath::Cos( alpha )  - yhit * TMath::Sin( alpha );
	    float ystereo = xhit * TMath::Sin( alpha )  + yhit * TMath::Cos( alpha );

            long long xkey = encodeStrip( d, xstereo, ystereo, xslocal, yslocal, xstrip, ystrip, exstrip, eystrip, xspull, yspull );
	    long long ykey = encodeWire ( d, xstereo, ystereo, xwlocal, ywlocal, xwire,  ywire,  exwire,  eywire,  xwpull, ywpull );

	    //
	    // Rotate encoded hits back by stereo angle
	    //
	    {
	      float xs = xstrip * TMath::Cos( -alpha ) - ystrip * TMath::Sin( -alpha );
	      float ys = ystrip * TMath::Sin( -alpha ) + ystrip * TMath::Cos( -alpha );
	      xstrip = xs; 
	      ystrip = ys;

	      float xw = xwire * TMath::Cos( -alpha ) - ywire * TMath::Sin( -alpha );
	      float yw = ywire * TMath::Sin( -alpha ) + ywire * TMath::Cos( -alpha );
	      xwire = xw; 
	      ywire = yw;
	    }

	    if ( xkey > 0 ) {

	      StRnDHit* xh = (merge_hits)? strip_hits[ xkey ] : 0;
	      if ( 0 == xh ) { xh = strip_hits[xkey] = new StRnDHit();}
	      xh->setLayer(d);
	      xh->setPosition(       StThreeVectorF(  xstrip,  ystrip, zhit-0.1 ) );
	      xh->setPositionError(  StThreeVectorF( exstrip, eystrip, 0.1 ) );
	      xh->setCharge( hit->de + xh->charge() );
	      xh->setIdTruth( hit->track_p,  xh-> qaTruth() + 1 );
	      xh->setDouble0( xhit );
	      xh->setDouble1( yhit );
	      //xh->setDouble2( zhit );
	      xh->setDouble3( xslocal ); 
	      xh->setDouble4( yslocal ); 
	      xh->setLadder(0); 
	      xh->setExtraByte0( xkey );

	      hStripDeltasX -> Fill( xspull*exstrip, d-6 );
	      hStripDeltasY -> Fill( yspull*eystrip, d-6 );
	      
	      hStripPullsX -> Fill( xspull, d-6 );
	      hStripPullsY -> Fill( yspull, d-6 );

	    };
 


	    if ( ykey > 0 ) {

	      StRnDHit* yh = (merge_hits)? wire_hits[ ykey ] : 0;
	      if ( 0 == yh ) { yh = wire_hits[ykey] = new StRnDHit(); }
	      yh->setLayer(d);
	      yh->setPosition(       StThreeVectorF(  xwire,  ywire, zhit+0.1 ) );
	      yh->setPositionError(  StThreeVectorF( exwire, eywire, 0.1 ) );
	      yh->setCharge( hit->de + yh->charge() );
	      yh->setIdTruth( hit->track_p,  yh-> qaTruth() + 1 );
	      yh->setDouble0( xhit );
	      yh->setDouble1( yhit );
	      //yh->setDouble2( zhit );
	      yh->setDouble3( xwlocal );
	      yh->setDouble4( ywlocal ); 
	      yh->setLadder(1); 
	      yh->setExtraByte0( ykey );
	      
	      hWireDeltasX -> Fill( xwpull*exwire, d-6 );
	      hWireDeltasY -> Fill( ywpull*eywire, d-6 );
	      
	      hWirePullsX -> Fill( xwpull, d-6 );
	      hWirePullsY -> Fill( ywpull, d-6 );
	      
	    }


	}
    }

    //
    // Normalize ID truth amd addd to hit collection
    //
    //    StFtsHitCollection * ftscollection = event->ftsCollection();
    StRnDHitCollection* ftscollection = event->rndHitCollection();
     for ( auto& iter : strip_hits ) {
       auto* hit=iter.second;
       hit->setDetectorId( kFtsId );
       int id = hit->idTruth();
       int qa = 100 / hit->qaTruth();
       hit->setIdTruth( id, qa );
       if ( verbose ) hit->Print();
       ftscollection->addHit( hit );
     }
    for ( auto& iter : wire_hits ) {
      auto* hit=iter.second;
      hit->setDetectorId( kFtsId );
      int id = hit->idTruth();
      int qa = 100 / hit->qaTruth();
      hit->setIdTruth( id, qa );
      if ( verbose ) hit->Print();
      ftscollection->addHit( hit );
    }


}
#endif
//_____________________________________________________________________________
StMatrixF  Hack1to6(const StHit *stHit)
{
//  X = R*cos(Fi), Y=R*sin(Fi), Z = z   
//   dX/dR  = (    cos(Fi)  ,sin(Fi),0)
//   dX/dFi = (-R*sin(Fi), R*cos(Fi),0)
//   dX/dZ  = (         0,         0,1)

  auto  hiPos = stHit->position();   
  auto  hiErr = stHit->positionError();   
  double Rxy = sqrt(hiPos[0]*hiPos[0]+hiPos[1]*hiPos[1]);
  double cosFi = hiPos[0]/Rxy;   
  double sinFi = hiPos[1]/Rxy;   
  double T[3][3] = {{cosFi,-Rxy*sinFi,0}
                   ,{sinFi, Rxy*cosFi,0}
                   ,{    0,         0,1}};
  double Ginp[6] = { hiErr[0]*hiErr[0]
                   ,                0,hiErr[1]*hiErr[1]
		   ,                0,                0,hiErr[2]*hiErr[2]};
  double Gout[6];		   
		   
  TCL::trasat(T[0],Ginp,Gout,3,3);
  StMatrixF mtxF(3,3);

  for (int i=0,li=0;i< 3;li+=++i) {
     for (int j=0;j<=i;j++) {mtxF[i][j] = Gout[li+j]; mtxF[j][i] = mtxF[i][j];}}
     
  return mtxF;
}
#endif 
