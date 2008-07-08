// -*- mode: c++;-*-
// $Id: CollectEnergyDepositsFromBEMC.h,v 1.7 2008/07/08 23:45:43 tai Exp $
#ifndef COLLECTENERGYDEPOSITSFROMBEMC_H
#define COLLECTENERGYDEPOSITSFROMBEMC_H

#include "TowerEnergyDeposit.h"

#include <TVector3.h>

class StEmcRawHit;
class StMuDstMaker;
class StBemcTables;

namespace StSpinJet {

class StJetBEMC {

public:
  StJetBEMC() { }
  virtual ~StJetBEMC() { }

  virtual TowerEnergyDepositList getEnergyList() = 0;
};

class StJetBEMCMuDst : public StJetBEMC {

public:
  StJetBEMCMuDst(StMuDstMaker* uDstMaker, StBemcTables* bemcTables);
  virtual ~StJetBEMCMuDst() { }

  TowerEnergyDepositList getEnergyList();

private:

  TowerEnergyDeposit readTowerHit(const StEmcRawHit& hit);

  StMuDstMaker* mMuDstMaker;

  StBemcTables* _bemcTables;

};

class CollectEnergyDepositsFromBEMC {

public:
  CollectEnergyDepositsFromBEMC(StMuDstMaker* uDstMaker, StBemcTables* bemcTables);
  virtual ~CollectEnergyDepositsFromBEMC() { }

  void setUse2003Cuts(bool v) { mUse2003Cuts = v; }
  void setUse2005Cuts(bool v) { mUse2005Cuts = v; }

  TowerEnergyDepositList Do();

private:

  TowerEnergyDepositList selectBemcTowerHits(const TowerEnergyDepositList &energyList);
  bool shouldKeepThisBemcHit(const TowerEnergyDeposit& energyDeposit);

  bool accept2003Tower(int id);

  StJetBEMC* _bemc;


  bool mUse2003Cuts;
  bool mUse2005Cuts;

};

}


#endif // COLLECTENERGYDEPOSITSFROMBEMC_H
