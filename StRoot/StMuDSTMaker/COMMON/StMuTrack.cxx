/***************************************************************************
 *
 * $Id: StMuTrack.cxx,v 1.6 2003/02/21 14:32:47 laue Exp $
 *
 * Author: Frank Laue, BNL, laue@bnl.gov
 ***************************************************************************/

#include "StMuTrack.h"
#include "StMuException.hh"
#include "StEvent/StEventTypes.h"
#include "StEvent/StTrackGeometry.h"
#include "StEvent/StPrimaryVertex.h"
#include "StarClassLibrary/SystemOfUnits.h"
#include "StEvent/StTpcDedxPidAlgorithm.h"
#include "StarClassLibrary/StThreeVectorD.hh"
#include "StarClassLibrary/StPhysicalHelixD.hh"
#include "StarClassLibrary/StParticleTypes.hh"
#include "StEventUtilities/StuProbabilityPidAlgorithm.h"

StuProbabilityPidAlgorithm* StMuTrack::mProbabilityPidAlgorithm=0;
double StMuTrack::mProbabilityPidCentrality=0;

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
StMuTrack::StMuTrack(const StEvent* event, const StTrack* track, int index2Global, int index2RichSpectra, bool l3) : mIndex2Global(index2Global), mIndex2RichSpectra(index2RichSpectra) {
  const StTrack* globalTrack = track->node()->track(global);

  mId = track->key();
  mType = track->type();
  mFlag = track->flag();
  mTopologyMap = track->topologyMap();
  mNHitsPoss = track->numberOfPossiblePoints(kTpcId);

  // while getting the bestGuess, the pidAlgorithm (StTpcDedxPidAlgorithm) is set up.
  // pointers to track and pidTraits are set 
  // So, even though BestGuess will generate a "variable not used" warning, DO NOT DELETE THE NEXT LINES
  static StTpcDedxPidAlgorithm PidAlgorithm;
  static StElectron* Electron = StElectron::instance();
  static StPionPlus* Pion = StPionPlus::instance();
  static StKaonPlus* Kaon = StKaonPlus::instance();
  static StProton* Proton = StProton::instance();
  const StParticleDefinition* pd = track->pidTraits(PidAlgorithm);
  if (pd) {
    mNSigmaElectron = pack2Int( fabsMin(PidAlgorithm.numberOfSigma(Electron),__SIGMA_SCALE__), __SIGMA_SCALE__ );
    mNSigmaPion =     pack2Int( fabsMin(PidAlgorithm.numberOfSigma(Pion),__SIGMA_SCALE__),     __SIGMA_SCALE__ );
    mNSigmaKaon =     pack2Int( fabsMin(PidAlgorithm.numberOfSigma(Kaon),__SIGMA_SCALE__),     __SIGMA_SCALE__ );
    mNSigmaProton =   pack2Int( fabsMin(PidAlgorithm.numberOfSigma(Proton),__SIGMA_SCALE__),   __SIGMA_SCALE__ );
  }

  // if we have pid traits
  if ( PidAlgorithm.traits() ) {
    mdEdx = PidAlgorithm.traits()->mean();
    mNHitsDedx = PidAlgorithm.traits()->numberOfPoints();
  }

  // the following just point to particle definitions in StEvent
  if ( track->detectorInfo() ) {
    mFirstPoint = track->detectorInfo()->firstPoint();
    mLastPoint = track->detectorInfo()->lastPoint();
    mNHits = track->detectorInfo()->numberOfPoints(kTpcId);
  } 


  mNHitsFit = track->fitTraits().numberOfFitPoints(kTpcId);
  mChiSqXY = track->fitTraits().chi2(0);
  mChiSqZ = track->fitTraits().chi2(1);

  if ( track->geometry() ) {
    mHelix = StMuHelix(track->geometry()->helix(),event->runInfo()->magneticField());
    if (event->primaryVertex()) {
      mP = momentumAtPrimaryVertex(event,track);
      mPt = mP.perp();
      mPhi = mP.phi();
      mEta = mP.pseudoRapidity();
      mDCA = dca(event, track);
      if ( globalTrack ) mDCAGlobal = dca(event, globalTrack);

      if (!l3) { // L3TRACKS seem to break pid    
	int charge = track->geometry()->charge();
	//	StParticleDefinition* pc = (*mProbabilityPidAlgorithm)( *track, track->pidTraits() );
	mProbabilityPidAlgorithm->processPIDAsFunction(mProbabilityPidCentrality, mDCA.mag(), charge, mP.mag()/charge, mEta, mNHitsDedx, mdEdx);
	mPidProbElectron= pack2UnsignedShort( (charge>0) ? mProbabilityPidAlgorithm->beingPositronProb() : mProbabilityPidAlgorithm->beingElectronProb(), __PROB_SCALE__) ;
	mPidProbPion=     pack2UnsignedShort( (charge>0) ? mProbabilityPidAlgorithm->beingPionPlusProb() : mProbabilityPidAlgorithm->beingPionMinusProb(), __PROB_SCALE__);
	mPidProbKaon=     pack2UnsignedShort( (charge>0) ? mProbabilityPidAlgorithm->beingKaonPlusProb() : mProbabilityPidAlgorithm->beingKaonMinusProb(), __PROB_SCALE__); 
	mPidProbProton=   pack2UnsignedShort( (charge>0) ? mProbabilityPidAlgorithm->beingProtonProb()   : mProbabilityPidAlgorithm->beingAntiProtonProb(), __PROB_SCALE__); 
      }
    }
  }

  fillMuProbPidTraits(event,track);

  if ( track->outerGeometry() ) 
    mOuterHelix = StMuHelix(track->outerGeometry()->helix(),event->runInfo()->magneticField());
};



StThreeVectorD StMuTrack::dca(const StEvent* event, const StTrack* track) {
  double pathlength = track->geometry()->helix().pathLength( event->primaryVertex()->position() );
  return track->geometry()->helix().at(pathlength)-event->primaryVertex()->position();
}

StThreeVectorD StMuTrack::momentumAtPrimaryVertex(const StEvent* event, const StTrack* track) {
  double pathlength = track->geometry()->helix().pathLength( event->primaryVertex()->position() );
  return track->geometry()->helix().momentumAt(pathlength,event->runInfo()->magneticField()*kilogauss);
}

StPhysicalHelixD StMuTrack::helix() const {return StPhysicalHelixD(mHelix.p(),mHelix.origin(), mHelix.b()*kilogauss, mHelix.q());}  
StPhysicalHelixD StMuTrack::outerHelix() const {return StPhysicalHelixD(mOuterHelix.p(),mOuterHelix.origin(), mOuterHelix.b()*kilogauss, mOuterHelix.q());}  

double StMuTrack::length() const { 
  return fabs( helix().pathLength(StThreeVectorD(mLastPoint)) ); }
double StMuTrack::lengthMeasured() const { 
  return fabs( helix().pathLength(StThreeVectorD(mLastPoint)) - helix().pathLength(StThreeVectorD(mFirstPoint)) ); }

#include "StEvent/StProbPidTraits.h"
void StMuTrack::fillMuProbPidTraits(const StEvent* e, const StTrack* t) {
  // get vector of traits; 
  StPtrVecTrackPidTraits traits = t->pidTraits(kTpcId);
  // get the StDedxPidTraits
  StDedxPidTraits* dedxPidTraits =0;
  unsigned int size = traits.size();
  for (unsigned int i = 0; i < size; i++) {
    if ( !(dedxPidTraits=dynamic_cast<StDedxPidTraits*>(traits[i])) ) continue;
    if (dedxPidTraits->method() == kTruncatedMeanIdentifier)  mProbPidTraits.setdEdxTruncated( dedxPidTraits->mean() ); 
    if (dedxPidTraits->method() == kLikelihoodFitIdentifier)  {
      mProbPidTraits.setdEdxFit( dedxPidTraits->mean() ); 
      mProbPidTraits.setdEdxTrackLength( dedxPidTraits->length() ); 
    }
  }

  // get the StProbPidTraits 
  StProbPidTraits* probPidTraits =0;
  size = traits.size();
  for (unsigned int i = 0; i < size; i++) {
    if ( (probPidTraits=dynamic_cast<StProbPidTraits*>(traits[i])) ) {
      for (int i=0; i<mProbPidTraits.numberOfParticles(); i++) 	mProbPidTraits.setProbability(i,probPidTraits->GetProbability(i));
      mProbPidTraits.setNdf(probPidTraits->GetNDF());
    }
  } 
  
}

ClassImp(StMuTrack)


/***************************************************************************
 *
 * $Log: StMuTrack.cxx,v $
 * Revision 1.6  2003/02/21 14:32:47  laue
 * Yuri's updates to the PID probabilities. dE/dx track length in TPC added
 *
 * Revision 1.5  2002/11/22 18:08:53  laue
 * Bug in logic fixed. Checking for null pointers was wrong.
 *
 * Revision 1.4  2002/11/18 14:29:31  laue
 * update for Yuri's new StProbPidTraits
 *
 * Revision 1.3  2002/09/19 21:54:01  laue
 * fix bug in length() method
 *
 * Revision 1.2  2002/08/20 19:55:49  laue
 * Doxygen comments added
 *
 * Revision 1.1  2002/03/08 17:04:18  laue
 * initial revision
 *
 *
 **************************************************************************/
