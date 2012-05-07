//StiMaker.h

#ifndef StiMaker_HH
#define StiMaker_HH

#include <string>
using std::string;

#include "StMaker.h"
#include "StEvent/StEnumerations.h"
#include "Sti/StiKalmanTrackFinder.h"
#include "Sti/StiKalmanTrackFitter.h"

class TFile;
class TTree;
class StiPullEvent;
class StEvent;
class StiHit;
class StiTrack;
class StiStEventFiller;
class StiTrackContainer;
class StiTrackFinder;
class StiKalmanTrackFinder;
class StiKalmanTrackFitter;
class StiKalmanTrackNode;
class StiKalmanTrack;
class StiTrackMerger;
class StiToolkit;
class StiVertexFinder;
template<class FILTERED> class EditableFilter;


class StiMaker : public StMaker 
{
 public:
    
    StiMaker(const char* name = "Sti");
    virtual ~StiMaker();
    virtual void  Clear(const char* opt="");
    virtual Int_t Init();
            Int_t InitDetectors();
            Int_t InitPulls();
            Int_t FillPulls();
    virtual Int_t InitRun(int);
    virtual Int_t Make();
    virtual Int_t MakeGlobalTracks(StEvent  *event);
    virtual Int_t MakePrimaryTracks(StEvent *event);
    virtual Int_t Finish();

    virtual const char* GetCVS() const
    {static const char cvs[]="Tag $Name:  $ $Id: StiMaker.h,v 2.32 2012/05/07 14:56:14 fisyak Exp $ built "__DATE__" "__TIME__; return cvs;}	


    StiToolkit * getToolkit();
    void load(TDataSet *);

 protected:
    virtual TDataSet  *FindDataSet (const char* logInput,
                                    const StMaker *uppMk=0,
                                    const StMaker *dowMk=0) const ;
  TDataSet*   fVolume;   //!
    
 private:
    void  MyClear();

    bool                 eventIsFinished;
    bool                 _initialized;
    StiToolkit  *        _toolkit;
    StiHitLoader<StEvent,StiDetectorBuilder> * _hitLoader;
    StiTrackFinder *       _seedFinder;
    StiKalmanTrackFinder * _tracker;
    StiKalmanTrackFitter * _fitter;
    StiStEventFiller *    _eventFiller;
    StiTrackContainer *   _trackContainer;
    StiVertexFinder*      _vertexFinder;
    EditableFilter<StiTrack> * _loaderTrackFilter;
    EditableFilter<StiHit>   * _loaderHitFilter;
#if 0
    void fillVxFlags();
#endif
    TFile 		*mPullFile;
    StiPullEvent 	*mPullEvent;
    TTree 	        *mPullTTree;
    int 	        mPullHits[3];//number of hits filled. See FillPulls
    int                 mTotPrimTks[2];
    TStopwatch          *mTimg[5];   //HitLoad,GloTrks,Vtx,PriTrks,StFill
    ClassDef(StiMaker,0)
};

//inlines

inline StiToolkit * StiMaker::getToolkit()
{
  return _toolkit;
}
#endif
