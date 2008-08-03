// -*- mode: c++;-*-
// $Id: StMuTrackFourVec.h,v 1.4 2008/08/03 00:26:50 tai Exp $
#ifndef STMUTRACKFOURVEC_H
#define STMUTRACKFOURVEC_H

#include "StJetFinder/AbstractFourVec.h"

#include "StMuTrackEmu.h"

#include "StDetectorId.h"

#include <TLorentzVector.h>

#include <iostream>
#include <string>

class StMuTrackFourVec : public AbstractFourVec {

public:
    
  StMuTrackFourVec() : _track(0), index(0), mDetId(kUnknownId), mCharge(0) { }

  StMuTrackFourVec(StMuTrackEmu* t, const TLorentzVector& p, double charge, Int_t i, int detectorId)
    : _track(t)
    , _vec(p)
    , index(i)
    , mDetId(detectorId)
    , mCharge(charge)
  { }

  virtual ~StMuTrackFourVec() { if(_track) delete _track; _track = 0; }
    
  ///momenta
  double pt() const { return _vec.Pt(); }
  double px() const { return _vec.Px(); } 
  double py() const { return _vec.Py(); }
  double pz() const { return _vec.Pz(); }

  ///angles
  double phi()      const { return _vec.Phi(); }
  double eta()      const { return _vec.Eta(); }
  
  //4-th component
  double eT()   const { return _vec.Et(); }

  double e()    const { return _vec.E(); }
  double mass() const { return _vec.M(); }

  //charge
  double charge() const { return mCharge; }

  // Mu StjTrack (null if it's an emc tower/hit/point) this will change soon
  StMuTrackEmu* track() const { return _track; }

  //Index of the track/tower/cluster/point in the container that it came from
  Int_t getIndex(void) const { return index; }
    
  //Id of the detector that generated this 4-vector
  int detectorId() const {return mDetId;}
    
private:

  StMuTrackEmu *_track;
  TLorentzVector _vec;
  Int_t index;
  int mDetId;
  double mCharge;
};

#endif // STMUTRACKFOURVEC_H
