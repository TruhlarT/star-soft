// -*- mode: c++;-*-
// $Id: StjBEMC.h,v 1.6 2008/08/04 00:55:26 tai Exp $
// Copyright (C) 2008 Tai Sakuma <sakuma@bnl.gov>
#ifndef STJBEMC_H
#define STJBEMC_H

#include <TObject.h>

#include "StjTowerEnergyList.h"

class StjBEMC : public TObject {

public:
  StjBEMC() { }
  virtual ~StjBEMC() { }

  virtual void Init() { }

  virtual StjTowerEnergyList getEnergyList() = 0;

  ClassDef(StjBEMC, 1)

};

#endif // STJBEMC_H
