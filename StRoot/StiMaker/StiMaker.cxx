//
// $Id $
//StiMaker.cxx
// M.L. Miller
// 5/00
// Modified Pruneau 3/02
//
//
// $Log: StiMaker.cxx,v $
// Revision 1.98  2002/06/26 23:05:31  pruneau
// changed macro
//
// Revision 1.97  2002/06/18 18:08:34  pruneau
// some cout statements removed/added
//
// Revision 1.96  2002/06/04 19:45:31  pruneau
// including changes for inside out tracking
//
// Revision 1.95  2002/05/29 19:13:50  calderon
// Added
//
//   mevent = mStEventFiller->fillEvent(mevent, toolkit->getTrackContainer());
//
// for globals and
//
//   mevent = mStEventFiller->fillEventPrimaries(mevent, toolkit->getTrackContainer());
//
// for primaries.
//
//
#include <iostream.h>
#include <math.h>
#include <string>

// StRoot
#include "StChain.h"
#include "St_DataSet.h"
#include "St_DataSetIter.h"
#include "StMessMgr.h"

// SCL
#include "SystemOfUnits.h"
#include "PhysicalConstants.h"

// StEvent
#include "StEventTypes.h"

//StMcEventMaker
#include "StMcEventMaker/StMcEventMaker.h"

// Sti
#include "Sti/StiIOBroker.h"
#include "Sti/StiFactoryTypes.h"
#include "Sti/StiHitContainer.h"
#include "Sti/StiHit.h"
#include "Sti/StiDetector.h"
#include "Sti/StiPlacement.h"
#include "Sti/StiHitFiller.h"
#include "Sti/StiDetectorContainer.h"
#include "Sti/StiTrackContainer.h"
#include "Sti/StiCompositeSeedFinder.h"
#include "Sti/StiSeedFinder.h"
#include "Sti/StiLocalTrackSeedFinder.h"
#include "Sti/StiTrackSeedFinder.h"
#include "Sti/StiEvaluableTrackSeedFinder.h"
#include "StiGui/StiRDLocalTrackSeedFinder.h"
#include "Sti/StiDetectorFinder.h"
#include "Sti/StiKalmanTrack.h"
#include "Sti/StiKalmanTrackFinder.h"
#include "Sti/StiTrackMerger.h"
#include "Sti/StiLocalTrackMerger.h"
#include "Sti/Messenger.h"
#include "Sti/StiDynamicTrackFilter.h"

//StiGui
#include "StiGui/StiGuiFactoryTypes.h"
#include "StiGui/StiDrawableHits.h"
#include "StiGui/StiRootDrawableHits.h"
#include "StiGui/StiRootDrawableLine.h"
#include "StiGui/StiRootDrawableHitContainer.h"
#include "StiGui/StiRootDisplayManager.h"

//StiEvaluator
#include "StiEvaluator/StiEvaluator.h"
#include "StiEvaluator/StiEventAssociator.h"

// StiMaker
#include "StiDefaultToolkit.h"
#include "StiStEventFiller.h"
#include "StiMaker.h"

StiMaker* StiMaker::sinstance = 0;

ostream& operator<<(ostream&, const StiHit&);


ClassImp(StiMaker)
  
  StiMaker::StiMaker(const Char_t *name) : 
    StMaker(name),
    initialized(0),
    mEvalFileName("empty"),
    ioBroker(0),
    toolkit(0),
    tracker(0),
    mStEventFiller(0),
    mevent(0), 
    mMcEvent(0), 
    mMcEventMaker(0),
    mAssociationMaker(0)
{
  cout <<"StiMaker::StiMaker()"<<endl;
  sinstance = this;
  toolkit = StiDefaultToolkit::instance();
}

StiMaker* StiMaker::instance()
{
  return (sinstance) ? sinstance : new StiMaker();
}

void StiMaker::kill()
{
  if (sinstance) {
    delete sinstance;
    sinstance = 0;
  }
  return;
}

StiMaker::~StiMaker() 
{
  cout <<"StiMaker::~StiMaker()"<<endl;
	
  Messenger::kill();
}

void StiMaker::Clear(const char*)
{
  if (initialized) 
    {
      initialized = true;
      toolkit->getHitContainer()->clear();
      toolkit->getDetectorContainer()->reset();
      toolkit->getHitFactory()->reset();
      toolkit->getTrackFactory()->reset();
      toolkit->getTrackNodeFactory()->reset();
      toolkit->getTrackContainer()->clear();
      if (ioBroker->useGui()) 
				toolkit->getDisplayManager()->reset();
    }
  StMaker::Clear();
}

Int_t StiMaker::Finish()
{
  return StMaker::Finish();
}

Int_t StiMaker::Init()
{
  return kStOk;
}

Int_t StiMaker::InitRun(int run)
{
  if (!initialized)
    {
      cout <<"\n --- StiMaker::InitRun(): Building --- \n"<<endl;
      initialized=true;
      
      Messenger::init();
      Messenger::setRoutingMask(0);
      
      ioBroker = toolkit->getIOBroker();
      cout <<"\n\n ------------------- StiIOBroker ----------------------- \n\n"<<*ioBroker<<endl;
      if (ioBroker->useGui()) 
				{
					cout <<"--- Display Manager will be set" << endl;
					toolkit->getDisplayManager()->cd();
					cout <<"--- Display Manager Ready" << endl;
				}
      else
				cout <<"--- Display Manager will not be used" << endl;
      if (ioBroker->simulated()==true)
				{
					if (mAssociationMaker)
						cout << "AssociationMaker Defined" << endl;
					else
						cout << "---- AssociationMaker NOT Defined" << endl;
					
					StiEventAssociator::instance(mAssociationMaker);
					StiEvaluator::instance(mEvalFileName);
					//toolkit->setAssociationMaker(mAssociationMaker);
					//toolkit->getEvaluator(mEvalFileName);
					cout <<"--- Evaluator Ready" << endl;
				}
      else
				cout <<"--- Evaluator will not be used" << endl;
      tracker = dynamic_cast<StiKalmanTrackFinder *>(toolkit->getTrackFinder());
      //StiStEventFiller
      mStEventFiller = new StiStEventFiller();
      
      cout <<"--- Tracker Ready" << endl;
      if (ioBroker->useGui()) 
				{
					toolkit->getDisplayManager()->setSkeletonView();
					toolkit->getDisplayManager()->draw();
					toolkit->getDisplayManager()->update();
					//toolkit->getDisplayManager()->print();
				}
      cout <<"\n --- StiMaker::InitRun(): Done building --- \n"<<endl;
    }
  return StMaker::InitRun(run);
}

Int_t StiMaker::Make()
{
  cout <<" \n\n ------------ You have entered StiMaker::Make() ----------- \n\n"<<endl;
  eventIsFinished = false;
  StEvent* rEvent = 0;
  rEvent = dynamic_cast<StEvent*>( GetInputDS("StEvent") );
  StMcEvent* mc = 0;
  if (rEvent) 
    {
      mevent = rEvent;
      cout <<"Number of Primary Vertices:\t"<<mevent->numberOfPrimaryVertices()<<endl;
			 
      //Fill hits, organize the container
      toolkit->getHitFiller()->setEvent(mevent);
      toolkit->getHitFiller()->fillHits(toolkit->getHitContainer(), toolkit->getHitFactory());
				
      cout <<"StiMaker::Make() - INFO - sortHits starting"<<endl;
      toolkit->getHitContainer()->sortHits();
      cout <<"StiMaker::Make() - INFO - sortHits completed"<<endl;
      cout <<"StiMaker::Make() - INFO - Call StiHitContainer::update()"<<endl;
      toolkit->getHitContainer()->update();
      cout <<"StiMaker::Make() - INFO Call TrackSeedFinder reset "<<endl;
      //Init seed finder for start
      StiSeedFinder * seedFinder = toolkit->getTrackSeedFinder();
      if (seedFinder)
				seedFinder->reset();
      else
				{
					cout << "StiMaker::Make() - FATAL - seedFinder==0" << endl;
					return 0;
				}
      cout <<"StiMaker::Make() - INFO - Call TrackSeedFinder reset completed"<<endl;
      if (ioBroker->simulated()) 
	{
	  if (!mMcEventMaker)
	    {
	      cout <<"StiMaker::Make(). ERROR!\tmMcEventMaker==0"<<endl;
	      return 0;
	    }
	  mc = mMcEventMaker->currentMcEvent();
	  mMcEvent = mc;
	  if (mc==0)
	    {
	      cout <<"StiMaker::Make(). ERROR!\tMcEvent==0"<<endl;
	      return 0;
	    }
	  StiEvaluableTrackSeedFinder* temp;
	  temp = dynamic_cast<StiEvaluableTrackSeedFinder*>(toolkit->getTrackSeedFinder());
	  if (temp!=0) 
	    temp->setEvent(mc);
	}
      //Now we can loop, if we're not using the gui
      if (!ioBroker->useGui()) 
	finishEvent();
    }
  if (ioBroker->useGui()==true) 
    {
      toolkit->getDisplayManager()->draw();
      toolkit->getDisplayManager()->update();
    }
  return kStOK;
}

void StiMaker::printStatistics() const
{
  cout <<"HitFactory Size:\t"<<toolkit->getHitFactory()->getCurrentSize()<<endl;
  cout <<"HitContainer size:\t"<<toolkit->getHitContainer()->size()<<endl;
  cout <<"Number of Primary Vertices:\t"<<toolkit->getHitContainer()->numberOfVertices()<<endl;
}

void StiMaker::finishEvent()
{
  if (eventIsFinished)
    {
      cout << "StiMaker::finishEvent() - Event reconstruction is finished." <<endl;
      return;				
    }
  cout <<"StiMaker::finishEvent() - Event reconstruction begins."<<endl;
  cout <<mevent->numberOfPrimaryVertices()<<endl;
  
  StTimer clock;
  clock.start();
  tracker->findTracks();
  clock.stop();
  cout <<"StiMaker::finishEvent() - Time to find tracks: "<<clock.elapsedTime()<<" cpu seconds"<<endl;

  //
  // fill the global tracks in StEvent
  //
  clock.start();
  cout <<"StiMaker::finishEvent() - INFO - Call StEvent Filler"  << endl;
  mevent = mStEventFiller->fillEvent(mevent, toolkit->getTrackContainer());
  clock.stop();
  cout <<"StiMaker::finishEvent() - Time to fill StEvent: "<<clock.elapsedTime()<<" cpu seconds"<<endl;

  bool useTrackMerger=false;
  if (useTrackMerger)
    {
      cout <<"Merge Tracks"<<endl;
      clock.reset();
      //clock.start();
      //mTrackMerger->mergeTracks();
      //clock.stop();
      //cout <<"StiMaker::finishEvent() - Time to merge tracks: "<<clock.elapsedTime()<<" cpu seconds"<<endl;
    }
  bool useExtendToVertex=true;
  if (useExtendToVertex)
    {
      cout <<"StiMaker::finishEvent() - INFO - Get main vertex and extend tracks" << endl;
      if (mevent->primaryVertex()) {
	  StiHit * vertex = toolkit->getHitFactory()->getObject();
	  const StThreeVectorF& vp = mevent->primaryVertex()->position();
	  const StThreeVectorF& ve = mevent->primaryVertex()->positionError();
	  vertex->set(0.,0.,vp.x(),vp.y(),vp.z(),ve.x(),0.,0.,ve.y(),0.,ve.z());
	  vertex->setStHit(mevent->primaryVertex());
	  tracker->extendTracksToVertex(vertex);
	  cout <<"StiMaker::finishEvent() - INFO - Tracks extension to main vertex completed" << endl;

	  //
	  // fill the primary tracks in StEvent
	  //
	  clock.start();  
	  cout <<"StiMaker::finishEvent() - INFO - Call StEvent Filler for Primaries"  << endl;
	  //mevent = mStEventFiller->fillEventPrimaries(mevent, toolkit->getTrackContainer());
	  clock.stop();
	  cout <<"StiMaker::finishEvent() - Time to fill StEvent Primaries: "<<clock.elapsedTime()<<" cpu seconds"<<endl;

      }
      else {
	  cout <<"StiMaker::finishEvent() - INFO - Event has no vertex" << endl;
      }
    }
  if (ioBroker->simulated())
    {
      cout <<"StiMaker::finishEvent() - INFO - Call Associator"<<endl;
      StiEventAssociator::instance()->associate(mMcEvent);
      cout <<"StiMaker::finishEvent() - INFO - Associator done"<<endl;
      cout <<"StiMaker::finishEvent() - INFO - Call Evaluator"<<endl;
      StiEvaluator::instance()->evaluate(toolkit->getTrackContainer());
      cout <<"StiMaker::finishEvent() - INFO - Evaluator done"<<endl;
    }
  /* 
     Proper display done if the following piece of code is commented out.
     if (ioBroker->useGui()==true) 
     {
     cout <<"StiMaker::finishEvent() - INFO - Call HitContainer update"<<endl;
     toolkit->getDisplayManager()->reset();
     toolkit->getHitContainer()->update();
     cout <<"StiMaker::finishEvent() - INFO - HitContainer update completed"<<endl;
     
     cout <<"StiMaker::finishEvent() - INFO - Call DisplayManager update "<<endl;
     // update canvas
     toolkit->getDisplayManager()->draw(); 
     toolkit->getDisplayManager()->update();
     cout <<"StiMaker::finishEvent() - INFO - DisplayManager update completed"<<endl;
     }
  */
  clock.stop();
  eventIsFinished = true;
  cout <<"StiMaker::finishEvent() - INFO - Done"<<endl;
}

void StiMaker::finishTrack()
{
	//Add call to next tracker action here
	if (ioBroker->doTrackFit()==true) {
		tracker->fitNextTrack();
	}
	else {
		tracker->findNextTrack();
	}
	return;
}

void StiMaker::doNextTrackStep()
{
	tracker->doNextTrackStep();
}

void StiMaker::defineNextTrackStep(StiFindStep val)
{
	cout <<"StiMaker::defineNextTrackStep(). Set to: ";
	cout <<static_cast<int>(val)<<endl;
	tracker->setStepMode(val);
}

StiIOBroker* StiMaker::getIOBroker()
{
	return toolkit->getIOBroker();
}

