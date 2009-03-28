// $Id: StJetMaker.cxx,v 1.70 2009/03/28 06:01:00 pibero Exp $
#include "StJetMaker.h"

#include "StjeParticleCollector.h"
#include "StjeJetFinderRunner.h"
#include "StjeJetCuts.h"
#include "StjeTreeWriter.h"
#include "StjeDefaultJetTreeWriter.h"
#include "StppJetAnalyzer.h"

#include <StJetFinder/StProtoJet.h>

#include <StSpinPool/StJets/StJets.h>

#include <list>

ClassImp(StJetMaker)
  
StJetMaker::StJetMaker(const char* name, StMuDstMaker* uDstMaker, const char* outputName) 
  : StMaker(name)
  , _defaultTreeWriter(new StjeDefaultJetTreeWriter(*uDstMaker, outputName))
  , _treeWriter(_defaultTreeWriter)
  , _backwordCompatibility(new StJetMakerBackwordCompatibility)
{

}

StJetMaker::~StJetMaker()
{
  delete _defaultTreeWriter;
  delete _backwordCompatibility;
}


void StJetMaker::addAnalyzer(const StppAnaPars* ap, StJetPars* jp, StFourPMaker* fp, const char* name)
{
  list<StProtoJet>* protoJetList = new list<StProtoJet>;

  vector<const AbstractFourVec*>* particleList = new vector<const AbstractFourVec*>;

  StJets* stjets = new StJets();

  _particleCollectorList.push_back(new StjeParticleCollector(ap, fp, *particleList));

  _jetFinderList.push_back(new StjeJetFinderRunner(jp, *particleList, *protoJetList));

  _jetCutsList.push_back(new StjeJetCuts(ap, *protoJetList));

  _treeWriter->addJetFinder(fp, particleList, protoJetList, name, stjets);

  _stjetsMap[name] = stjets;

  _backwordCompatibility->addAnalyzer(new StppJetAnalyzer(*protoJetList), _treeWriter, name);
}

void StJetMaker::SetTreeWriter(StjeTreeWriter* treeWriter)
{
  _treeWriter = treeWriter;
}

Int_t StJetMaker::Init() 
{
  for_each(_jetFinderList.begin(), _jetFinderList.end(), mem_fun(&StjeJetFinderRunner::Init));

  _treeWriter->Init();

  return kStOk;
}

Int_t StJetMaker::Make()
{
  for_each(_particleCollectorList.begin(), _particleCollectorList.end(), mem_fun(&StjeParticleCollector::Do));

  for_each(_jetFinderList.begin(), _jetFinderList.end(), mem_fun(&StjeJetFinderRunner::Run));

  for_each(_jetCutsList.begin(), _jetCutsList.end(), mem_fun(&StjeJetCuts::Apply));

  _treeWriter->fillJetTree();

  return kStOk;
}

Int_t StJetMaker::Finish()
{
  _treeWriter->Finish();

  return kStOK;
}

TTree* StJetMaker::tree() const 
{
  return _treeWriter->jetTree();
}
