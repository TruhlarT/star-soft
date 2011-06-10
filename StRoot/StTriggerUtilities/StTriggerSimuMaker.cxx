//////////////////////////////////////////////////////////////////////////
//
//
// StTriggerSimuMaker R.Fatemi, Adam Kocoloski , Jan Balewski  (Fall, 2007)
//
// Goal: generate trigger response based on ADC
// implemented BEMC,EEMC,....
// >StTriggerSimu/*SUB*/St*SUB*TriggerSimu.h
// >where *SUB* are the subsystems: Eemc, Bemc, Bbc,.... 
// > L2 is served by a separate maker
//
//////////////////////////////////////////////////////////////////////////

// $Id: StTriggerSimuMaker.cxx,v 1.45 2011/06/10 18:56:18 pibero Exp $

// MySQL C API
#include "mysql.h"

// DSM crates
#include "RTS/trg/include/trgConfNum.h"
#include "StDSMUtilities/StDSM2009Utilities.hh"

#include <Stiostream.h>
#include "StChain.h"
#include "TFile.h"
#include <math.h>

#include <fstream>
#include "StEmcUtil/database/StEmcDecoder.h"

#include "St_db_Maker/St_db_Maker.h" // just for time stamp
#include "Eemc/EMCdsm2Tree.h"// to access Etot

//StEvent
#include "StEvent/StEvent.h"

//get  EEMC
#include "Eemc/StEemcTriggerSimu.h"
#include "Eemc/EemcHttpInfo.h"
#include "Eemc/EEfeeTPTree.h" // for printouts only
#include "Eemc/EEfeeTP.h"  // for printouts only

//get BEMC
#include "StTriggerUtilities/Bemc/StBemcTriggerSimu.h"
#include "StEmcRawMaker/StBemcTables.h"
#include "StEmcUtil/geometry/StEmcGeom.h"

//get EMC
#include "StTriggerUtilities/Emc/StEmcTriggerSimu.h"

//get BBC
#include "Bbc/StBbcTriggerSimu.h"

//get L2
#include "L2Emulator/StL2TriggerSimu.h"

//get HEAD Maker
#include "StTriggerSimuMaker.h"
#include "StTriggerSimuResult.h"

// Trigger definition
#include "TBufferFile.h"
#include "tables/St_triggerDefinition_Table.h"
#include "StTriggerDefinition.h"

// Trigger threshold
#include "tables/St_triggerThreshold_Table.h"
#include "StTriggerThreshold.h"

ClassImp(StTriggerSimuMaker)

StTriggerSimuMaker::StTriggerSimuMaker(const char *name):StMaker(name) {
    mDbMk = dynamic_cast<St_db_Maker*> ( this->GetMakerInheritsFrom("St_db_Maker") );
    mYear=-1;
    mMCflag=0;
    eemc=0;
    bbc=0;
    bemc=0;
    lTwo=0;
    mHList=0;
    emc = new StEmcTriggerSimu;
    for (int a=0; a<numSimulators; a++){
      mSimulators[a]=0;
    }

    fill(mBarrelJetPatchTh,mBarrelJetPatchTh+3,-1);
    fill(mBarrelHighTowerTh,mBarrelHighTowerTh+4,-1);

    fill(mEndcapJetPatchTh,mEndcapJetPatchTh+3,-1);
    fill(mEndcapHighTowerTh,mEndcapHighTowerTh+2,-1);

    fill(mOverlapJetPatchTh,mOverlapJetPatchTh+3,-1);

    mChangeJPThresh = 0;
}

StTriggerSimuMaker::~StTriggerSimuMaker() { /* no-op */ }


void StTriggerSimuMaker::useEemc(int flag){
    eemc=new StEemcTriggerSimu();
    eemc->setConfig(flag);
    mSimulators[0]=eemc;
}

void StTriggerSimuMaker::useBbc(){
    bbc=new StBbcTriggerSimu;
    mSimulators[1]=bbc;
}

void StTriggerSimuMaker::useBemc(){
    bemc=new StBemcTriggerSimu;
    bemc->setHeadMaker(this);
    mSimulators[2]=bemc;
}

void StTriggerSimuMaker::useL2(StGenericL2Emulator* L2Mk){
    lTwo=new StL2TriggerSimu(L2Mk);
    mSimulators[4]=lTwo;

}

void StTriggerSimuMaker::useL2(StGenericL2Emulator2009* L2Mk){
    lTwo=new StL2TriggerSimu(L2Mk);
    mSimulators[4]=lTwo;

}

Int_t StTriggerSimuMaker::Init() {
    LOG_INFO <<Form("StTriggerSimuMaker::Init(), MCflag=%d",mMCflag)<<endm;
    if(eemc) {
        eemc->setHList(mHList);
    }

    if(bemc) {
        bemc->setHList(mHList);
    }

    for(Int_t i=0; i<numSimulators; i++) {
      if(mSimulators[i]){  
        mSimulators[i]->setMC(mMCflag);
        mSimulators[i]->Init();
      }

    }


    return StMaker::Init();
}

void StTriggerSimuMaker::Clear(const Option_t*){
    LOG_DEBUG<<"StTriggerSimuMaker::Clear()"<<endm;
    
    for(Int_t i=0; i<numSimulators; i++) {
      if (mSimulators[i]){
        mSimulators[i]->Clear();
      }
    }
    
    mResults.clear();
}

Int_t StTriggerSimuMaker::InitRun(int runNumber) {
    assert(mDbMk);
    mYear = mDbMk->GetDateTime().GetYear();
    int yyyymmdd = mDbMk->GetDateTime().GetDate(); //form of 19971224 (i.e. 24/12/1997)
    int hhmmss = mDbMk->GetDateTime().GetTime(); //form of 123623 (i.e. 12:36:23)
    LOG_INFO << Form("InitRun() run=%d yyyymmdd=%d  hhmmss=%06d\n", runNumber, yyyymmdd, hhmmss) << endm;

    //Use unified EMC trigger for EEMC/BEMC triggers in y=2009 or later
    if (mYear >= 2009 && (mSimulators[0] || mSimulators[2])) {
      emc->setHeadMaker(this);
      emc->setBemc(bemc);
      emc->setEemc(eemc);
      emc->setMC(mMCflag);
      mSimulators[3] = emc;
      if (!get2009DsmRegistersFromOfflineDatabase(runNumber) && !get2009DsmRegistersFromOnlineDatabase(runNumber)) {
	LOG_WARN << "Can't get 2009 DSM registers" << endm;
      }
    }

    for (Int_t i = 0; i < numSimulators; ++i)
      if (mSimulators[i])
	mSimulators[i]->InitRun(runNumber);

    return kStOK;
}

Int_t StTriggerSimuMaker::Make() {
   
  for(Int_t i=0; i<numSimulators; i++) {
    if (mSimulators[i]){
      mSimulators[i]->Make();
    }
  }

  vector<int> trigIds = triggerIds();
  TString line = "Triggers: ";
  for (size_t i = 0; i < trigIds.size(); ++i) {
    line += Form("%d ",trigIds[i]);
    buildDetailedResult(trigIds[i]);
  }
  LOG_DEBUG << line << endm;

  return kStOK;
}

bool StTriggerSimuMaker::isTrigger(int trigId) {

  for(Int_t i=0; i<numSimulators; i++) {
    if (mSimulators[i] && mSimulators[i]->triggerDecision(trigId) == kNo) return false;
  }
  
  return true;
}

vector<int> StTriggerSimuMaker::triggerIds() const
{
  vector<int> v;

  if (mYear < 2009) {
    if (bemc) copy(bemc->triggerIds().begin(),bemc->triggerIds().end(),back_inserter(v));
    if (eemc) copy(eemc->triggerIds().begin(),eemc->triggerIds().end(),back_inserter(v));
  }
  else {
    set<int> s = emc->triggerIds();
    copy(s.begin(),s.end(),back_inserter(v));
  }

  return v;
}

bool StTriggerSimuMaker::isTriggerDefined(int trigId)
{

  bool TrigDefined;
  
  TrigDefined = false;

  if (mYear < 2009) {
    if (bemc) {
      vector<int> b = bemc->triggerIds();
      for (size_t i = 0; i < b.size(); ++i) {
	if (trigId==b[i]) TrigDefined=true;
      }
    }
    if (eemc) {
      vector<int> e = bemc->triggerIds();
      for (size_t i = 0; i < e.size(); ++i) {
	if (trigId==e[i]) TrigDefined=true;
      }
    }
  }
  else {
    set<int> s = emc->triggerIds();
    if (s.count(trigId)>0) TrigDefined = true; 
  }
  
  
  return TrigDefined;
}


void StTriggerSimuMaker::buildDetailedResult(int trigId) {
    StTriggerSimuResult& result = mResults[trigId];
    result.setTriggerId(trigId);
    if(bbc) {
        result.setBbcDecision(bbc->triggerDecision(trigId));
    }
    if(bemc) {
        result.setBemcDecision(bemc->triggerDecision(trigId));

        if(bemc->triggerDecision(trigId)==1) {
            // Record HTs above Threshold
            vector< pair<int,int> > Towers=bemc->getTowersAboveThreshold(trigId);
            for(vector< pair<int,int> >::iterator itr=Towers.begin(); itr!=Towers.end(); itr++){
                result.addHighTower((*itr).first,(*itr).second);
            }
            // Record TPs above Threshold
            vector< pair<int,int> > tPatches=bemc->getTriggerPatchesAboveThreshold(trigId);
            for(vector< pair<int,int> >::iterator itr=tPatches.begin(); itr!=tPatches.end(); itr++){
                result.addTriggerPatch((*itr).first,(*itr).second);
            }
            // Record JPs above Threshold
            vector< pair<int,int> > jPatches=bemc->getJetPatchesAboveThreshold(trigId);
            for(vector< pair<int,int> >::iterator itr=jPatches.begin(); itr!=jPatches.end(); itr++){
                result.addJetPatch((*itr).first,(*itr).second);	    
            }
        }
    }
    if(eemc) {
        result.setEemcDecision(eemc->triggerDecision(trigId));
    }
    if (emc) {
    }
    if(lTwo) {
        result.setL2Decision(lTwo->triggerDecision(trigId));
        result.setL2Result(lTwo->result());
    }
}

Int_t StTriggerSimuMaker::Finish() {
  return StMaker::Finish();
}

bool StTriggerSimuMaker::get2009DsmRegistersFromOfflineDatabase(int runNumber)
{
  return getTriggerDefinitions(runNumber) && getTriggerThresholds(runNumber);
}

bool StTriggerSimuMaker::getTriggerDefinitions(int runNumber)
{
  TDataSet* DB = GetInputDB("Calibrations/trg");
  if (DB) {
    St_triggerDefinition* desc = dynamic_cast<St_triggerDefinition*>(DB->Find("triggerDefinition"));
    if (desc) {
      triggerDefinition_st* table = desc->GetTable();
      LOG_INFO << setw(20) << "triggerIndex"
	       << setw(20) << "name"
	       << setw(20) << "triggerId"
	       << setw(20) << "onbits"
	       << setw(20) << "offbits"
	       << setw(20) << "onbits1"
	       << setw(20) << "onbits2"
	       << setw(20) << "onbits3"
	       << setw(20) << "offbits1"
	       << setw(20) << "offbits2"
	       << setw(20) << "offbits3"
	       << endm;
      TBufferFile buf(TBuffer::kRead);
      buf.SetBuffer(table[0].trigdef,sizeof(table[0].trigdef),false);
      TObjArray* a = 0;
      buf >> a;
      for (int i = 0; i < a->GetEntriesFast(); ++i) {
	StTriggerDefinition* trigdef = dynamic_cast<StTriggerDefinition*>(a->At(i));
	LOG_INFO << setw(20) << trigdef->triggerIndex
		 << setw(20) << trigdef->name
		 << setw(20) << trigdef->triggerId
		 << setw(20) << trigdef->onbits
		 << setw(20) << trigdef->offbits
		 << setw(20) << trigdef->onbits1
		 << setw(20) << trigdef->onbits2
		 << setw(20) << trigdef->onbits3
		 << setw(20) << trigdef->offbits1
		 << setw(20) << trigdef->offbits2
		 << setw(20) << trigdef->offbits3
		 << endm;
	TriggerDefinition trigDef;
	trigDef.triggerIndex = trigdef->triggerIndex;
	strcpy(trigDef.name,trigdef->name.Data());
	trigDef.triggerId = trigdef->triggerId;
	trigDef.onbits = trigdef->onbits;
	trigDef.offbits = trigdef->offbits;
	trigDef.onbits1 = trigdef->onbits1;
	trigDef.onbits2 = trigdef->onbits2;
	trigDef.onbits3 = trigdef->onbits3;
	trigDef.offbits1 = trigdef->offbits1;
	trigDef.offbits2 = trigdef->offbits2;
	trigDef.offbits3 = trigdef->offbits3;
	emc->defineTrigger(trigDef);
      }
      a->Delete();
      return true;
    }
  }
  return false;
}

bool StTriggerSimuMaker::getTriggerThresholds(int runNumber)
{
  TDataSet* DB = GetInputDB("Calibrations/trg");
  if (DB) {
    St_triggerThreshold* desc = dynamic_cast<St_triggerThreshold*>(DB->Find("triggerThreshold"));
    if (desc) {
      triggerThreshold_st* table = desc->GetTable();
      LOG_INFO << setw(20) << "object"
	       << setw(20) << "index"
	       << setw(20) << "reg"
	       << setw(20) << "label"
	       << setw(20) << "value"
	       << setw(20) << "defaultvalue"
	       << endm;
      TBufferFile buf(TBuffer::kRead);
      buf.SetBuffer(table[0].trigthr,sizeof(table[0].trigthr),false);
      TObjArray* a = 0;
      buf >> a;
      for (int i = 0; i < a->GetEntriesFast(); ++i) {
	StTriggerThreshold* trigthr = dynamic_cast<StTriggerThreshold*>(a->At(i));
	LOG_INFO << setw(20) << trigthr->object
		 << setw(20) << trigthr->index
		 << setw(20) << trigthr->reg
		 << setw(20) << trigthr->label
		 << setw(20) << trigthr->value
		 << setw(20) << trigthr->defaultvalue
		 << endm;
	int value = trigthr->value;
	if (value == -1) value = trigthr->defaultvalue;
	switch (trigthr->object) {
	case L1_CONF_NUM:
	  switch (trigthr->index) {
	  case 20:                // EM201
	    emc->get2009_DSMLayer2_Result()->setRegister(trigthr->reg,value);
	    break;
	  case 30:                // LD301
	    emc->get2009_DSMLayer3_Result()->setRegister(trigthr->reg,value);
	    break;
	  }
	  break;
	case BC1_CONF_NUM:
	  switch (trigthr->index) {
	  case 21:                // EE101
	    eemc->get2009_DSMLayer1_Result()->setRegister(trigthr->reg,value);
	    break;
	  case 23:                // EE001
	    eemc->get2009_DSMLayer0_Result()->setRegister(trigthr->reg,value);
	    break;
	  case 33:                // BC101
	    bemc->get2009_DSMLayer1_Result()->setRegister(trigthr->reg,value);
	    break;
	  }
	  break;
	case BCW_CONF_NUM:
	  switch (trigthr->index) {
	  case 16:                // BW001
	    for (int dsm = 0; dsm < 15; ++dsm)
	      (*bemc->get2009_DSMLayer0_Result())[dsm].registers[trigthr->reg] = value;
	    break;
	  }
	  break;
	case BCE_CONF_NUM:
	  switch (trigthr->index) {
	  case 16:                // BE001
	    for (int dsm = 15; dsm < 30; ++dsm)
	      (*bemc->get2009_DSMLayer0_Result())[dsm].registers[trigthr->reg] = value;
	    break;
	  }
	  break;
	}
      }
      a->Delete();
      return true;
    }
  }
  return false;
}

bool StTriggerSimuMaker::get2009DsmRegistersFromOnlineDatabase(int runNumber)
{
  // Open connection to Run 9 database

  MYSQL mysql;
  const char* host = "dbbak.starp.bnl.gov";
  const char* user = "";
  const char* pass = "";
  unsigned int port = 3408;
  const char* database = "Conditions_rts";
  const char* unix_socket = NULL;
  unsigned long client_flag = 0;
  TString query;

  LOG_INFO << Form("host=%s user=\"%s\" pass=\"%s\" port=%d database=%s",host,user,pass,port,database) << endm;

  mysql_init(&mysql);

  if (!mysql_real_connect(&mysql,host,user,pass,database,port,unix_socket,client_flag)) {
    LOG_WARN << "Can't connect to database: " << mysql_error(&mysql) << endm;
    return false;
  }

  // For simulation, get run number from DB time stamp

  if (mMCflag == 1) {
    //query = Form("select idx_rn from triggers where beginTime >= '%s' limit 1",GetDBTime().AsSQLString());
    query = Form("select max(idx_rn) from triggers where beginTime <= '%s'",GetDBTime().AsSQLString());
    LOG_INFO << query << endm;
    mysql_query(&mysql,query);

    if (MYSQL_RES* result = mysql_store_result(&mysql)) {
      while (MYSQL_ROW row = mysql_fetch_row(result)) {
        runNumber = atoi(row[0]);
      }
    }
    LOG_INFO << "DB Time = " << GetDBTime().AsSQLString() << endm;
    LOG_INFO << "Run Number = " << runNumber << endm;
  }

  // object=DSM crate, idx=DSM board
  query = Form("select object,idx,reg,label,value,defaultvalue from dict where hash=(select dicthash from run where idx_rn = %d)",runNumber);
  LOG_INFO << query << endm;
  mysql_query(&mysql,query);

  if (MYSQL_RES* result = mysql_store_result(&mysql)) {
    LOG_INFO << setw(10) << "object"
	     << setw(10) << "idx"
	     << setw(10) << "reg"
	     << setw(30) << "label"
	     << setw(10) << "value"
	     << setw(15) << "defaultvalue"
	     << endm;

    while (MYSQL_ROW row = mysql_fetch_row(result)) {
      int object = atoi(row[0]);
      int idx = atoi(row[1]);
      int reg = atoi(row[2]);
      TString label = row[3];
      int value = atoi(row[4]);
      int defaultvalue = atoi(row[5]);

      LOG_INFO << setw(10) << object
	       << setw(10) << idx
	       << setw(10) << reg
	       << setw(30) << label
	       << setw(10) << value
	       << setw(15) << defaultvalue
	       << endm;

      if (value == -1) value = defaultvalue;

      switch (object) {
      case L1_CONF_NUM:
	switch (idx) {
	case 20:		// EM201
	  emc->get2009_DSMLayer2_Result()->setRegister(reg,value);
	  break;
	case 30:		// LD301
	  emc->get2009_DSMLayer3_Result()->setRegister(reg,value);
	  break;
	}
	break;
      case BC1_CONF_NUM:
	switch (idx) {
	case 21:		// EE101
	  eemc->get2009_DSMLayer1_Result()->setRegister(reg,value);
	  break;
	case 23:		// EE001
	  eemc->get2009_DSMLayer0_Result()->setRegister(reg,value);
	  break;
	case 33:		// BC101
	  bemc->get2009_DSMLayer1_Result()->setRegister(reg,value);
	  break;
	}
	break;
      case BCW_CONF_NUM:
	switch (idx) {
	case 16:		// BW001
	  for (int dsm = 0; dsm < 15; ++dsm)
	    (*bemc->get2009_DSMLayer0_Result())[dsm].registers[reg] = value;
	  break;
	}
	break;
      case BCE_CONF_NUM:
	switch (idx) {
	case 16:		// BE001
	  for (int dsm = 15; dsm < 30; ++dsm)
	    (*bemc->get2009_DSMLayer0_Result())[dsm].registers[reg] = value;
	  break;
	}
	break;
      }
    }
    mysql_free_result(result);
  }

  LOG_INFO << "The following registers have new values:" << endm;

  // Shift all JP thresholds by mChangeJPThresh
  if (mChangeJPThresh) {
    for (int reg = 0; reg < 3; ++reg) {
      int value = bemc->get2009_DSMLayer1_Result()->getRegister(reg);
      value += mChangeJPThresh;
      LOG_INFO << setw(20) << reg
	       << setw(30) << "BEMC-JP-th" << reg
	       << setw(20) << value
	       << endm;
      bemc->get2009_DSMLayer1_Result()->setRegister(reg,value);
    }

    for (int reg = 0; reg < 3; ++reg) {
      int value = eemc->get2009_DSMLayer1_Result()->getRegister(reg);
      value += mChangeJPThresh;
      LOG_INFO << setw(20) << reg
	       << setw(30) << "EEMC-JP-th" << reg
	       << setw(20) << value
	       << endm;
      eemc->get2009_DSMLayer1_Result()->setRegister(reg,value);
    }

    for (int reg = 0; reg < 3; ++reg) {
      int value = emc->get2009_DSMLayer2_Result()->getRegister(reg);
      value += mChangeJPThresh;
      LOG_INFO << setw(20) << reg
	       << setw(30) << "BEMC-EEMC-overlap-JP-th" << reg
	       << setw(20) << value
	       << endm;
      emc->get2009_DSMLayer2_Result()->setRegister(reg,value);
    }
  }

  // Overwrite thresholds from database if set explicitly
  for (int reg = 0; reg < 3; ++reg) {
    int value = mBarrelJetPatchTh[reg];
    if (value != -1) {
      LOG_INFO << setw(20) << reg
	       << setw(30) << "BEMC-JP-th" << reg
	       << setw(20) << value
	       << endm;
      bemc->get2009_DSMLayer1_Result()->setRegister(reg,value);
    }
  }

  for (int reg = 0; reg < 4; ++reg) {
    int value = mBarrelHighTowerTh[reg];
    if (value != -1) {
      LOG_INFO << setw(20) << reg
	       << setw(30) << "BEMC-HT-th" << reg
	       << setw(20) << value
	       << endm;
      bemc->get2009_DSMLayer0_Result()->setRegister(reg,value);
    }
  }

  for (int reg = 0; reg < 3; ++reg) {
    int value = mEndcapJetPatchTh[reg];
    if (value != -1) {
      LOG_INFO << setw(20) << reg
	       << setw(30) << "EEMC-JP-th" << reg
	       << setw(20) << value
	       << endm;
      eemc->get2009_DSMLayer1_Result()->setRegister(reg,value);
    }
  }

  for (int reg = 0; reg < 2; ++reg) {
    int value = mEndcapHighTowerTh[reg];
    if (value != -1) {
      LOG_INFO << setw(20) << reg
	       << setw(30) << "EEMC-HT-th" << reg
	       << setw(20) << value
	       << endm;
      eemc->get2009_DSMLayer0_Result()->setRegister(reg,value);
    }
  }

  for (int reg = 0; reg < 3; ++reg) {
    int value = mOverlapJetPatchTh[reg];
    if (value != -1) {
      LOG_INFO << setw(20) << reg
	       << setw(30) << "BEMC-EEMC-overlap-JP-th" << reg
	       << setw(20) << value
	       << endm;
      emc->get2009_DSMLayer2_Result()->setRegister(reg,value);
    }
  }

  // Trigger definitions

  TriggerDefinition triggers[32];

  query = Form("select idx_trigger,name,offlineBit from triggers where idx_rn = %d", runNumber);
  LOG_INFO << query << endm;
  mysql_query(&mysql,query);

  if (MYSQL_RES* result = mysql_store_result(&mysql)) {
    while (MYSQL_ROW row = mysql_fetch_row(result)) {
      int idx_trigger = atoi(row[0]);
      triggers[idx_trigger].triggerIndex = idx_trigger;
      strcpy(triggers[idx_trigger].name,row[1]);
      triggers[idx_trigger].triggerId = atoi(row[2]);
    }
    mysql_free_result(result);
  }

  query = Form("select idx_idx,onbits,offbits,onbits1,onbits2,onbits3,offbits1,offbits2,offbits3 from pwc where idx_rn = %d", runNumber);
  LOG_INFO << query << endm;
  mysql_query(&mysql,query);

  if (MYSQL_RES* result = mysql_store_result(&mysql)) {
    LOG_INFO << setw(20) << "idx_trigger"
             << setw(20) << "name"
             << setw(20) << "offlineBit"
             << setw(20) << "onbits"
             << setw(20) << "offbits"
             << setw(20) << "onbits1"
             << setw(20) << "onbits2"
             << setw(20) << "onbits3"
             << setw(20) << "offbits1"
             << setw(20) << "offbits2"
             << setw(20) << "offbits3"
             << endm;

    while (MYSQL_ROW row = mysql_fetch_row(result)) {
      int idx_trigger = atoi(row[0]);
      triggers[idx_trigger].onbits = atoi(row[1]);
      emc->defineTrigger(triggers[idx_trigger]);
      LOG_INFO << setw(20) << idx_trigger
               << setw(20) << triggers[idx_trigger].name
               << setw(20) << triggers[idx_trigger].triggerId
               << setw(20) << Form("0x%08x",triggers[idx_trigger].onbits)
               << setw(20) << Form("0x%08x",triggers[idx_trigger].offbits)
               << setw(20) << Form("0x%08x",triggers[idx_trigger].onbits1)
               << setw(20) << Form("0x%08x",triggers[idx_trigger].onbits2)
               << setw(20) << Form("0x%08x",triggers[idx_trigger].onbits3)
               << setw(20) << Form("0x%08x",triggers[idx_trigger].offbits1)
               << setw(20) << Form("0x%08x",triggers[idx_trigger].offbits2)
               << setw(20) << Form("0x%08x",triggers[idx_trigger].offbits3)
               << endm;
    }
    mysql_free_result(result);
  }

  mysql_close(&mysql);

  return true;
}

/*****************************************************************************
 * $Log: StTriggerSimuMaker.cxx,v $
 * Revision 1.45  2011/06/10 18:56:18  pibero
 * Updated meaning of mMCflag variable: 0=data, 1=simulation, 2=embedding
 *
 * Revision 1.44  2010/10/05 15:49:01  rfatemi
 * Include ability to test if trigger is defined in trigger code for the database timestamp
 *
 * Revision 1.43  2010/08/26 15:28:31  pibero
 * In the newer trigger code, the trigger DB is accessed with the query
 * "select idx_rn from triggers where beginTime >= '%s' limit 1".  The
 * problem with this query is that it selects the run following the
 * current time stamp and, unfortunately, production runs aren't always
 * followed by production runs.  So often the query can pick up a
 * following pedestal run and emulators give up.  A more appropriate
 * query would be "select max(idx_rn) from triggers where beginTime <=
 * '%s'", which selects the begin time right before the time stamp and
 * hence the actual current run.  I can validate that this works as
 * desired.
 *
 * Michael Betancourt
 * PhD Candidate
 * Hadronic Physics Group
 * Laboratory for Nuclear Science
 * Massachusetts Institute of Technology
 *
 * Revision 1.42  2010/08/13 22:55:18  pibero
 * Added onbits1-3 and offbits1-3
 *
 * Revision 1.41  2010/08/13 22:21:11  pibero
 * Move from online to offline DB
 *
 * Revision 1.40  2010/08/08 21:58:53  pibero
 * Back to checking decision of individual simulators.
 *
 * Revision 1.39  2010/08/03 16:53:30  pibero
 * Function isTrigger() checks vector of trigger IDs instead
 * of querying individual detectors.
 *
 * Revision 1.38  2010/06/24 07:51:14  pibero
 * Added hooks to overwrite DSM thresholds from the database.
 *
 * Revision 1.37  2010/05/14 16:36:49  jeromel
 * Wrong include path for mysql
 *
 * Revision 1.36  2010/05/12 23:42:11  pibero
 * Changed absolute path for mysql.h to relative path
 *
 * Revision 1.35  2010/04/17 17:43:40  pibero
 * *** empty log message ***
 *
 * Revision 1.34  2010/04/16 01:47:38  pibero
 * Oops, forgot to include triggers before 2009. Thanks, Liaoyuan.
 *
 * Revision 1.33  2010/03/01 18:48:36  pibero
 * More updates for Run 9
 *
 * Revision 1.32  2010/02/18 20:07:02  pibero
 * Run 9 updates
 *
 * Revision 1.31  2009/11/16 07:51:19  pibero
 * Added LOG_DEBUG messages and triggerIds()
 *
 * Revision 1.30  2009/11/13 20:00:52  pibero
 * Updates for Run 9 to work on simulation
 *
 * Revision 1.29  2009/10/12 18:04:12  pibero
 * Moved StEEmcUtil/EEdsm to StTriggerUtilities/Eemc
 *
 * Revision 1.28  2009/09/26 18:46:28  pibero
 * Migration from ROOT MySQL to STAR DB API
 *
 * Revision 1.27  2009/09/23 22:35:30  pibero
 * Removed dependencies on ROOT MySQL
 *
 * Revision 1.26  2009/09/20 06:46:29  pibero
 * Updates for Run 9
 *
 * Revision 1.25  2009/02/04 20:00:48  rfatemi
 * change includes for StEmcDecoder
 *
 * Revision 1.24  2009/02/03 15:40:38  rfatemi
 * Changed structure of mSimulators to accomodate 2009 EMC simulator update
 *
 * Revision 1.23  2009/01/17 13:09:02  pibero
 * Initial Version of EMC DSM algorithms for 2009
 *
 * Revision 1.22  2008/01/22 18:06:26  kocolosk
 * added detailedResult code for BEMC L0, courtesy Dave Staszak
 * fixed two bugs in vector accessors in result class (also thanks to Dave)
 *
 * Revision 1.21  2008/01/17 17:04:07  kocolosk
 * some revisions to StTriggerSimuResult structure to hopefully improve clarity and maintainability
 *
 * Revision 1.20  2008/01/17 01:58:25  kocolosk
 * StTriggerSimuResult makes detailed emulation results persistent
 *
 *
 *****************************************************************************/
