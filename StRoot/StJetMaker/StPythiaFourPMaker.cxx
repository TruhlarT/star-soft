// $Id: StPythiaFourPMaker.cxx,v 1.8 2008/08/02 04:03:59 tai Exp $
#include "StPythiaFourPMaker.h"

#include "StMuTrackFourVec.h"

#include "StjMCMuDst.h"

#include "StjMCParticleListCut.h"
#include "StjMCParticleCut.h"
#include "StjMCParticleCutEta.h"
#include "StjMCParticleCutStatus.h"

#include <TLorentzVector.h>

#include <iostream>

using namespace std;
using namespace StSpinJet;
using namespace StJetMCParticleCut;
    
ClassImp(StPythiaFourPMaker)

Int_t StPythiaFourPMaker::Init()
{
  _mc = new StJetMCMuDst(this);
  _cut = new StJetMCParticleListCut();
  _cut->addCut(new MCParticleCutStatus(1));
  _cut->addCut(new MCParticleCutEta(-5.0, 5.0));
  return kStOK;
}

void StPythiaFourPMaker::Clear(Option_t* opt)
{
  for (FourList::iterator it = tracks.begin(); it != tracks.end(); ++it) {
    delete (*it);
  }

  tracks.clear();

  return;
}

Int_t StPythiaFourPMaker::Make()
{
  MCParticleList theList = _mc->getMCPartilceList();

  theList = (*_cut)(theList);

  for(MCParticleList::const_iterator it = theList.begin(); it != theList.end(); ++it) {

    TLorentzVector p4_;
    p4_.SetPtEtaPhiM((*it).pt, (*it).eta, (*it).phi, (*it).m);
			
    StMuTrackFourVec* pmu = new StMuTrackFourVec(0, p4_, 0, (*it).mcparticleId - 1, kUnknownId);
				
    tracks.push_back(pmu);
  }
	
  return kStOK;
}







