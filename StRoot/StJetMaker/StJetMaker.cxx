/***************************************************************************
 *
 * $Id: StJetMaker.cxx,v 1.32 2008/03/27 21:34:07 tai Exp $
 * 
 * Author: Thomas Henry February 2003
 ***************************************************************************
 *
 * Description:  Jet Nano-Dst Creator
 *
 ***************************************************************************
 *
 * Revision 1.0  2003/02/20 thenry
 * StJetMaker was modified and adapted from Akio Ogawa's StppuDstMaker
 * to allow multiple jet analysis modules to be
 * run simultaneosly with various parameters while the Maker loads the events
 * and analyses them.  Four different jet analyzers exist:
 *
 * Konstanin's Analyzers:
 *     Kt type: StppKonstKtJetAnalyzer
 *     Cone type: StppKonstConeJetAnalyzer
 *
 * Mike's Analyzers:
 *     Kt type: StppMikeKtJetAnalyzer
 *     Cone type: StppMikeConeJetAnalyzer
 *
 * These modules all require the StJetFinder modules.
 *
 **************************************************************************/

#include "StJetMaker.h"

//root
#include "TFile.h"
#include "TTree.h"

//St_base
#include "StMessMgr.h"

//StEvent
#include "StEvent.h"

//StMuDstMaker
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"

//StJetFinder
#include "StJetFinder/StProtoJet.h"

//StJetMaker
#include "StJets.h"
#include "StJet.h"
#include "StFourPMakers/StFourPMaker.h"
#include "StFourPMakers/StBET4pMaker.h"
#include "StFourPMakers/StMuEmcPosition.h"

using namespace std;

ClassImp(StJetMaker)
  
StJetMaker::StJetMaker(const Char_t *name, StMuDstMaker* uDstMaker, const char *outputName) 
  : StMaker(name)
  , mAnalyzerCtl(0)
  , mMuDstMaker(uDstMaker)
  , mOutName(outputName)
  , mJetTree(0)
{

}

/*!
  Constructing a new jet analysis requires three elements:
  (1) An instance of StppAnaPars that defines the track and jet cuts used in the analysis.
  See StRoot/StJetMaker/StppJetAnalyzer.h for specifics
  (2) A derived instance of StJetPars (i.e., StConePars or StKtPars) that defines the internal
  parameters used in the jet finding algorithm (e.g., cone radius, etc).  See
  StRoot/StJetFinder/StConeJetFinder.h and StKtCluJetFinder.h for specifics
  (3) A unique character string which is used to identify this branch in the jets TTree

*/
void StJetMaker::addAnalyzer(const StppAnaPars* ap, const StJetPars* jp, StFourPMaker* fp, const char* name)
{
  StppJetAnalyzer* analyzer = new StppJetAnalyzer(ap, jp, fp);

  AnalyzerCtl anaCtl;
  anaCtl.mBranchName = name;
  anaCtl.mAnalyzer = analyzer;
  anaCtl.mJets = new StJets();

  mAnalyzerCtl.push_back(anaCtl);
}

Int_t StJetMaker::Init() 
{
  cout << "StJetMaker: jet output file: " << mOutName << endl;
    
  mOutFile = new TFile(mOutName.c_str(), "recreate");
    
  mJetTree  = new TTree("jet", "jetTree");
  for(std::vector<AnalyzerCtl>::iterator it = mAnalyzerCtl.begin(); it != mAnalyzerCtl.end(); ++it) {
    mJetTree->Branch ((*it).mBranchName.c_str(), "StJets", &((*it).mJets));
  }

  return StMaker::Init();
}

Int_t StJetMaker::Make()
{

  for(std::vector<AnalyzerCtl>::iterator it = mAnalyzerCtl.begin(); it != mAnalyzerCtl.end(); ++it) {
    StppJetAnalyzer* thisAna = (*it).mAnalyzer;
    StJets* jets = (*it).mJets;

    StFourPMaker* fourPMaker = thisAna->fourPMaker();

    thisAna->clear();
	
    thisAna->setFourVec(fourPMaker->getTracks());
    thisAna->findJets();
	
    fillTree(*jets, thisAna, fourPMaker);

  }
    
  mJetTree->Fill();
    
  return kStOk;
}

void StJetMaker::fillTree(StJets& jets, StppJetAnalyzer* thisAna, StFourPMaker* fourPMaker)
{
  jets.Clear();
  jets.setBemcCorrupt(fourPMaker->bemcCorrupt() );

  StMuEvent* event = mMuDstMaker->muDst()->event();
  jets.seteventId(event->eventId());
  jets.seteventNumber(event->eventNumber());
  jets.setrunId(event->runId());
  jets.setrunNumber(event->runNumber());

  StBET4pMaker* bet4p = dynamic_cast<StBET4pMaker*>(fourPMaker);
  if (bet4p) {
    jets.setDylanPoints( bet4p->nDylanPoints() );
    jets.setSumEmcE( bet4p->sumEmcEt() );
  }
	
  StppJetAnalyzer::JetList &cJets = thisAna->getJets();
  for(StppJetAnalyzer::JetList::iterator it = cJets.begin(); it != cJets.end(); ++it) {
    fillJet(jets, *it);
  }
}


void StJetMaker::fillJet(StJets &jets, StProtoJet& pj)
{
  StJet aJet(pj.e(), pj.px(), pj.py(), pj.pz(), 0, 0);
  aJet.zVertex = mMuDstMaker->muDst()->event()->primaryVertexPosition().z();

  StProtoJet::FourVecList &trackList = pj.list();
  for(StProtoJet::FourVecList::iterator it2 = trackList.begin(); it2 != trackList.end(); ++it2)  {
    StMuTrackFourVec *track = dynamic_cast<StMuTrackFourVec*>(*it2);
    if (!track) {
      cout <<"StJets::addProtoJet(). ERROR:\tcast to StMuTrackFourVecFailed.  no action"<<endl;
      return;
    }
    int muTrackIndex = track->getIndex();
    if (muTrackIndex <0) {
      cout <<"Error, muTrackIndex<0. abort()"<<endl;
      abort();
    }
      
    TrackToJetIndex t2j( jets.nJets(), muTrackIndex, track->detectorId() );
    t2j.SetPxPyPzE(track->px(), track->py(), track->pz(), track->e() );
      
    //and cache some properties if it really came from a StMuTrack:
    StMuTrack* muTrack = track->particle();
    if (muTrack) {  //this will fail for calorimeter towers

      double bField(0.5); // to put it in Tesla
      double rad(238.6);// geom->Radius()+5.;

      StThreeVectorD momentumAt, positionAt;
      StMuEmcPosition mMuPosition;
      mMuPosition.trackOnEmc(&positionAt, &momentumAt, muTrack, bField, rad );

      t2j.setCharge( muTrack->charge() );
      t2j.setNhits( muTrack->nHits() );
      t2j.setNhitsPoss( muTrack->nHitsPoss() );
      t2j.setNhitsDedx( muTrack->nHitsDedx() );
      t2j.setNhitsFit( muTrack->nHitsFit() );
      t2j.setNsigmaPion( muTrack->nSigmaPion() );
      t2j.setTdca ( muTrack->dcaGlobal().mag() );
      t2j.setTdcaz ( muTrack->dcaZ() );
      t2j.setTdcaxy ( muTrack->dcaD() );
      t2j.setetaext ( positionAt.pseudoRapidity() );
      t2j.setphiext ( positionAt.phi() );
    }
     
    jets.addTrackToIndex(t2j);

    //ok, get track/tower properties here:
    StDetectorId mDetId = track->detectorId();
    if (mDetId==kTpcId) {
      aJet.nTracks++;
      aJet.tpcEtSum += track->eT();
    }
    else if (mDetId==kBarrelEmcTowerId) {
      aJet.nBtowers++;
      aJet.btowEtSum += track->eT();
    }
    else if (mDetId==kEndcapEmcTowerId) {
      aJet.nEtowers++;
      aJet.etowEtSum += track->eT();
    }
  }

  jets.addJet(aJet);

}

Int_t StJetMaker::Finish()
{
  mOutFile->Write();
  mOutFile->Close();
  delete mOutFile;

  StMaker::Finish();
  return kStOK;
}
