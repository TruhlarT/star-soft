// -*- mode: c++;-*-
// $Id: StJetMaker.h,v 1.37 2008/05/01 17:44:50 tai Exp $
#ifndef STJETMAKER_HH
#define STJETMAKER_HH

#include "StMaker.h"

#include "StJetMakerBackwordCompatibility.h"

#include <vector>

class TTree;
class StppJetAnalyzer;
class StMuDstMaker;
class StFourPMaker;
class StJetPars;
class StppAnaPars;

namespace StSpinJet {
  class StJetTreeWriter;
  class StJetFinderRunner;
}

class StJetMaker : public StMaker {

public:

  StJetMaker(const Char_t *name, StMuDstMaker* uDstMaker, const char *outputFile);
    
  Int_t Init();
  Int_t Make();
  Int_t Finish();
    
  TTree* tree() const;
    
  void addAnalyzer(const StppAnaPars*, StJetPars*, StFourPMaker*, const char* anaName);
    
  typedef StSpinJet::StJetMakerBackwordCompatibility::jetBranchesMap jetBranchesMap;
  jetBranchesMap& getJets() const { return _backwordCompatibility->getJets(); }

private:

  std::vector<StSpinJet::StJetFinderRunner*> _jetFinderList;

  StSpinJet::StJetTreeWriter *_treeWriter;

  StSpinJet::StJetMakerBackwordCompatibility *_backwordCompatibility;

  ClassDef(StJetMaker, 0)

};

#endif // STJETMAKER_HH
