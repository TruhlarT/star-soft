//*-- Author : James Dunlop
// 
// $Id: StHitFilterMaker.cxx,v 1.4 2004/09/02 19:13:44 fisyak Exp $
// $Log: StHitFilterMaker.cxx,v $
// Revision 1.4  2004/09/02 19:13:44  fisyak
// Keep Tpc hits for tracks with Tof Pid Traits
//
// Revision 1.3  2004/04/08 19:28:55  caines
// Make Hitfilter take out those SVT hits not on tracks defined in the constructor - same as TPC filtering
//
// Revision 1.2  2003/07/30 15:27:00  caines
// Set options so you delete TPC and SVT hit if Zert >30. If ZVert<30cm save all good svt hits and TPC hits on tracks
//
// Revision 1.1  2003/02/07 02:16:15  jeromel
// First version of a generlized HitFilter/removal maker. Expeditious review
// done.
//
//


#include "StHitFilterMaker.h"
#include "StChain.h"
#include "StMessMgr.h"


#include "StEventTypes.h"
#include <algorithm>
#ifndef ST_NO_NAMESPACES
using std::binary_search;
using std::unique;
using std::sort;

#endif


ClassImp(StHitFilterMaker)

//_____________________________________________________________________________
/// StHitFilterMaker constructor
StHitFilterMaker::StHitFilterMaker(const char *name, Double_t ptl, Double_t pth, Double_t eta, Double_t zvert):StMaker(name),mPtLowerCut(ptl),mPtUpperCut(pth),mAbsEtaCut(eta), mAbsZVertCut(zvert){
  //  This has defaults for the cuts in the include file
}

/// Dummy destructor
StHitFilterMaker::~StHitFilterMaker(){
    //NOOP
}

/// Init - is a first method the top level StChain calls to initialize all its makers 
Int_t StHitFilterMaker::Init(){

  // Output the cuts
  gMessMgr->Info() << "StHitFilterMaker::Init():  keeping tracks between      " << 
    mPtLowerCut << " and " << mPtUpperCut << "GeV/c (negative = no cut)" << endm;
  gMessMgr->Info() << "StHitFilterMaker::Init():  keeping tracks with |eta| < " << 
    mAbsEtaCut << endm;
   gMessMgr->Info() << "StHitFilterMaker::Init():  keeping tracks with |ZVert| < " << 
    mAbsZVertCut << endm;
  return StMaker::Init();
}


//_____________________________________________________________________________
/*!
  Get a pointer to stevent using the GetInputDS() method, loops
  over track nodes and select based on the accpt() method. Also
  strips the runaway hits (hits not on tracks).
 */
Int_t StHitFilterMaker::Make(){
    //	Get StEvent
    //
    StEvent* event;
    event = (StEvent *) GetInputDS("StEvent");
    
    
    if (!event) {
        gMessMgr->Info() <<"StHitFilterMaker::Make(): not a valid StEvent: " << endm;
	

	return kStOK;
    }
    // Fill up the ones to keep if ZVert in range
    vector<StTrackNode*> keptTrackNodes;
    if( accept(event)){
      StSPtrVecTrackNode& nodes = event->trackNodes();
      for (StSPtrVecTrackNodeIterator nodeIter = nodes.begin();
	   nodeIter != nodes.end(); ++nodeIter) {
	bool isAcceptedTrack = false;
	
	for (UInt_t ientry=0;
	     ientry < (*nodeIter)->entries(); ++ientry) {
	  StTrack *track = (*nodeIter)->track(ientry);
	  
	  // Check that it's got tpc hits
	  
	  if (!(track->topologyMap().hasHitInDetector(kTpcId))) {
	    continue;
	  }
	  
	  if (accept(track)) {
	    isAcceptedTrack = true;
	    break;
	  }
	}
	if (isAcceptedTrack) {
	  keptTrackNodes.push_back(*nodeIter);
	}
      }
      // Sort it and keep unique
      sort(keptTrackNodes.begin(),keptTrackNodes.end());
      vector<StTrackNode*>::iterator uniquePos = 
	unique(keptTrackNodes.begin(),keptTrackNodes.end());
      keptTrackNodes.erase(uniquePos,keptTrackNodes.end());
    }
    
    gMessMgr->Info() << "StHitFilterMaker::Make(): keeping TPC hits on " <<
      keptTrackNodes.size() << "track nodes " << endm;
    
    this->removeTpcHitsNotOnTracks(event,keptTrackNodes);
    this->removeSvtHitsNotOnTracks(event,keptTrackNodes);
    this->removeBadSvtHits(event);
    
    return kStOK;
}

bool StHitFilterMaker::accept(StEvent *event) {

  if( !(event->primaryVertex()))  return false;
  if( fabs(event->primaryVertex()->position().z()) > mAbsZVertCut) return false;
  return true;
}

bool StHitFilterMaker::accept(StTrack *track) {
    if (track->flag() <= 0) return false;
    StSPtrVecTrackPidTraits &traits = track->pidTraits();
    unsigned int size = traits.size();
    if (size) {
      for (unsigned int i = 0; i < size; i++) {
	if (! traits[i]) continue;
	if ( traits[i]->IsZombie()) continue;
	StTofPidTraits* p = dynamic_cast<StTofPidTraits*>(traits[i]);
	if (p) {return true;}
      }
    }
    if (track->geometry()) {
	if (mPtLowerCut > 0 && track->geometry()->momentum().perp() < mPtLowerCut )
	    return false;
	if (mPtUpperCut > 0 && track->geometry()->momentum().perp() > mPtUpperCut )
	    return false;
	if (mAbsEtaCut > 0 && fabs(track->geometry()->momentum().pseudoRapidity()) > mAbsEtaCut) 
	    return false;
	
    }
    
    return true;
}

bool StHitFilterMaker::accept(StHit *hit) {
  if( hit->flag() > 3) return false;
  return true;
}


/*!
  This is a pretty simple cut and paste + extension from StEventScavenger
  Only difference is that it searches the vector of keptTrackNodes
  for good nodes, rather than relying on zombies.
*/	
bool StHitFilterMaker::removeTpcHitsNotOnTracks(StEvent *event, 
						vector<StTrackNode*>& keptTrackNodes) 
{
  Int_t removedHits = 0;
    
  if (event && event->tpcHitCollection()) {
    // first remove all hits not associated with a track at all
    StTpcHitCollection *theHits = event->tpcHitCollection();
    for (unsigned int n=0; n<theHits->numberOfSectors(); n++) {
      for (unsigned int m=0; m<theHits->sector(n)->numberOfPadrows(); m++) {
	
	for (unsigned int h=0; h<theHits->sector(n)->padrow(m)->hits().size(); h++) {
		    
	  if (theHits->sector(n)->padrow(m)->hits()[h]->trackReferenceCount() == 0) {
	    if (! (theHits->sector(n)->padrow(m)->hits()[h]->isZombie())) {
	      theHits->sector(n)->padrow(m)->hits()[h]->makeZombie();
	      ++removedHits;
	    }
	  }
	}
      }
    }
    gMessMgr->Info() << "StHitFilterMaker::removeTpcHitsNotOnTracks.  Removed " <<
      removedHits << " TPC hits not on any tracks" << endm;
    removedHits = 0;
	
    // now all hits not associated 
    StSPtrVecTrackNode& nodes = event->trackNodes();
    for (unsigned int i = 0; i < nodes.size(); i++) {   // loop nodes
      StTrackNode* node = nodes[i];
      if (!binary_search(keptTrackNodes.begin(),
			 keptTrackNodes.end(),
			 node)) 
	{
	  
	  for (unsigned int j = 0; j < node->entries(); j++) {   // loop tracks in node
	    StTrack* track = node->track(j);
	    // Don't do anything if it doesn't have a TPC hit
	    if (!(track->topologyMap().hasHitInDetector(kTpcId))) {
	      continue;
	    }
	    
	    StTrackDetectorInfo* info = track->detectorInfo();
	    if (info) {
	      StPtrVecHit& hitList = info->hits();
	      for (unsigned int k = 0; k < hitList.size(); k++)   // loop hits
		if (hitList[k]->detector() == kTpcId && 
		    !(hitList[k]->isZombie()) ) {
		  hitList[k]->makeZombie();
		  ++removedHits;
		}
	      
	    }
	  }
	}
    }
    gMessMgr->Info() << "StHitFilterMaker::removeTpcHitsNotOnTracks.  Removed " <<
      removedHits << " TPC hits not on passed tracks" << endm;
    
    return true;
  }
  else
    return false;
}

/*!
  searches the vector of keptTrackNodes
  for good nodes, rather than relying on zombies. and removes SVT hits not on tracks
*/	
bool StHitFilterMaker::removeSvtHitsNotOnTracks(StEvent *event, 
						vector<StTrackNode*>& keptTrackNodes) 
{
  Int_t removedHits = 0;
    
  if (event && event->svtHitCollection()) {
    // first remove all hits not associated with a track at all
    StSvtHitCollection *theHits = event->svtHitCollection();
    for (unsigned int l=0; l<theHits->numberOfBarrels(); l++) {
      for (unsigned int m=0; m<theHits->barrel(l)->numberOfLadders(); m++) {
	for (unsigned int n=0; n<theHits->barrel(l)->ladder(m)->numberOfWafers(); n++) {
	  for (unsigned int h=0; h<theHits->barrel(l)->ladder(m)->wafer(n)->hits().size(); h++) {   
	    
	    if (theHits->barrel(l)->ladder(m)->wafer(n)->hits()[h]->trackReferenceCount() == 0) {
	      if (! (theHits->barrel(l)->ladder(m)->wafer(n)->hits()[h]->isZombie())) {
		theHits->barrel(l)->ladder(m)->wafer(n)->hits()[h]->makeZombie();
		++removedHits;
	      }
	    }
	  }
	}
      }
    }

    gMessMgr->Info() << "StHitFilterMaker::removedSvtHitsNotOnTracks.  Removed " <<
      removedHits << " SVT hits not on any tracks" << endm;
    removedHits = 0;
	
    // now all hits not associated 
    StSPtrVecTrackNode& nodes = event->trackNodes();
    for (unsigned int i = 0; i < nodes.size(); i++) {   // loop nodes
      StTrackNode* node = nodes[i];
      if (!binary_search(keptTrackNodes.begin(),
			 keptTrackNodes.end(),
			 node)) 
	{
	  
	  for (unsigned int j = 0; j < node->entries(); j++) {   // loop tracks in node
	    StTrack* track = node->track(j);
	    // Don't do anything if it doesn't have a SVT hit
	    if (!(track->topologyMap().hasHitInDetector(kSvtId))) {
	      continue;
	    }
	    
	    StTrackDetectorInfo* info = track->detectorInfo();
	    if (info) {
	      StPtrVecHit& hitList = info->hits();
	      for (unsigned int k = 0; k < hitList.size(); k++)   // loop hits
		if (hitList[k]->detector() == kSvtId && 
		    !(hitList[k]->isZombie()) ) {
		  hitList[k]->makeZombie();
		  ++removedHits;
		}
	      
	    }
	  }
	}
    }
    gMessMgr->Info() << "StHitFilterMaker::removeSvtHitsNotOnTracks.  Removed " <<
      removedHits << " SVT hits not on passed tracks" << endm;
    
    return true;
  }
  else
    return false;
}


/*!
  This is a pretty simple cut and paste + extension from StEventScavenger
  Only difference is that it searches the vector of keptTrackNodes
  for good nodes, rather than relying on zombies.
*/	
bool StHitFilterMaker::removeBadSvtHits(StEvent *event) 
{
  Int_t removedHits = 0;
  
  if (event && event->svtHitCollection()) {
    // first remove all hits with flag > 3
    StSvtHitCollection *theHits = event->svtHitCollection();
    for (unsigned int l=0; l<theHits->numberOfBarrels(); l++) {
      for (unsigned int m=0; m<theHits->barrel(l)->numberOfLadders(); m++) {
	for (unsigned int n=0; n<theHits->barrel(l)->ladder(m)->numberOfWafers(); n++) {
	  for (unsigned int h=0; h<theHits->barrel(l)->ladder(m)->wafer(n)->hits().size(); h++) {   
	    if (! (accept(theHits->barrel(l)->ladder(m)->wafer(n)->hits()[h])) ||
		!accept(event)) {
	      if (! (theHits->barrel(l)->ladder(m)->wafer(n)->hits()[h]->isZombie())) {
		theHits->barrel(l)->ladder(m)->wafer(n)->hits()[h]->makeZombie();
		++removedHits;
	      }
	    }
	  }
	}
      }
    }

    gMessMgr->Info() << "StHitFilterMaker::removeBadSvtHits.  Removed " <<
      removedHits << " bad SVT hits" << endm;
  return true;
  }
  else
    return false;
}




