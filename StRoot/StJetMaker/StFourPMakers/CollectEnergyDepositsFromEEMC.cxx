// $Id: CollectEnergyDepositsFromEEMC.cxx,v 1.3 2008/07/08 10:35:30 tai Exp $
#include "CollectEnergyDepositsFromEEMC.h"

#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StMuDSTMaker/COMMON/StMuEmcCollection.h"

#include "StEEmcDbMaker/StEEmcDbMaker.h"
#include "StEEmcDbMaker/EEmcDbItem.h"
#include "StEEmcUtil/EEmcGeom/EEmcGeomSimple.h"


namespace StSpinJet {

CollectEnergyDepositsFromEEMC::CollectEnergyDepositsFromEEMC(StMuDstMaker* uDstMaker)
  : mMuDstMaker(uDstMaker)
{

}

void CollectEnergyDepositsFromEEMC::Init(StEEmcDbMaker* eedb)
{
  mEeGeom = new EEmcGeomSimple();
  mEeDb = eedb;
  mEeDb->setThreshold(3);
}

TowerEnergyDepositList CollectEnergyDepositsFromEEMC::Do()
{
  StMuEmcCollection* muEmc = mMuDstMaker->muDst()->muEmcCollection();

  TowerEnergyDepositList ret;

  for (int id = 0; id < muEmc->getNEndcapTowerADC(); ++id) {

    int rawadc, sec, sub, etabin;
    muEmc->getEndcapTowerADC(id, rawadc, sec, sub, etabin);
    assert(sec >0 && sec <= MaxSectors);
	
    const EEmcDbItem *dbItem = mEeDb->getT(sec,sub-1+'A',etabin);
    assert(dbItem); 
	
    if(dbItem->fail) continue; //drop broken channels
    if(dbItem->stat) continue; // drop not working channels and jumpy pedestal channels
    if(dbItem->gain<=0.) continue; // drop it, unless you work with ADC spectra
    if(rawadc<dbItem->thr) continue; // drop raw ADC < ped+N*sigPed, N==3 in init
	    
    double adc = rawadc - (dbItem->ped);
    double energy = adc/(dbItem->gain);
    if(energy < 0.01) continue; // drop if less than 10MeV for now
	    
    TowerEnergyDeposit energyDeposit;
    energyDeposit.detectorId = kEndcapEmcTowerId;
    energyDeposit.towerId = (sec*5 + sub)*12 + etabin;


    TVector3 towerLocation = mEeGeom->getTowerCenter(sec-1,sub-1,etabin-1);
    energyDeposit.towerLocation = towerLocation;
    energyDeposit.towerX = towerLocation.x();
    energyDeposit.towerY = towerLocation.y();
    energyDeposit.towerZ = towerLocation.z();

    StThreeVectorF vertex = mMuDstMaker->muDst()->event()->primaryVertexPosition();
    energyDeposit.vertex = TVector3(vertex.x(), vertex.y(), vertex.z());

    energyDeposit.vertexX = vertex.x();
    energyDeposit.vertexY = vertex.y();
    energyDeposit.vertexZ = vertex.z(); 

    energyDeposit.energy   = energy;
    energyDeposit.adc      = rawadc;
    energyDeposit.pedestal = dbItem->ped;
    energyDeposit.rms      = 0.0;
    energyDeposit.status   = dbItem->stat;

    ret.push_back(energyDeposit);

  }

  return ret;
}

}
