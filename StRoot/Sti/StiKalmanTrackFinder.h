#ifndef StiKalmanTrackFinder_H
#define StiKalmanTrackFinder_H 1

#include <iostream>
using std::cout;
using std::endl;

#include "StiTrackFinder.h"
#include "StiKalmanTrack.h"
#include "StiKalmanTrackNode.h"
#include "StiKalmanTrackFinderParameters.h"
#include "Messenger.h"
#include "SubjectObserver.h"
#include "StThreeVector.hh"
#include "StThreeVectorF.hh"
#include "StThreeVectorD.hh"
#include "Sti/StiHitFiller.h"

class StiDetector;
class StiDectorContainer;
class StiTrack;
class StiToolkit;
class StiSeedFinder;
class StiKalmanTrackFactory;
class StiDetectorContainer;
class StiHitContainer;
class StiTrackContainer;
class StiTrack;
class StEvent;
class StMcEvent;

enum StiFindStep {StepByLayer=1,StepByDetector=2 };

class StiKalmanTrackFinder : public StiTrackFinder, public Observer
{
public:
    StiKalmanTrackFinder(StiToolkit * userToolkit);
    virtual ~StiKalmanTrackFinder();
    //action methods_______________________________________________

    virtual void update();
    virtual void changed(Subject* changedSubject);

    virtual void findTracks();
    virtual void fitTracks(); 
    virtual void extendTracksToVertex(StiHit* vertex);
    virtual void findNextTrack();
    virtual void fitNextTrack();
    virtual void findNextTrackSegment();
    virtual bool find(StiTrack *track, int direction);
    
    virtual void reset();
    virtual bool isValid(bool debug=false) const; //Check if everything is kosher
    
    virtual bool hasMore();
    
    void setParameters(StiKalmanTrackFinderParameters *par);
    StiKalmanTrackFinderParameters * getParameters();
    
    void doInitLayer(int trackingDirection);
    void doNextDetector();
    void doFinishLayer();
    void doFinishTrackSearch();
    void doNextTrackStep();
    void setStepMode(StiFindStep m)
      {
	mode = m;
      }
    StiFindStep getStepMode()
      {
	return mode;
      }
    
  int getTrackSeedFoundCount() const;
  int getTrackFoundCount(Filter<StiTrack> * filter) const;
  int getTrackFoundCount() const;
    
  void setEvent(StEvent * event, StMcEvent * mcEvent);
 
  virtual Filter<StiTrack> * getTrackFilter() const;
  virtual Filter<StiTrack> * getGuiTrackFilter() const;
  virtual Filter<StiTrack> * getGuiMcTrackFilter() const;

protected:

    void getNewState();
    void printState();

    // Local cache of pointers
    // none of the following are owned by this class.
    StiToolkit                * toolkit;
    Filter<StiTrack>            * trackFilter;
    Filter<StiTrack>            * guiTrackFilter;
    Filter<StiTrack>            * guiMcTrackFilter;
    StiSeedFinder             * trackSeedFinder;
    Factory<StiKalmanTrackNode> * trackNodeFactory;
    Factory<StiKalmanTrack> * trackFactory;
    Factory<StiTrack> *         mcTrackFactory;
    StiDetectorContainer      * detectorContainer;
    StiHitContainer           * hitContainer;
    StiTrackContainer         * trackContainer;
    StiTrackContainer         * mcTrackContainer;
    StiKalmanTrackFinderParameters * pars;

private:
    
    StiFindStep mode;
    int       state;
    int       visitedDet ;
    int       position;
    int       lastMove;
    int       nAdded;
    
    double    chi2;
    double    bestChi2;
    StiKalmanTrack         * track;
    StiKalmanTrackNode * sNode;
    StiKalmanTrackNode * tNode;
    StiKalmanTrackNode * bestNode;
    StiKalmanTrackNode * leadNode;
    StiHit * bestHit;
    StiHit * hit;
    const StiDetector * sDet;
    const StiDetector * tDet;
    const StiDetector * leadDet;
    bool trackDone;
    bool scanningDone;
    bool hasHit;
    bool hasDet;
    
    Messenger & trackMes;
    
};

//inlines

inline void StiKalmanTrackFinder::setParameters(StiKalmanTrackFinderParameters *par)
{
	pars = par;
	StiKalmanTrack::setParameters(par);
	StiKalmanTrackNode::setParameters(par);
}

inline Filter<StiTrack> * StiKalmanTrackFinder::getTrackFilter() const
{
  return trackFilter;
}

inline Filter<StiTrack> * StiKalmanTrackFinder::getGuiTrackFilter() const
{
  return guiTrackFilter;
}

inline Filter<StiTrack> * StiKalmanTrackFinder::getGuiMcTrackFilter() const
{
  return guiMcTrackFilter;
}

#endif



