#ifndef StiKalmanTrackFinder_H
#define StiKalmanTrackFinder_H 1

#include "StiTrackFinder.h"
#include "Exception.h"

class StiDetector;
class StiDectorContainer;
class StiTrack;
class StiKalmanTrack;

class StiKalmanTrackFinder : public StiTrackFinder
{
 public:
  StiKalmanTrackFinder();
  ~StiKalmanTrackFinder();
    //action methods_______________________________________________
    //inherited
    virtual void reset();
    virtual void findTracks();
    virtual bool isValid(bool debug=false) const; //Check if everything is kosher
    
    virtual void doTrackFit();
    virtual void doTrackFind();
    virtual bool hasMore();
    
    virtual void setElossCalculated(bool option);
    virtual void setMCSCalculated(bool option);
    void   setMassHypothesis(double m);
    double getMassHypothesis();

    //Local
    virtual void findTrack(StiTrack * t); //throw ( Exception);
	virtual StiKalmanTrackNode * followTrackAt(StiKalmanTrackNode * node); //throw (Exception);
    void removeNodeFromTrack(StiKalmanTrackNode * node, StiKalmanTrack* track);
    void pruneNodes(StiKalmanTrackNode * node);
    void reserveHits(StiKalmanTrackNode * node);
    bool extendToMainVertex(StiKalmanTrackNode * node);



    //double getYWindow(StiKalmanTrackNode * n, StiHit * h) const;
    //double getZWindow(StiKalmanTrackNode * n, StiHit * h) const;
    
protected:
    
    int    singleNodeFrom;
    bool   singleNodeDescent;
    double massHypothesis;
    double maxChi2ForSelection;
    int minContiguousHitCountForNullReset;
    int maxNullCount;  
    int maxContiguousNullCount;

};

#endif


