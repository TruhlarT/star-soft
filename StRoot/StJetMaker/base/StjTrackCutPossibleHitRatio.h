// -*- mode: c++;-*-
// $Id: StjTrackCutPossibleHitRatio.h,v 1.5 2008/08/04 02:37:24 tai Exp $
// Copyright (C) 2008 Tai Sakuma <sakuma@bnl.gov>
#ifndef STJTRACKCUTPOSSIBLEHITRATIO_H
#define STJTRACKCUTPOSSIBLEHITRATIO_H

#include "StjTrackCut.h"

class StjTrackCutPossibleHitRatio : public StjTrackCut {
  // to avoid split tracks

public:
  StjTrackCutPossibleHitRatio(double minRatio = 0.51) :_minRatio(minRatio) { }
  virtual ~StjTrackCutPossibleHitRatio() { }

  bool operator()(const StjTrack& track)
  {
    if(static_cast<double>(track.nHits)/static_cast<double>(track.nHitsPoss) < .51) return true;

    return false;
  }

private:

  double  _minRatio;

  ClassDef(StjTrackCutPossibleHitRatio, 1)

};

#endif // STJTRACKCUTPOSSIBLEHITRATIO_H
