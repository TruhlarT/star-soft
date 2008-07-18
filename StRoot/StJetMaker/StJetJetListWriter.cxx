// $Id: StJetJetListWriter.cxx,v 1.1 2008/07/18 19:20:07 tai Exp $
#include "StJetJetListWriter.h"

#include <TFile.h>
#include <TTree.h>

#include <iostream>

using namespace std;
using namespace StSpinJet;

StJetJetListWriter::StJetJetListWriter(const char* jetTreeName, const char* jetFourVecTreeName, TDirectory* file)
  : _file(file)
{
  _file->cd();

  _jetTree = new TTree(jetTreeName, jetTreeName);
  _jetTree->SetAutoSave(kMaxLong64);
  _jetTree->SetMaxTreeSize(kMaxLong64);

  _jetTree->Branch("eventId"    , &_jet_eventId      , "eventId/I"       );
  _jetTree->Branch("nJets"      , &_jet_nJets        , "nJets/I"         );
  _jetTree->Branch("jetId"      ,  _jet_jetId        , "jetId[nJets]/I"  );     
  _jetTree->Branch("pt"         ,  _jet_pt           , "pt[nJets]/D"     );
  _jetTree->Branch("eta"        ,  _jet_eta          , "eta[nJets]/D"    );
  _jetTree->Branch("detectorEta",  _jet_detectorEta  , "detectorEta[nJets]/D");    
  _jetTree->Branch("phi"        ,  _jet_phi          , "phi[nJets]/D"    );
  _jetTree->Branch("m"          ,  _jet_m            , "m[nJets]/D"      );
  _jetTree->Branch("vertexZ"    ,  _jet_vertexZ      , "vertexZ[nJets]/D");    
  _jetTree->Branch("runNumber"  , &_jet_runNumber    , "runNumber/I"     );

  _jetFourVecTree = new TTree(jetFourVecTreeName, jetFourVecTreeName);
  _jetFourVecTree->SetAutoSave(kMaxLong64);
  _jetFourVecTree->SetMaxTreeSize(kMaxLong64);

  _jetFourVecTree->Branch("eventId"    , &_four_eventId      , "eventId/I"               );
  _jetFourVecTree->Branch("nFourVecs"  , &_four_nFourVecs    , "nFourVecs/I"             );
  _jetFourVecTree->Branch("jetId"      ,  _four_jetId        , "jetId[nFourVecs]/I"      );     
  _jetFourVecTree->Branch("pt"         ,  _four_pt           , "pt[nFourVecs]/D"         );
  _jetFourVecTree->Branch("eta"        ,  _four_eta          , "eta[nFourVecs]/D"        );
  _jetFourVecTree->Branch("phi"        ,  _four_phi          , "phi[nFourVecs]/D"        );
  _jetFourVecTree->Branch("towerId"    ,  _four_towerId      , "towerId[nFourVecs]/I"    );     
  _jetFourVecTree->Branch("trackId"    ,  _four_trackId      , "trackId[nFourVecs]/S"    );     
  _jetFourVecTree->Branch("m"          ,  _four_m            , "m[nFourVecs]/D"          );
  _jetFourVecTree->Branch("type"       ,  _four_type         , "type[nFourVecs]/I"       );     
  _jetFourVecTree->Branch("detectorId" ,  _four_detectorId   , "detectorId[nFourVecs]/I" );     
  _jetFourVecTree->Branch("fourvecId"  ,  _four_fourvecId    , "fourvecId[nFourVecs]/I"  );     
  _jetFourVecTree->Branch("runNumber"  , &_four_runNumber    , "runNumber/I"     );
}

void StJetJetListWriter::Fill(const JetList& jetList, const FourVecList& fourVecList)
{
  fillJetTree(jetList);
  fillFourVecTree(jetList, fourVecList);
}

void StJetJetListWriter::fillJetTree(const JetList& jetList)
{
  if(jetList.empty()) return;

  _jet_runNumber = jetList[0].runNumber;
  _jet_eventId = jetList[0].eventId;

  _jet_nJets = jetList.size();
  for(int i = 0; i < _jet_nJets; ++i) {
    const Jet& jet = jetList[i];
    _jet_jetId[i]       = jet.jetId;
    _jet_pt[i]          = jet.pt;
    _jet_eta[i]         = jet.eta;
    _jet_phi[i]         = jet.phi;
    _jet_m[i]           = jet.m;
    _jet_vertexZ[i]     = jet.vertexZ;
    _jet_detectorEta[i] = jet.detectorEta;
  }

  _jetTree->Fill();
}

void StJetJetListWriter::fillFourVecTree(const JetList& jetList, const FourVecList& fourVecList)
{
  if(fourVecList.empty()) return;

  _four_runNumber = fourVecList[0].runNumber;
  _four_eventId = fourVecList[0].eventId;

  _four_nFourVecs = fourVecList.size();
  for(int i = 0; i < _four_nFourVecs; ++i) {
    const FourVec& four = fourVecList[i];
    _four_fourvecId[i]  = four.fourvecId;
    _four_jetId[i]      = findJetId(four, jetList);
    _four_type[i]       = four.type;
    _four_detectorId[i] = four.detectorId;
    _four_trackId[i]    = four.trackId;
    _four_towerId[i]    = four.towerId;
    _four_pt[i]         = four.pt;
    _four_eta[i]        = four.eta;
    _four_phi[i]        = four.phi;
    _four_m[i]          = four.m;
    
  }

  _jetFourVecTree->Fill();
}

Int_t StJetJetListWriter::findJetId(const FourVec& four, const JetList& jetList)
{
  for(JetList::const_iterator jet = jetList.begin(); jet != jetList.end(); ++jet) {
    for(FourVecList::const_iterator it = (*jet).fourVecList.begin(); it != (*jet).fourVecList.end(); ++it) {
      if(four.fourvecId == (*it).fourvecId) return (*jet).jetId;
    }
  }
  return 0;
}


void StJetJetListWriter::Finish()
{
  _jetTree->BuildIndex("runNumber", "eventId");
  _jetFourVecTree->BuildIndex("runNumber", "eventId");
}
