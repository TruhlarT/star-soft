#include "StSpectraCutNhit.h"

StSpectraCutNhit::StSpectraCutNhit(){

}
StSpectraCutNhit::StSpectraCutNhit(int lowLimit, int highLimit){
 mLowLimit = lowLimit;
 mHighLimit = highLimit;
}

StSpectraCutNhit::~StSpectraCutNhit() {
}

bool StSpectraCutNhit::satisfiesCut(StGlobalTrack* track, StEvent* event){
  int nhit = track->numberOfTpcHits();
  if (nhit > mLowLimit && nhit < mHighLimit) { 
    return true;
  } else {
    return false;
  }
}

