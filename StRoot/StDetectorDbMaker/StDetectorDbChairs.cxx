#include <assert.h>
#include "StMaker.h"
//________________________________________________________________________________
#include "St_starClockOnlC.h"
St_starClockOnlC *St_starClockOnlC::fgInstance = 0;
ClassImp(St_starClockOnlC);
//________________________________________________________________________________
St_starClockOnlC *St_starClockOnlC::instance() {
  if (fgInstance) return fgInstance;
  St_starClockOnl *table = (St_starClockOnl *) StMaker::GetChain()->GetDataBase("RunLog/onl/starClockOnl");
  assert(table);
  fgInstance = new St_starClockOnlC(table);
  return fgInstance;
}
//________________________________________________________________________________
starClockOnl_st *St_starClockOnlC::Struct(Int_t i) {
  starClockOnl_st *s = ((St_starClockOnl* ) instance()->Table())->GetTable(); 
  Int_t N =  getNumRows();
  if (i >= 0 && i < N) return s + i;
  for (Int_t j = 0; j < N; j++, s++) if (s->frequency > 0) break;
  return s;
}
//________________________________________________________________________________
#include "St_beamInfoC.h"
St_beamInfoC *St_beamInfoC::fgInstance = 0;
ClassImp(St_beamInfoC);

St_beamInfoC *St_beamInfoC::instance() {
  if (fgInstance) return fgInstance;
  St_beamInfo *table = (St_beamInfo *) StMaker::GetChain()->GetDataBase("RunLog/onl/beamInfo");
  assert(table);
  fgInstance = new St_beamInfoC(table);
  return fgInstance;
}
//________________________________________________________________________________
#include "StDetectorDbFTPCGas.h"
StDetectorDbFTPCGas* StDetectorDbFTPCGas::fgInstance = 0; 
#include "St_ftpcGasSystemC.h"
St_ftpcGasSystemC *St_ftpcGasSystemC::fgInstance = 0;
ClassImp(St_ftpcGasSystemC);

St_ftpcGasSystemC *St_ftpcGasSystemC::instance() {
  if (fgInstance) return fgInstance;
  St_ftpcGasSystem *table = (St_ftpcGasSystem *) StMaker::GetChain()->GetDataBase("Calibrations/ftpc/ftpcGasSystem");
  assert(table);
  fgInstance = new St_ftpcGasSystemC(table);
  return fgInstance;
}
//________________________________________________________________________________
#include "St_ftpcGasOutC.h"
St_ftpcGasOutC *St_ftpcGasOutC::fgInstance = 0;
ClassImp(St_ftpcGasOutC);

St_ftpcGasOutC *St_ftpcGasOutC::instance() {
  if (fgInstance) return fgInstance;
  St_ftpcGasOut *table = (St_ftpcGasOut *) StMaker::GetChain()->GetDataBase("Calibrations/ftpc/ftpcGasOut");
  assert(table);
  fgInstance = new St_ftpcGasOutC(table);
  return fgInstance;
}
//________________________________________________________________________________
#include "St_tpcGasC.h"
St_tpcGasC *St_tpcGasC::fgInstance = 0;
ClassImp(St_tpcGasC);

St_tpcGasC *St_tpcGasC::instance() {
  if (fgInstance) return fgInstance;
  St_tpcGas *table = (St_tpcGas *) StMaker::GetChain()->GetDataBase("Calibrations/tpc/tpcGas");
  assert(table);
  fgInstance = new St_tpcGasC(table);
  return fgInstance;
}
//________________________________________________________________________________
#include "St_ftpcVoltageC.h"
St_ftpcVoltageC *St_ftpcVoltageC::fgInstance = 0;
ClassImp(St_ftpcVoltageC);

St_ftpcVoltageC *St_ftpcVoltageC::instance() {
  if (fgInstance) return fgInstance;
  St_ftpcVoltage *table = (St_ftpcVoltage *) StMaker::GetChain()->GetDataBase("Calibrations/ftpc/ftpcVoltage");
  assert(table);
  fgInstance = new St_ftpcVoltageC(table);
  return fgInstance;
}
//________________________________________________________________________________
#include "St_ftpcVoltageStatusC.h"
St_ftpcVoltageStatusC *St_ftpcVoltageStatusC::fgInstance = 0;
ClassImp(St_ftpcVoltageStatusC);

St_ftpcVoltageStatusC *St_ftpcVoltageStatusC::instance() {
  if (fgInstance) return fgInstance;
  St_ftpcVoltageStatus *table = (St_ftpcVoltageStatus *) StMaker::GetChain()->GetDataBase("Calibrations/ftpc/ftpcVoltageStatus");
  assert(table);
  fgInstance = new St_ftpcVoltageStatusC(table);
  return fgInstance;
}
//________________________________________________________________________________
#include "St_tpcGridLeakC.h"
St_tpcGridLeakC *St_tpcGridLeakC::fgInstance = 0;
ClassImp(St_tpcGridLeakC);

St_tpcGridLeakC *St_tpcGridLeakC::instance() {
  if (fgInstance) return fgInstance;
  St_tpcGridLeak *table = (St_tpcGridLeak *) StMaker::GetChain()->GetDataBase("Calibrations/tpc/tpcGridLeak");
  assert(table);
  fgInstance = new St_tpcGridLeakC(table);
  return fgInstance;
}
//________________________________________________________________________________
#include "St_triggerInfoC.h"
St_triggerInfoC *St_triggerInfoC::fgInstance = 0;
ClassImp(St_triggerInfoC);

St_triggerInfoC *St_triggerInfoC::instance() {
  if (fgInstance) return fgInstance;
  St_triggerInfo *table = (St_triggerInfo *) StMaker::GetChain()->GetDataBase("RunLog/onl/triggerInfo");
  assert(table);
  fgInstance = new St_triggerInfoC(table);
  return fgInstance;
}
//________________________________________________________________________________
#include "St_defaultTrgLvlC.h"
St_defaultTrgLvlC *St_defaultTrgLvlC::fgInstance = 0;
ClassImp(St_defaultTrgLvlC);

St_defaultTrgLvlC *St_defaultTrgLvlC::instance() {
  if (fgInstance) return fgInstance;
  St_defaultTrgLvl *table = (St_defaultTrgLvl *) StMaker::GetChain()->GetDataBase("Calibrations/trg/defaultTrgLvl");
  assert(table);
  fgInstance = new St_defaultTrgLvlC(table);
  return fgInstance;
}
//________________________________________________________________________________
#include "St_starMagOnlC.h"
St_starMagOnlC *St_starMagOnlC::fgInstance = 0;
ClassImp(St_starMagOnlC);

St_starMagOnlC *St_starMagOnlC::instance() {
  if (fgInstance) return fgInstance;
  St_starMagOnl *table = (St_starMagOnl *) StMaker::GetChain()->GetDataBase("RunLog/onl/starMagOnl");
  assert(table);
  fgInstance = new St_starMagOnlC(table);
  return fgInstance;
}
//________________________________________________________________________________
#include "StDetectorDbRichScalers.h"
StDetectorDbRichScalers *StDetectorDbRichScalers::fgInstance = 0;
//________________________________________________________________________________
#include "St_trigDetSumsC.h"
St_trigDetSumsC *St_trigDetSumsC::fgInstance = 0;
ClassImp(St_trigDetSumsC);
//________________________________________________________________________________
#include "St_richvoltagesC.h"
St_richvoltagesC *St_richvoltagesC::fgInstance = 0;
ClassImp(St_richvoltagesC);

St_richvoltagesC *St_richvoltagesC::instance() {
  if (fgInstance) return fgInstance;
  St_richvoltages *table = (St_richvoltages *) StMaker::GetChain()->GetDataBase("Calibrations/rich/richvoltages");
  assert(table);
  fgInstance = new St_richvoltagesC(table);
  return fgInstance;
}
//________________________________________________________________________________
#include "St_y1MultC.h"
St_y1MultC *St_y1MultC::fgInstance = 0;
ClassImp(St_y1MultC);

St_y1MultC *St_y1MultC::instance() {
  if (fgInstance) return fgInstance;
  St_y1Mult *table = (St_y1Mult *) StMaker::GetChain()->GetDataBase("Calibrations/rich/y1Mult");
  assert(table);
  fgInstance = new St_y1MultC(table);
  return fgInstance;
}
//________________________________________________________________________________
#include "St_spaceChargeCorC.h"
ClassImp(St_spaceChargeCorC);
St_spaceChargeCorR1C *St_spaceChargeCorR1C::fgInstance = 0;
ClassImp(St_spaceChargeCorR1C);

St_spaceChargeCorR1C *St_spaceChargeCorR1C::instance() {
  if (fgInstance) return fgInstance;
  St_spaceChargeCor *table = (St_spaceChargeCor *) StMaker::GetChain()->GetDataBase("Calibrations/rich/spaceChargeCor");
  assert(table);
  fgInstance = new St_spaceChargeCorR1C(table);
  return fgInstance;
}
//________________________________________________________________________________
St_spaceChargeCorR2C *St_spaceChargeCorR2C::fgInstance = 0;
ClassImp(St_spaceChargeCorR2C);

St_spaceChargeCorR2C *St_spaceChargeCorR2C::instance() {
  if (fgInstance) return fgInstance;
  St_spaceChargeCor *table = (St_spaceChargeCor *) StMaker::GetChain()->GetDataBase("Calibrations/rich/spaceChargeCorR2");
  assert(table);
  fgInstance = new St_spaceChargeCorR2C(table);
  return fgInstance;
}
//________________________________________________________________________________
#include "St_tpcOmegaTauC.h"
St_tpcOmegaTauC *St_tpcOmegaTauC::fgInstance = 0;
ClassImp(St_tpcOmegaTauC);

St_tpcOmegaTauC *St_tpcOmegaTauC::instance() {
  if (fgInstance) return fgInstance;
  St_tpcOmegaTau *table = (St_tpcOmegaTau *) StMaker::GetChain()->GetDataBase("Calibrations/tpc/tpcOmegaTau");
  assert(table);
  fgInstance = new St_tpcOmegaTauC(table);
  return fgInstance;
}
//________________________________________________________________________________
#include "St_tpcRDOMasksC.h"
St_tpcRDOMasksC *St_tpcRDOMasksC::fgInstance = 0;
ClassImp(St_tpcRDOMasksC);

St_tpcRDOMasksC *St_tpcRDOMasksC::instance() {
  if (fgInstance) return fgInstance;
  St_tpcRDOMasks *table = (St_tpcRDOMasks *) StMaker::GetChain()->GetDataBase("RunLog/onl/tpcRDOMasks");
  assert(table);
  fgInstance = new St_tpcRDOMasksC(table);
  return fgInstance;
}
//________________________________________________________________________________
UInt_t       St_tpcRDOMasksC:: getSectorMask(UInt_t sector) {
  UInt_t MASK = 0x0000; // default is to mask it out
  //UInt_t MASK = 0xFFFF; // change to  ON by default ** THIS WAS A HACK
  if(sector < 1 || sector > 24 || getNumRows() == 0){
    LOG_WARN << "St_tpcRDOMasksC:: getSectorMask : return default mask for " 
	     << "sector= " << sector << " getNumRows()=" << getNumRows() << endm;
    return MASK;
  }
  MASK = mask(((sector + 1) / 2) - 1); // does the mapping from sector 1-24 to packed sectors
  if( sector % 2 == 0){ // if its even relevent bits are 6-11
    MASK = MASK >> 6;
  }
  // Otherwise want lower 6 bits    
  MASK &= 0x000003F; // Mask out higher order bits
  return MASK;
}

//________________________________________________________________________________
#include "St_tpcHighVoltagesC.h"
St_tpcHighVoltagesC *St_tpcHighVoltagesC::fgInstance = 0;
ClassImp(St_tpcHighVoltagesC);

St_tpcHighVoltagesC *St_tpcHighVoltagesC::instance() {
  if (fgInstance) return fgInstance;
  St_tpcHighVoltages *table = (St_tpcHighVoltages *) StMaker::GetChain()->GetDataBase("Calibrations/tpc/tpcHighVoltages");
  assert(table);
  fgInstance = new St_tpcHighVoltagesC(table);
  return fgInstance;
}
//________________________________________________________________________________
#include "St_triggerIDC.h"
St_triggerIDC *St_triggerIDC::fgInstance = 0;
ClassImp(St_triggerIDC);

St_triggerIDC *St_triggerIDC::instance() {
  if (fgInstance) return fgInstance;
  St_triggerID *table = (St_triggerID *) StMaker::GetChain()->GetDataBase("RunLog/onl/triggerID");
  assert (table);
  fgInstance = new St_triggerIDC(table);
  return fgInstance;
}
//________________________________________________________________________________
#include "St_trigPrescalesC.h"
St_trigPrescalesC *St_trigPrescalesC::fgInstance = 0;
ClassImp(St_trigPrescalesC);

St_trigPrescalesC *St_trigPrescalesC::instance() {
  if (fgInstance) return fgInstance;
  St_trigPrescales *table = (St_trigPrescales *) StMaker::GetChain()->GetDataBase("RunLog/onl/trigPrescales");
  assert(table);
  fgInstance = new St_trigPrescalesC(table);
  return fgInstance;
}
//________________________________________________________________________________
#include "St_L0TriggerInfoC.h"
St_L0TriggerInfoC *St_L0TriggerInfoC::fgInstance = 0;
ClassImp(St_L0TriggerInfoC);

St_L0TriggerInfoC *St_L0TriggerInfoC::instance() {
  if (fgInstance) return fgInstance;
  St_L0TriggerInfo *table = (St_L0TriggerInfo *) StMaker::GetChain()->GetDataBase("RunLog/onl/L0TriggerInfo");
  assert(table);
  fgInstance = new St_L0TriggerInfoC(table);
  return fgInstance;
}
//________________________________________________________________________________
#include "St_trigL3ExpandedC.h"
St_trigL3ExpandedC *St_trigL3ExpandedC::fgInstance = 0;
ClassImp(St_trigL3ExpandedC);

St_trigL3ExpandedC *St_trigL3ExpandedC::instance() {
  if (fgInstance) return fgInstance;
  St_trigL3Expanded *table = (St_trigL3Expanded *) StMaker::GetChain()->GetDataBase("RunLog/onl/trigL3Expanded");
  assert(table);
  fgInstance = new St_trigL3ExpandedC(table);
  return fgInstance;
}
//________________________________________________________________________________
#include "St_dsmPrescalesC.h"
St_dsmPrescalesC *St_dsmPrescalesC::fgInstance = 0;
ClassImp(St_dsmPrescalesC);

St_dsmPrescalesC *St_dsmPrescalesC::instance() {
  if (fgInstance) return fgInstance;
  St_dsmPrescales *table = (St_dsmPrescales *) StMaker::GetChain()->GetDataBase("RunLog/onl/dsmPrescales");
  assert(table);
  fgInstance = new St_dsmPrescalesC(table);
  return fgInstance;
}
//________________________________________________________________________________
#include "St_additionalTriggerIDC.h"
St_additionalTriggerIDC *St_additionalTriggerIDC::fgInstance = 0;
ClassImp(St_additionalTriggerIDC);

St_additionalTriggerIDC *St_additionalTriggerIDC::instance() {
  if (fgInstance) return fgInstance;
  St_additionalTriggerID *table = (St_additionalTriggerID *) StMaker::GetChain()->GetDataBase("RunLog/onl/additionalTriggerID");
  assert (table);
  fgInstance = new St_additionalTriggerIDC(table);
  return fgInstance;
}
//________________________________________________________________________________
#include "StDetectorDbTriggerID.h"
StDetectorDbTriggerID *StDetectorDbTriggerID::fgInstance = 0;
//________________________________________________________________________________
map<Int_t,Float_t> StDetectorDbTriggerID::getTotalPrescales() {
  map<Int_t,Float_t> value;
  // First walk forward through the multiple levels of prescales
  for (UInt_t irow=0;irow<getDsmPrescalesNumRows(); ++irow) {
    Int_t trgId = getDsmPrescalesTrgId(irow);
    value[trgId] = Float_t(getDsmPrescalesDsmPrescale(irow));
  }
  
  for (UInt_t irow=0; irow<getL0NumRows(); ++irow) {
    Int_t trgId = getL0OfflineTrgId(irow);
    map<Int_t,Float_t>::iterator p=value.find(trgId);
    if (p != value.end()) {
      (*p).second *= Float_t(getPsL0(irow));
    }
    else {
      value[trgId] = Float_t(getPsL0(irow));
    }
  }
  // For completeness: this one is always unity as far as I can tell
  for (UInt_t irow=0; irow<getSNumRows(); ++irow) {
    UInt_t idxTrigger = getIdxTrigger(irow);
    Int_t trgId = 0;
    for (UInt_t jrow=0; jrow<getIDNumRows(); ++jrow) {
      if (idxTrigger == getIdxTrg(jrow)) {
	trgId = getOfflineTrgId(jrow);
	break;
      }
    }
    map<Int_t,Float_t>::iterator p=value.find(trgId);
    
    if (p != value.end()) {
      (*p).second *= Float_t(getPs(irow));
    }
    else {
      value[trgId] = Float_t(getPs(irow));
    }
  }
  
  // Now deal with L3Expanded
  for (UInt_t irow=0; irow<getTrigL3ExpandedNumRows(); ++irow) {
    Int_t oldtid = getTrigL3ExpandedL3TrgId(irow);
    Int_t newtid = getTrigL3ExpandedL3ExpandedTrgId(irow);
    Float_t l2ps = getTrigL3ExpandedL2Ps(irow);
    
    map<Int_t,Float_t>::iterator p = value.find(oldtid);
    if (p!= value.end()) {
      value[newtid] = ((*p).second)*l2ps;
    }
    else {
      value[newtid] = l2ps;
    }
    
  }
  return value;
}
//________________________________________________________________________________
Float_t StDetectorDbTriggerID::getTotalPrescaleByTrgId(Int_t trgId) {
  map<Int_t,Float_t> theMap = getTotalPrescales();
  map<Int_t,Float_t>::const_iterator p = theMap.find(trgId);
  if (p != theMap.end()) {
    return (*p).second;
  }
  else {
    return 0;
  }
}
#include "StDetectorDbIntegratedTriggerID.h"
//________________________________________________________________________________
StDetectorDbIntegratedTriggerID *StDetectorDbIntegratedTriggerID::fgInstance = 0;
