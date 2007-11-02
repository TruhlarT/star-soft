//
// Pibero Djawwotho <pibero@iucf.indiana.edu>
// Indiana University
// October 23, 2007
//

#ifndef L2upsilon_hh
#define L2upsilon_hh

#include <cstdio>
#include <vector>
#include <list>
#include <ctime>

using namespace std;
class L2Histo;
#ifdef __ROOT__ // RCF environment
#include "StTriggerUtilities/L2Emulator/L2algoUtil/L2VirtualAlgo.h"
#include "StDaqLib/TRG/trgStructures.h"
#else

#include "StTriggerUtilities/L2Emulator/L2algoUtil/L2VirtualAlgo.h"
#include "StDaqLib/TRG/trgStructures.h"
#endif

#include "bemcTower.h"

class L2EmcDb;

struct BemcCluster {
  float x;
  float y;
  float z;
  float E;
};

class Timer {
public:
  void start();
  time_t time() const;

private:
  time_t startTime;
};

class L2upsilon : public L2VirtualAlgo {
public:
  L2upsilon(const char* name, L2EmcDb* db, char* outDir, int resOff);
  ~L2upsilon();

  int initRun(int runNumber, int* userInt, float* userFloat);
  bool doEvent(int L0trg, int eventNumber, TrgDataType* trgData,
	       int bemcIn, unsigned short* bemcData,
	       int eemcIn, unsigned short* eemcData);
  void finishRun();
  void print();

private:
  void  findSeedTowers(vector<int>& L0Seeds, vector<int>& L2Seeds);
  void  calcCluster(int rdo);

  void  createHistograms();
  void  writeHistograms();
  void  resetHistograms();
  void  deleteHistograms();

  const char* timeString() const;

  BemcTower bemcTower[4800];
  BemcCluster bemcCluster[4800];
  int mSoftIdToRdo[4801];
  int mPhiEtaToRdo[120][40];
  TrgDataType* trgData;
  unsigned short* bemcData;

  char mBaseFileName[FILENAME_MAX];
  FILE* mLogFile;

  int mEventsSeen;
  int mEventsAccepted;

  // float parameters
  float mMinL0ClusterEnergy;
  float mMinL2ClusterEnergy;
  float mMinInvMass;
  float mMaxInvMass;
  float mMaxCosTheta;

  // int parameters
  int mL0SeedThreshold;
  int mL2SeedThreshold;
  int mUseCtb;
  int mUseVertexZ;
  int mNumberOfTowersPerCluster;

  // Histograms
  list<L2Histo*> mHistograms;
  L2Histo* hL0SeedTowers;
  L2Histo* hL2SeedTowers;
  L2Histo* hNumberOfL0Seeds;
  L2Histo* hNumberOfL2Seeds;
  L2Histo* hInvMass;
  L2Histo* hTime;
  L2Histo* hEnergyOfL0Cluster;
  L2Histo* hEnergyOfL2Cluster;
  L2Histo* hCosTheta;
  L2Histo* hVertexZ;
  L2Histo* hCtbIndex;
  L2Histo* hHighTowers;
  L2Histo* hL0rate;
  L2Histo* hL2rate;


  // Timer
  Timer timer;
};

inline void Timer::start() { startTime = std::time(0); }
inline time_t Timer::time() const { return std::time(0) - startTime; }

inline L2upsilon::L2upsilon(const char* name, L2EmcDb* db, char* outDir, int resOff) :
  L2VirtualAlgo(name, db, outDir, resOff)
{
  mLogFile = 0;
  createHistograms();
}

inline L2upsilon::~L2upsilon()
{
  if (mLogFile) {
    finishRun();
    fclose(mLogFile);
    mLogFile = 0;
  }

  deleteHistograms();
}

inline const char* L2upsilon::timeString() const
{
  time_t t = time(0);
  return ctime(&t);
}

#endif
