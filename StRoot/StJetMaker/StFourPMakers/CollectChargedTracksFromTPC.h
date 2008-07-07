// -*- mode: c++;-*-
// $Id: CollectChargedTracksFromTPC.h,v 1.3 2008/07/07 22:28:48 tai Exp $
#ifndef COLLECTCHARGEDTRACKSFROMTPC_H
#define COLLECTCHARGEDTRACKSFROMTPC_H


#include <vector>
#include <utility>

class StMuTrack;
class StMuDstMaker;

namespace StSpinJet {

class StMuTrackEmu;

class CollectChargedTracksFromTPC {

public:

  CollectChargedTracksFromTPC(StMuDstMaker* uDstMaker);
  virtual ~CollectChargedTracksFromTPC();

  typedef std::vector<std::pair<const StMuTrack*, int> > TrackList__;
  typedef std::vector<StSpinJet::StMuTrackEmu*> TrackList;

  TrackList Do();

  void setUse2006Cuts(bool v) { _use2006Cuts = v; }

private:

  TrackList__ getTracksFromTPC();

  TrackList__ selectTracksToPassToJetFinder(const TrackList__& trackList);

  bool shoudNotPassToJetFinder(const StMuTrack& track) const;

  StMuDstMaker* _uDstMaker;

  bool _use2006Cuts;

};

}

#endif // COLLECTCHARGEDTRACKSFROMTPC_H
