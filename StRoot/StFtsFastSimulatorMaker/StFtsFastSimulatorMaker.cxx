// $Id: StFtsFastSimulatorMaker.cxx,v 1.1.2.2 2018/03/23 17:12:53 jwebb Exp $                                            
//                                                                                                                     
// $Log: StFtsFastSimulatorMaker.cxx,v $
// Revision 1.1.2.2  2018/03/23 17:12:53  jwebb
// Previous versions of the simulator were used for the initial studies of
// forward tracking.  This commit updates to a more recent version, with a
// more correct implementation of the thin gap chambers.  Main differences
// relate to
//
// FTS Si Disk Simulation
//
// 1) The inner and outer radii of sensitive area for the Si disks is now
//    a run-time, rather than compile time, parameter
//
// 2) Option is added to segment the disks with constant-eta, rather than
//    constant-r, strips.
//
// 3) Individual disks may be enabled / disabled at run time.
//
// 4) ID truth is determined by the last particle which hits the strip,
//    previously by the first.
//
// FTS sTGC Wheel Simulation
//
// 1) Wire and strip pitch configurable at run time.
//
// 2) Bug fix for multiple hits to strips and wires
//
// 3) Implementation of "ghost" hits... i.e. sTGC hits are defined by the
//    intersection of struck wires and strips.  Hit multiplicity in each
//    pad creates 2^n hits, which are now accounted for.
//
// Revision 1.20  2017/01/17 16:25:33  jwebb
// Runtime configuration of min/max radii for Si disks.
//
// Runtime switch to enable / disable hit ambiguities in the sTGC wheels.
//
// Revision 1.19  2016/12/22 19:55:04  jwebb
// Code cleanup.  Bug fix for multiple hits on wires (keys were duplicated).  Emulation of point finding.  Error matrices computed correctly for both Si disks and sTGC wheels.
//
// Revision 1.18  2016/12/09 15:48:56  jwebb
// Added option to switch off digitization of specified disks and wheels.
//
// Revision 1.17  2016/12/07 21:16:44  jwebb
// Corrected y-error error
//
// Revision 1.16  2016/12/07 21:14:57  jwebb
// Added compile-time option to allow for ambiguities (wire chamber problem)
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
//

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
#include <vector>
#include "TCanvas.h"
#include "TH2F.h"
#include "TLine.h" 
#include "TVector3.h"
#include "TCernLib.h"
#include "TString.h"

//
// Wheel segmentation 
//
//efine __NO_AMBIGUITY__

TCanvas *canvas = 0;
StMatrixF  Hack1to6(const StHit *stHit);

constexpr float PI     = atan2(0.0,-1.0);
constexpr float SQRT12 = sqrt(12.0);

const float fudge_error = 1.0;

const float OCTANT_WIDTH_PHI        = PI/4;
const float OCTANT_GLOBAL_PHI_MIN[] = {-PI/8, PI/8, 3*PI/8, 5*PI/8, 7*PI/8, 9*PI/8, 11*PI/8, 13*PI/8};
const float OCTANT_GLOBAL_PHI_MAX[] = {       PI/8, 3*PI/8, 5*PI/8, 7*PI/8, 9*PI/8, 11*PI/8, 13*PI/8, 15*PI/8};

      float OCTANT_XMIN[] = {  6.0f,  6.0f,  6.0f,  6.0f,  6.0f,  6.0f }; // octant size in each disk... 
      float OCTANT_XMAX[] = { 42.0f, 42.0f, 66.0f, 66.0f, 66.0f, 66.0f };

const float PAD_WIDTH    = 6.0f;
const float STRIP_WIDTH  = 0.3f;   // must divide nicly into 6cm
const float WIRE_SPACING = 0.15f;  // ditto


//
// Disk segmentation
//
float RMIN[] = {   0.85*2.56505,   0.85*3.41994,   0.85*4.27484,  0.85*5.13010, 0.85*5.985, 0.85*6.83988 };
float RMAX[] = {  1.15*11.56986,  1.15*15.42592,  1.15*19.28199, 1.15*23.13971, 1.15*26.99577, 1.15*30.84183 };


void StFtsFastSimulatorMaker::setDisk( const int i, const float rmn, const float rmx )
{
  RMIN[i] = rmn;
  RMAX[i] = rmx;
}

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
    mEnable({true,true,true,true,true,true,true,true,true,true,true,true}),
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
    mPointHits(false),
    mAmbiguity(true),
    mStripWidth(0.3),
    mWireSpacing(0.15),
    mWindow(3.0),
    mStereo(2*TMath::Pi() / 8 / 6),
    mStagger(0.0),
    mConstEta(false)
{}


int StFtsFastSimulatorMaker::Init()
{

  // Stagger the pads in every other wheel
  for ( auto i : { 2, 4, 6 } )
    {
      OCTANT_XMIN[i] -= mStagger;
      OCTANT_XMAX[i] += mStagger;
    }

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
    fillThinGapChambers(event);

    return kStOk;
}

/* Fill an event with StFtsHits. */
/* This should fill StFtsStrip for realistic simulator and let clustering fill StFtsHit */
/* For now skipping StFtsStrip and clustering, and fill StFtsHits directly here*/




void StFtsFastSimulatorMaker::fillSilicon(StEvent* event) {

  //    StFtsHitCollection * ftscollection = event->ftsCollection();    
  StRnDHitCollection* ftscollection = event->rndHitCollection();

  static const int NDISC=6;    
  //static const int MAXR  =128; // JCW: let's give Stv best shot at this possible...
  //static const int MAXPHI=128*12;      
  static const int MAXR   = mNumR;
  static const int MAXPHI = mNumPHI * mNumSEC;


    
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


  // Constant eta segmentation
  static const float etaMn = 2.5;
  static const float etaMx = 4.0;
  static const float thetaMn = 2.0 * TMath::ATan( TMath::Exp(-etaMx) );
  static const float thetaMx = 2.0 * TMath::ATan( TMath::Exp(-etaMn) );
  static const int   nbins = MAXR;
  static const float deta = (etaMx - etaMn)/nbins; 


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
		enrmax[id][ir][ip]=-999; 
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
	    if ( false == mEnable[d-1] ) continue; // disk switched off

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

            // compute point eta 
            float theta =  TMath::ATan2(rr,z); // rastered eta
            float eta   = -TMath::Log( TMath::Tan(theta/2) ); 

	    // Cuts made on rastered value
	    if(rr<RMIN[d-1] || rr>RMAX[d-1]) continue;

	    // Strip numbers on rastered value 
	    int  ir = int( MAXR*(rr-RMIN[d-1])/(RMAX[d-1]-RMIN[d-1]) );
	    // Phi number
	    int  ip = int( MAXPHI*pp/2.0/PI );
	    
	    // Guard against out-of-bounds on constant eta binning
	    if ( mConstEta ) {
	      if ( eta < etaMn ) continue;
	      if ( eta > etaMx ) continue;
	    }

	    // Strip numbers on rastered value (eta)
	    int ieta = int( nbins *(eta - etaMn)/(etaMx - etaMn) );



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

	      //
	      // Set position and position error based on radius-constant bins
	      //
	      float p0=(ip+0.5)*2.0*PI/float(MAXPHI);
	      float dp=2.0*PI/float(MAXPHI)/SQRT12;
	      if ( false == mConstEta ) {
		float r0=RMIN[d-1] + (ir+0.5)*(RMAX[d-1]-RMIN[d-1])/float(MAXR);
		float dr=(RMAX[d-1]-RMIN[d-1])/float(MAXR);       		
		float x0=r0*cos(p0) + xc;
		float y0=r0*sin(p0) + yc;
		assert( TMath::Abs(x0)+TMath::Abs(y0) > 0 );
		float dz=0.2/SQRT12;
		float er = dr/SQRT12;
		ftshit->setPosition(StThreeVectorF(x0,y0,z));
		ftshit->setPositionError(StThreeVectorF(er,dp,dz));
	      }
	      //
	      // Set position and error based on eta-constant bins
	      //
	      else {

		float thMn = 2.0 * TMath::ATan( TMath::Exp(-(etaMn+(ieta+1)*deta)) );
		float thMx = 2.0 * TMath::ATan( TMath::Exp(-(etaMn+(ieta+0)*deta)) );
		float rrMn = z * TMath::Tan(thMn); // rastered r-min
		float rrMx = z * TMath::Tan(thMx); // rastered r-max

		if ( rr < rrMn || rr > rrMx ) {	
		  LOG_INFO << Form("NEW d=%1d xyz=%8.4f %8.4f %8.4f r=%8.4f rr=%8.4f phi=%8.4f eta=%8.4f iR=%2d iPhi=%4d iEta=%2d dE=%8.4f[MeV] truth=%d",  d,x,y,z,r,rr,p,eta,ir,ip,ieta,e*1000.0,t) <<endm;	
		  LOG_INFO << "rrMn = " << rrMn << endm;
		  LOG_INFO << "rrMx = " << rrMx << endm;
		  assert(0);
		};
		
		float r0 = (rrMn + rrMx) * 0.5; // rastered position
		float x0=r0*cos(p0) + xc; // deraster the position
		float y0=r0*sin(p0) + yc;
		float dz=0.2/SQRT12;
		float dr = rrMx - rrMn;
		float er = dr/SQRT12;
		ftshit->setPosition(StThreeVectorF(x0,y0,z));
		ftshit->setPositionError(StThreeVectorF(er,dp,dz));

	      }

	      ftshit->setErrorMatrix(&Hack1to6(ftshit)[0][0]);
	      
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

}
//




void StFtsFastSimulatorMaker::fillThinGapChambers(StEvent *event)
{
    // Read the g2t table
    St_g2t_fts_hit* hitTable = static_cast<St_g2t_fts_hit*>(GetDataSet("g2t_fts_hit"));
    if (!hitTable) {
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

    for ( int i=0; i<nhits;  i++ )
      {
	hit = (g2t_fts_hit_st *)hitTable->At(i);    if ( 0==hit ) continue;

	float xhit = hit->x[0];
	float yhit = hit->x[1];
	float zhit = hit->x[2];
	int   disk = hit->volume_id;            if ( disk <=6 ) continue; // skip Si disks

	LOG_DEBUG << "wheel hit " << disk << " x=" << xhit << " y=" << yhit << " z=" << zhit << endl;

	if ( false == mEnable[disk-1] ) continue; // disk switched off

	float alph = mStereo * (disk-7);           // stereo angle at this sation

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

//	LOG_INFO << Form("    pad=%02d col=%02d",pad,col) << endm;


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
	float eywire = mWireSpacing / SQRT12;

	// Compute a wire number, and the wire position
	wire = (yoctant - ylow) / mWireSpacing;
	ywire = (float(wire)+0.50)*mWireSpacing + ylow;

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
	  
	  //	  long long wire_key = wire + 1000*col + 10000*pad + 100000*octant;

	  long long wire_key =
	    disk   /* 1-12 */          +
	    octant /* 0-7  */  *100    +
	    pad    /* 0-5  */  *1000   +
	    col    /* 0-2  */  *10000  +
	    wire   /* large */ *100000 ;
	  
	  StRnDHit *wire_hit = wire_hits[ wire_key ];
	  if ( 0==wire_hit ) 
	    {
	      wire_hit = wire_hits[wire_key] = new StRnDHit();
	      wire_hits_vec[ disk-7 ][ octant ][ col ][ pad ].push_back( wire_hit );
	    }
	  else 
	    {
	      float zold = wire_hit->position()[2] + 0.1f;
	      if ( TMath::Abs( zold - zhit ) > 0.1 ) {
		LOG_WARN << "Wrong wheel for double hit wire: zold=" << zold << " znew=" << zhit << endm;
		LOG_WARN << disk << endm;
		LOG_WARN << octant << endm;
		LOG_WARN << pad << endm;
		LOG_WARN << wire << endm;
		LOG_WARN << wire_key << endm;
	      }
	    }
	  
	  wire_hit -> setLayer( disk );
	  wire_hit -> setLadder( wire );
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


	  //	  wire_hits_vec[ octant ][ col ][ pad ].push_back( wire_hit );


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
	strip = xpad / mStripWidth;
	
	// Position of the strip relative to the pad boundary
	float  xstrip = ( 0.5 + float(strip)) * mStripWidth;

	// Shift strip back to octant coordinates.  x is shifted.  y should remain the same
	xstrip += float(pad) * PAD_WIDTH + OCTANT_XMIN[disk-7];
	
	
	// Width of the octant at the strip	
	float dyoctant = 2.0 * xstrip * TMath::Tan( PI/8 );
	
	// Place y at the center of each column
	float ystrip  = float(1-col) * dyoctant / 3;

	// This is the strip's error matrix in octant local system
	float dystrip = dyoctant / 3;
	float dxstrip = mStripWidth;	       
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
	
	//	long long key_strip = strip + 1000*pad + 100000*col + 10000000*octant + 10000000000*disk;

	long long key_strip = 
	  disk   /* 1-12 */          +
	  octant /* 0-7  */  *100    +
	  pad    /* 0-5  */  *1000   +
	  col    /* 0-2  */  *10000  +
	  strip  /* large */ *100000 ;

	StRnDHit *strip_hit = strip_hits[ key_strip ];
	if ( 0 == strip_hit ) 
	  { 
	    strip_hit = strip_hits[key_strip] = new StRnDHit();
	    strip_hits_vec[ disk-7 ][ octant ][ col ][ pad ].push_back( strip_hit );
	  }
	else 
	  {
	    float zold = strip_hit->position()[2] - 0.1f;
	    if ( TMath::Abs( zold - zhit ) > 0.1 ) {
	      LOG_WARN << "Wrong wheel for double hit strip: zold=" << zold << " znew=" << zhit << endm;
	      LOG_WARN << disk << endm;
	      LOG_WARN << octant << endm;
	      LOG_WARN << pad << endm;
	      LOG_WARN << strip << endm;
	      LOG_WARN << key_strip << endm;
	    }
	  }
	  

	strip_hit -> setLayer  (   disk ); // disk mapped to layer
	strip_hit -> setLadder (  strip ); // indicates a strip
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

	//	strip_hits_vec[ octant ][ col ][ pad ].push_back( strip_hit );
	

	//#ifdef __NO_AMBIGUITY__
	if ( 0==mAmbiguity ) {
	if ( mPointHits ) { // combine xstrip and ywire into single point

	  LOG_INFO << " x: xoctant=" << xoctant
		   << "    xstrip=" << xstrip
		   << " y: yoctant=" << yoctant
		   << "    ywire=" << ywire
		   << endm;

	  float  x = xstrip;
	  float  y = ywire;
	  float dx = mStripWidth  / SQRT12;
	  float dy = mWireSpacing / SQRT12;
	  
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


	  //
	  // NOTE -- not sure at all that this logic is correct... but maybe we
	  // don't use it... combinatorics look like thay are handled below...
	  //
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
	//#endif
	
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
    //#ifdef __NO_AMBIGUITY__
    else if ( 0==mAmbiguity ) { // pad-like hits
      for ( auto& iter : point_hits ) {
	auto* hit = iter.second;
	assert(hit); if (verbose) hit->Print();
	ftscollection->addHit(hit);
      }
    }


    // Points have been generated
    if ( 0 == mAmbiguity ) 
      {
	return;
      }

    //#else
    //
    // handle combinatoric hits in pads (no
    //
    for ( int wheel = 0; wheel < 6; wheel++ )
      for ( int octant = 0; octant < 8; octant++ )
	for ( int column = 0; column < 3; column++ )
	  for ( int row = 0; row < 10; row++ )
	    {

	      const auto& strips = strip_hits_vec[wheel][octant][column][row];
	      const auto& wires  =  wire_hits_vec[wheel][octant][column][row];

	      for ( auto* shit : strips ) 
		for ( auto* whit : wires ) 
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
		    //		    float z = (spos[2]+wpos[2])*0.5;
		    float zw = wpos[2];
		    float zs = spos[2];
		    if ( TMath::Abs(zw-zs)>1.0 ) 
		      {
			LOG_INFO << "Strip and wire from different z locations WTF? " << zw << " " << zs << " " << whit->layer() << " " << shit->layer() << endm;
			shit->Print();
			whit->Print();	
			continue; // sweep under da rug...
		      }
		    float z = ( zw + zs ) * 0.5;
		    

		    float ex = serr[0] * fudge_error;
		    float ey = werr[1] * fudge_error;
		    float ez = 1.0;

		    float Ematrix[] = {
		      ex*ex ,
		      0.0f  , ey*ey 
		    };

		    float xg, yg;
		    octantToGlobal( x, y, octant, mStereo*wheel, xg, yg, Ematrix );

		    float Eglobal[] = {
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
		    ahit->setLayer( wheel+7 );				    
		    ahit->setLadder( octant ); // strip number
		    ahit->setWafer ( 10*row + column ); // wire number
		    ahit->setExtraByte2( strip );
		    ahit->setExtraByte3( wire );

		    ahit->setPosition( { xg, yg, z } );
		    ahit->setPositionError( { ex, ey, ez } );
		    ahit->setErrorMatrix( Eglobal );

		    if ( shit->idTruth() == whit->idTruth() )
		      {
			ahit->setIdTruth( shit->idTruth(), 100 );
		      }
		    else 
		      {
			ahit->setIdTruth( 0, 0 );
		      }

		    ahit->setExtraByte0( shit->idTruth() );
		    ahit->setExtraByte1( whit->idTruth() );
		    


		    

		    point_hits_by_wheel[ wheel ].push_back( ahit );

		    //		    ftscollection->addHit(ahit);
		    //		    ahit->Print();

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
    for ( int i=0; i<6; i++ ) {
    
    for ( auto& hit1 : point_hits_by_wheel[ wheel1[i] ] ) 
      {
	hit_count_total++;

	// hit already added
	if ( 0 != point_accumulator[ hit1 ] ) continue;

	float xh1 = hit1->position()[0];
	float yh1 = hit1->position()[1];
	float zh1 = hit1->position()[2];

	float dx1 = hit1->covariantMatrix()(1,1);
	float dy1 = hit1->covariantMatrix()(2,2);
	
	float dxdz = (xh1 - xv)/(zh1 - zv); // slope in x from vtx
	float dydz = (yh1 - yv)/(zh1 - zv); // slope in y from vtx

	for ( auto& hit2 : point_hits_by_wheel[ wheel2[i] ] )
	  {

	    float xh2 = hit2->position()[0];
	    float yh2 = hit2->position()[1];
	    float zh2 = hit2->position()[2];
	    
	    float xpred = dxdz * ( zh2 - zv ); // str8 line from first to second plane
	    float ypred = dydz * ( zh2 - zv ); // str8 line from first to second plane
	    
	    if ( TMath::Abs( xpred - xh2 ) > window * dx1 ) continue;
	    if ( TMath::Abs( ypred - yh2 ) > window * dy1 ) continue;

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
    for ( auto& iter : point_accumulator ) 
      {
	hit_count_filt++;
	ftscollection->addHit( iter.first );
	
      };
    

    LOG_INFO << "Filtered FTS wheel htis:  " << hit_count_filt << endm;
    LOG_INFO << "Total FTS: " << ftscollection->numberOfHits() << endm;


    //#endif


};


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
