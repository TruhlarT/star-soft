// -*- mode: c++;-*-
// $Id: StjJetPrint.h,v 1.5 2008/08/04 06:10:23 tai Exp $
// Copyright (C) 2008 Tai Sakuma <sakuma@bnl.gov>
#ifndef STJJETPRINT_H
#define STJJETPRINT_H

#include <TObject.h>

#include "StjJetList.h"

#include <fstream>
#include <string>

class StjJetPrint : public TObject {

public:

  StjJetPrint() { }
  virtual ~StjJetPrint() { }

  void operator()(const StjJetList& jetList);

private:

  void print(const StjJet& jet);

  ClassDef(StjJetPrint, 1)

};

#endif // STJJETPRINT_H
