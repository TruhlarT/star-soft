// $Id: StFtsFastSimulatorMaker.h,v 1.1.2.3 2018/06/07 16:18:49 jwebb Exp $
//
// $Log: StFtsFastSimulatorMaker.h,v $
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
#if 0 
#ifndef ST_FTS_SIMULATOR_MAKER_H
#define ST_FTS_SIMULATOR_MAKER_H

class g2t_emc_hit_st;
class StFtsHit;
class StEvent; 

#include "StChain/StMaker.h"
#include <vector>

#include "TH1F.h"
#include "TH2F.h"

class StRnDHit;


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

  void setPointHits(){ mPointHits = true; }

 private:
  Int_t getDetectorId(const g2t_emc_hit_st& hit) const;

  void fillSilicon(StEvent* event);
  void fillThinGapChambers(StEvent *event);

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
  //table to keep pointer to hit for each disc, r & phi strips
 // StRnDHit* _map[6][64][1536];
//  double enrsum[6][64][1536]; 
 // double enrmax[6][64][1536]; 
    
  

  //   ClassDef(StFtsFastSimulatorMaker, 0)
};

inline const char* StFtsFastSimulatorMaker::GetCVS() const {
  static const char cvs[]="Tag $Name:  $ $Id: StFtsFastSimulatorMaker.h,v 1.1.2.3 2018/06/07 16:18:49 jwebb Exp $ built " __DATE__ " " __TIME__ ;
  return cvs;
}

#endif 
#endif
