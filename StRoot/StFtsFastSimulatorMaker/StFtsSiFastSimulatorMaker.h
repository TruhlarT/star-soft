#ifndef ST_FTS_FAST_SI_SIMULATOR_MAKER_H
#define ST_FTS_FAST_SI_SIMULATOR_MAKER_H

class StEvent; 
class StRnDHit;
class StRnDHitCollection;
class g2t_fts_hit_st;

#include "StMaker.h"

class StFtsSiFastSimulatorMaker : public StMaker {

public:
  explicit  StFtsSiFastSimulatorMaker( const char* name="ftssifastsim" );
  virtual  ~StFtsSiFastSimulatorMaker(){ /* nada */ }

  int Init();
  int Make();

  void Clear(const Option_t* opts="" );
  int  Finish();

  virtual const char* GetCVS() const;
private:
protected:

  void FillSensor( StRnDHitCollection* collection, g2t_fts_hit_st* hit );

  ClassDef(StFtsSiFastSimulatorMaker,0);
};

inline const char* StFtsSiFastSimulatorMaker::GetCVS() const {
  static const char cvs[]="Tag $Name:  $ $Id: StFtsSiFastSimulatorMaker.h,v 1.1.2.1 2018/03/23 15:05:20 jwebb Exp $ built " __DATE__ " " __TIME__ ;
  return cvs;
}

#endif
