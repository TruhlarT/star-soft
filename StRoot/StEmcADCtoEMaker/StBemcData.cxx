#include "StBemcData.h"
#include "StDaqLib/EMC/StEmcDecoder.h"
#include "Stiostream.h"
 
ClassImp(StBemcData)
 
StBemcData::StBemcData(char* name):TDataSet(name)
{
  mDecoder = NULL;
  zeroAll();
  for(int i=0;i<4800;i++) 
  {
    TowerStatus[i] = 0;
    PsdStatus[i] = 0;
  }
  for(int i=0;i<18000;i++) 
  {
    SmdeStatus[i] = 0;
    SmdpStatus[i] = 0;
  }

}
void StBemcData::zeroAll()
{
  //mDecoder = NULL;
  ///////////////////////////////////////////////////////////
  // NOTE from AAPSUAIDE
  //
  // the status flags (TowerStatus, SmdeStatus, etc) should
  // not be zeroed event by event. This should only clear the
  // detector data, such as ADC, energies and headers
  //
  // Status come from the database and are filled only once
  // per run, so, if it is zeroed it will not be set again
  // until the next run starts
  //////////////////////////////////////////////////////////
  
  for(int i=0;i<30;i++)
    {
      TDCError[i]    = 0;
      TDCToken[i]    = 0;
      TDCTrigger[i]  = 4;
      TDCCrateId[i]  = 0;
      TDCCount[i]    = 164;
    }
  for(int i=0;i<4800;i++)
    {
      TowerADC[i]    = 0;
      TowerEnergy[i] = 0;
      SmdeADC[i]     = 0;
      SmdpADC[i]     = 0;
      SmdeEnergy[i]  = 0;
      SmdpEnergy[i]  = 0;
      PsdADC[i]      = 0;
      PsdEnergy[i]   = 0;
    }
  for(int i=4800;i<18000;i++)
    {
      SmdeADC[i] = 0;
      SmdpADC[i] = 0;
      SmdeEnergy[i] = 0;
      SmdpEnergy[i] = 0;
    }
  TowerPresent = kFALSE;
  SMDPresent = kFALSE;
  PSDPresent = kFALSE;
  ValidTowerEvent = kFALSE;
  ValidSMDEvent = kFALSE;
  ValidPSDEvent = kFALSE;
}
StBemcData::~StBemcData()
{
  if(mDecoder) delete mDecoder;
} 
Bool_t StBemcData::getTDCStatus(Int_t c)
{
  if(c<0 || c>29) return kFALSE;
  if(c<3  && EventDate<20011105) return kTRUE;
  if(c<5  && EventDate>=20011105 && EventDate<20020301) return kTRUE;
  if(c<15 && EventDate>=20020301 && EventDate<20030701) return kTRUE;
  if(EventDate>=20030701) // returns the status based on the event header
    {
      return checkTDC(c);
    }
  return kFALSE;
} 
Bool_t StBemcData::getSMDStatus(Int_t c)
{
  if(c<0 || c>7) return kFALSE;
  if(c<1  && EventDate<20011105) return kTRUE;
  if(c<2  && EventDate>=20011105 && EventDate<20020301) return kTRUE;
  if(c<4  && EventDate>=20020301 && EventDate<20030701) return kTRUE;
  if(EventDate>=20030701) // returns the status based on the event header
    {
      return kTRUE;
    }
  return kFALSE;
} 
Bool_t StBemcData::checkTDC(Int_t i)
{
  float towerTh = 200;
  Bool_t ok = kTRUE;
  if(!mDecoder) mDecoder = new StEmcDecoder(EventDate,EventTime);
  Int_t crate;
  //if(!getTDCStatus(i)) return kTRUE;
  mDecoder->GetTowerCrateFromTDC(i,crate);
  if(TDCError[i]!=0) ok = kFALSE;
  if(TDCCrateId[i]!=crate && TDCCrateId[i]!=0) ok = kFALSE;
  if(TDCCount[i]!=164) ok = kFALSE;
  float sum =0, nt=0;
  float avg = 0;
  int id=0;
  if(TDCTrigger[i]==4)  //physics trigger only
    for(int j=0;j<160;j++)
    {
	    mDecoder->GetTowerIdFromTDC(i,j,id);
	    if(id>=1 && id<=4800) if(TowerStatus[id-1]==1) { sum+=TowerADC[id-1]; nt++; }
    }
  if(nt>0) avg = sum/nt;
  if(avg>towerTh) ok = kFALSE;
  if(!ok) for(int j=0;j<160;j++)
  {
	  mDecoder->GetTowerIdFromTDC(i,j,id);
	  TowerADC[id-1] = 0;
  }
  return ok;
}
void StBemcData::validateData()
{
  //towers first
  Bool_t ok = kTRUE;
  if(!TowerPresent) ok = kFALSE;
  if(TDCErrorFlag==1) ok = kFALSE;
  Int_t nbad = 0;
  for(Int_t i=0;i<30;i++) if(!checkTDC(i)) nbad++;
  if(nbad==30) ok = kFALSE;
  ValidTowerEvent = ok;
	
  //SMD
  ok = kTRUE;
  if(!SMDPresent) ok = kFALSE;
  if(SMDErrorFlag ==1) ok = kFALSE;
  ValidSMDEvent = ok;
	
  //PSD
  ok = kTRUE;
  if(!PSDPresent) ok = kFALSE;
  if(PSDErrorFlag ==1) ok = kFALSE;
  ValidPSDEvent = ok;
}
void StBemcData::printTower()
{
  cout <<"TOWER DATA -----------------------------------------------------------\n";
  cout <<"RunNumber = "<<RunNumber<<endl;
  cout <<"TriggerWord = "<<TriggerWord<<endl;
  cout <<"EventDate = "<<EventDate<<endl;
  cout <<"EventTime = "<<EventTime<<endl;
  cout <<"ValidTowerEvent = "<<(Int_t)ValidTowerEvent<<endl;
  cout <<"EventNumber = "<<EventNumber<<endl;
  cout <<"TowerByteCount = "<<TowerByteCount<<endl;
  cout <<"NTowerHits = "<<NTowerHits<<endl;
  cout <<"TDCErrorFlag = "<<TDCErrorFlag<<endl;
  cout <<"NTDCChannels = "<<NTDCChannels<<endl;
  for(Int_t i=0;i<30;i++)
    cout <<"  TDC = "<<i<<"  Error = "<<TDCError[i]<<"  Token = "<<TDCToken[i]<<"  Trigger = "<<TDCTrigger[i]
	 <<"  Crate = "<<TDCCrateId[i]<<"  Count = "<<TDCCount[i]<<endl;
  for(Int_t k=0;k<4800;k++)
    {
      cout <<" ID = "<<k<<" STAT = "<<(Int_t)TowerStatus[k]<<" ADC = "<<TowerADC[k]<<" E = "<<TowerEnergy[k]<<" |";
      if((k+1)%3==0) cout <<endl;
    }
}

void StBemcData::printSMD()
{
}
