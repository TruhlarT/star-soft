// -*- mode: c++;-*-
// $Id: StJetTrgMBWriter.h,v 1.1 2008/07/11 23:32:19 tai Exp $
#ifndef STJETTRGMBWRITER_H
#define STJETTRGMBWRITER_H

#include "StJetTrgWriter.h"

#include <Rtypes.h>

class TDirectory;
class TTree;

class StMuDstMaker;

#include <string>

class StJetTrgMBWriter : public StJetTrgWriter {

public:

  StJetTrgMBWriter(const char *treeName, const char* treeTitle, int trgId, TDirectory* file, StMuDstMaker* uDstMaker)
    : _treeName(treeName), _treeTitle(treeName)
    , _trgId(trgId)
    , _file(file)
    , _uDstMaker(uDstMaker) { }
  virtual ~StJetTrgMBWriter() { }

  void Init();
  void Make();
  void Finish();
    
private:

  std::string _treeName;
  std::string _treeTitle;
  int _trgId;

  TDirectory* _file;
  TTree* _tree;

  Int_t _runNumber;
  Int_t _eventId;
  Int_t _trigID;
  Double_t _prescale;
  Int_t _pass;

  StMuDstMaker* _uDstMaker;
};

#endif // STJETTRGMBWRITER_H
