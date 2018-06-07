#ifndef ST_FTS_FAST_SI_SIMULATOR_MAKER_H
#define ST_FTS_FAST_SI_SIMULATOR_MAKER_H

class StEvent; 
class StRnDHit;
class StRnDHitCollection;
class g2t_fts_hit_st;

struct stripPos_t
{
  int iPN; //back 0 // front 1 
  float x1;// low left
  float y1;// low left
  float x2;// uper right
  float y2;// uper right
};

#include "StMaker.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"

class StFtsSiFastSimulatorMaker : public StMaker {

public:
  explicit  StFtsSiFastSimulatorMaker( const char* name="ftssifastsim" );
  virtual  ~StFtsSiFastSimulatorMaker(){ /* nada */ }

  int Init();
  int Make();

  void Clear(const Option_t* opts="" );
  int  Finish();

  void setPointHits(){ mPointHits = true; }

  virtual const char* GetCVS() const;
private:
protected:

  TH2F* h2LocalXY;
  TH2F* h2LocalSmearedXY;
  TH2F* h2LocalDeltaXY;
  TH3F* h3LocalDeltaXYDisk;
  TFile* fOut;

  float mStereo;
  bool mPointHits;
  bool mAmbiguity;
  bool mEnable[12];

  float mStripWidth;
  float mWireSpacing;
  float mWindow; // for filtering combinatorics
  float mStagger;

  bool mConstEta;

  void fillStripDisk(StEvent *event);
  void fillThinGapChambers(StEvent *event);

  ClassDef(StFtsSiFastSimulatorMaker,0);
};

inline const char* StFtsSiFastSimulatorMaker::GetCVS() const {
  static const char cvs[]="Tag $Name:  $ $Id: StFtsSiFastSimulatorMaker.h,v 1.1.2.2 2018/06/07 16:19:20 jwebb Exp $ built " __DATE__ " " __TIME__ ;
  return cvs;
}

#endif
