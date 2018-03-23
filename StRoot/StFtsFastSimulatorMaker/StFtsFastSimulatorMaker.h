// $Id: StFtsFastSimulatorMaker.h,v 1.1.2.2 2018/03/23 17:12:55 jwebb Exp $
//
// $Log: StFtsFastSimulatorMaker.h,v $
// Revision 1.1.2.2  2018/03/23 17:12:55  jwebb
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
// Revision 1.10  2017/01/17 16:25:33  jwebb
// Runtime configuration of min/max radii for Si disks.
//
// Runtime switch to enable / disable hit ambiguities in the sTGC wheels.
//
// Revision 1.9  2016/12/22 19:55:04  jwebb
// Code cleanup.  Bug fix for multiple hits on wires (keys were duplicated).  Emulation of point finding.  Error matrices computed correctly for both Si disks and sTGC wheels.
//
// Revision 1.8  2016/12/09 16:15:17  jwebb
// Option to disable / enable individual disks.
//
// Revision 1.7  2016/12/06 21:45:52  jwebb
// Add pseudo point finder
//
// Revision 1.6  2016/12/06 19:25:41  jwebb
// Rewrite of sTGC wheels.
//
// Revision 1.5  2016/11/28 22:52:04  jwebb
// Added QA / fixed errors
//
// Revision 1.4  2016/11/23 16:06:07  jwebb
// Add thin gap chamber digitization to the simulator.  This version hardcodes the z-positions of the detectors.
//
// Revision 1.3  2015/11/25 22:18:32  jwebb
// Code to raster the position of the disks.
//
// Revision 1.2  2015/10/20 21:48:57  jwebb
// Updated FTS simulator to allow runtime configuration of pixels divisions.
//
// Revision 1.1  2015/10/16 15:22:50  jwebb
// Offline area established for STAR upgrades
//
//

#ifndef ST_FTS_SIMULATOR_MAKER_H
#define ST_FTS_SIMULATOR_MAKER_H

class g2t_emc_hit_st;
class StFtsHit;
class StEvent; 

#include "StChain/StMaker.h"
#include <vector>

#include "TH1F.h"
#include "TH2F.h"


class StFtsFastSimulatorMaker : public StMaker {
 public:
  explicit StFtsFastSimulatorMaker(const Char_t* name = "ftsSim");
  virtual ~StFtsFastSimulatorMaker() { }
  Int_t Make();
  int   Init();
  virtual const char* GetCVS() const;
  /// Define segmentation
  void setPixels( int numR=8, int numSec=12, int numPhi=128 ) { mNumR=numR;  mNumSEC=numSec; mNumPHI=numPhi; }
  /// Set offset for each disk ( x=R*cos(idisk*60 degrees), y=R*sin(...) )
  void setRaster( float R = 1.0 ){ mRaster = R; }
  /// Set min/max active radii for each disk
  void setDisk( const int i, const float rmn, const float rmx );
  /// Set even spacing in eta (defaults to even in r)
  void setConstEta(){ mConstEta = true; }
  

  /// Enable / disable specified disk (disks counted from 1)
  void setActive( const int disk, const bool flag=true ){ mEnable[disk-1] = flag; }
  /// Point making in each pad (strip,wire)-->(x,y)
  void setPointHits(){ mPointHits = true; }

  void setStripWidth( const float width=0.3 ){ mStripWidth=width; }
  void setWireSpacing( const float space=0.15 ){ mWireSpacing=space; }
  void setWindow( const float window=3.0 ){ mWindow=window; }

  void setStereo( const float stereo=2*TMath::Pi() / 8 / 6 ) { mStereo=stereo; }

  void setStagger( const float stagger=3.0 ){ mStagger = 3.0; }

  void setAmbiguity( const bool a=true ){ mAmbiguity = a; }
  
 private:
  Int_t getDetectorId(const g2t_emc_hit_st& hit) const;

  void fillSilicon(StEvent* event);
  void fillThinGapChambers(StEvent *event);

  bool mEnable[12];

  int mNumR;
  int mNumPHI;
  int mNumSEC;
  float mRaster;

  TH2F* hGlobalYX;
  TH2F* hOctantYX;

  TH2F* hOctantWireYX;
  TH2F* hOctantStripYX;


  TH2F* hWireDeltasX;
  TH2F* hWireDeltasY;
  TH2F* hStripDeltasX;
  TH2F* hStripDeltasY;

  TH2F* hWirePullsX;
  TH2F* hWirePullsY;
  TH2F* hStripPullsX;
  TH2F* hStripPullsY;

  TH2F* hPointsPullsX;
  TH2F* hPointsPullsY;

  bool mPointHits;
  bool mAmbiguity;


  
  float mStripWidth;
  float mWireSpacing;
  float mWindow; // for filtering combinatorics
  float mStereo;
  float mStagger;

  bool mConstEta;

  ClassDef(StFtsFastSimulatorMaker, 0)
};

inline const char* StFtsFastSimulatorMaker::GetCVS() const {
  static const char cvs[]="Tag $Name:  $ $Id: StFtsFastSimulatorMaker.h,v 1.1.2.2 2018/03/23 17:12:55 jwebb Exp $ built " __DATE__ " " __TIME__ ;
  return cvs;
}

#endif 
