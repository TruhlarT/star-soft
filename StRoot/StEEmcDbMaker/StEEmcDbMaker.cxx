// *-- Author : Jan Balewski
// 
// $Id: StEEmcDbMaker.cxx,v 1.25 2004/04/04 06:10:37 balewski Exp $
 

#include <time.h>
#include <string.h>

#include <TDatime.h>

#include "StChain.h"
#include "St_DataSetIter.h"

#include "St_db_Maker/St_db_Maker.h" // tmp to ovveride time stamp

#include "StEventTypes.h"

#include "StEEmcDbMaker.h"

#include "StEEmcDbIndexItem1.h" // OLD
#include "StEEmcDbMaker/EEmcDbItem.h"
#include "StEEmcDbMaker/EEmcDbCrate.h"
#include "StEEmcUtil/EEfeeRaw/EEname2Index.h" 


#include "tables/St_eemcDbADCconf_Table.h"
#include "tables/St_eemcDbPMTcal_Table.h"
#include "tables/St_eemcDbPMTped_Table.h"
#include "tables/St_eemcDbPMTstat_Table.h"
#include "tables/St_kretDbBlobS_Table.h"
#include "cstructs/eemcConstDB.hh"


ClassImp(StEEmcDbMaker)

//_________________________________________________________
//________________________________________________________
//________________________________________________________
StEEmcDbMaker::StEEmcDbMaker(const char *name):StMaker(name){
  printf("\n Constructor :::::: %s\n",GetName());
  mfirstSecID=mlastSecID=mNSector=0;
  myTimeStampDay=0;
  myTimeStampUnix=0;

  //............ NEW ..............

 //................ allocate memory for lookup tables
  byIndex=new  EEmcDbItem[EEindexMax];

  byCrate=new  EEmcDbItem ** [mxAdcCrate];

  int i;
  for(i=0;i<mxAdcCrate;i++){
    byCrate[i]=NULL;
    if(i==0 || (i>maxTwCrateID && i<minMapmtCrateID) ) continue; // to save memory for nonexisting crates
    byCrate[i]=new EEmcDbItem * [mxAdcChan];
    memset(byCrate[i],0,sizeof(EEmcDbItem *)*mxAdcChan);// clear all pointers
  }


  //...... old
  mDbItem1=new  StEEmcDbIndexItem1[EEindexMax];
  mLookup=new  StEEmcDbIndexItem1 ** [mxAdcCrate];
  

  for(i=0;i<mxAdcCrate;i++){
    mLookup[i]=NULL;
    if(i==0 || (i>6 && i<64) ) continue; // to save memory for nonexisting crates
    mLookup[i]=new StEEmcDbIndexItem1 * [mxAdcChan];
    memset(mLookup[i],0,sizeof(StEEmcDbIndexItem1 *)*mxAdcChan);// clear all pointers
  }

  // new
  mDbFiber=0; nFiber=0;

  setDBname("Calibrations/eemc");
  
}


//________________________________________________________
//________________________________________________________
//_______________________________________________________
StEEmcDbMaker::~StEEmcDbMaker(){
  delete [] mDbItem1;

  int i;
  for(i=0;i<mxAdcCrate;i++) {
    if(mLookup[i])
      delete [] mLookup[i];
  }
  delete [] mLookup;

  if( mNSector) {
    delete [] mDbADCconf;
    //    delete [] mDbPMTconf;
    delete [] mDbPMTcal;
    delete [] mDbPMTped;
    delete [] mDbPMTstat;
    delete [] mDbsectorID;
  }

  //new
  delete mDbFiber;
}

//________________________________________________________
//________________________________________________________
//________________________________________________________
void  StEEmcDbMaker::setTimeStampDay( int tD) {

  if(myTimeStampDay) {
    printf("Logical error:  redeclaration of %s::myTimeStampDay =%d,STOP\n",GetName(),myTimeStampDay);
    exit(1);
  }
  myTimeStampDay=tD;

  int iy=tD/10000; tD%=10000;
  int im=tD/100;  tD%=100;
  int id=tD;
  printf("%d %d %d\n",iy,im,id);

  // build Unix time stamp 
  struct tm t;
  memset(&t,0,sizeof t);
  t.tm_sec=0;    /* seconds after the minute - [0,61] */
  t.tm_min=0;      /* minutes after the hour - [0,59] */
  t.tm_hour=0;      /* hours - [0,23] */
  t.tm_mday=id;     /* day of month - [1,31] */
  t.tm_mon=im-1;      /* month of year - [0,11] */
  t.tm_year=iy-1900;     /* years since 1900 */
  t.tm_isdst=0;    /* daylight savings time flag */  
  //int tm_wday;     /* days since Sunday - [0,6] */
  //int tm_yday;     /* days since January 1 - [0,365] */
  myTimeStampUnix =(unsigned int) mktime(&t);

  printf("%s::myTimeStampDay set to %d\n",GetName(),myTimeStampDay);
  printf("Unix Time stamp=%s",ctime((const time_t *)&myTimeStampUnix));


}

//------------------
//------------------
void StEEmcDbMaker::setThreshold(float x){
 KsigOverPed=x;
 printf("%s::setThres KsigOverPed=%f, threshold=ped+sig*KsigOverPed\n",GetName(),KsigOverPed);
}


//------------------
//------------------
void StEEmcDbMaker::setPreferedFlavor(const char *flavor, const char *nameMask){
  strncpy(dbFlavor.flavor,flavor,DbFlavor::mx);
  strncpy(dbFlavor.nameMask,nameMask,DbFlavor::mx);
  printf("SET %s::preferFlavor(flav='%s', mask='%s')\n",GetName(),dbFlavor.flavor,dbFlavor.nameMask);
}



//________________________________________________________
//________________________________________________________
//________________________________________________________
Int_t StEEmcDbMaker::Init(){
  if( mNSector==0) setSectors(1,12);//default
  setThreshold(5.0);  // defines threshold for ADCs
  // should be +2 or +3 sigma in the future

  setPreferedFlavor("onlped","eemcPMTped"); // tmp for tests,JB

  return StMaker::Init();
}


//________________________________________________________
//________________________________________________________
//________________________________________________________
void StEEmcDbMaker::setSectors(int sec1,int sec2){
  assert(mNSector==0) ; //you can do it just once, no memory realocation implemented

  mfirstSecID=sec1;
  mlastSecID=sec2;
  mNSector=mlastSecID - mfirstSecID+1;

  mDbADCconf=(eemcDbADCconf_st **) new void *[mNSector];
  mDbPMTcal= (eemcDbPMTcal_st  **) new void *[mNSector];
  mDbPMTped= (eemcDbPMTped_st  **) new void *[mNSector];
  mDbPMTstat=(eemcDbPMTstat_st **) new void *[mNSector];
  mDbsectorID=  new int [mNSector];

  clear();

  printf("\n\n%s::Use sectors from %d to %d\n",GetName(),mfirstSecID,mlastSecID);

}

//__________________________________________________
//__________________________________________________
//__________________________________________________

const EEmcDbCrate* StEEmcDbMaker::getFiber(int icr) {
  assert(icr>=0);
  assert(icr<nFiber);
  return mDbFiber+icr;
}



//--------------------------------------------------
//--------------------------------------------------
void StEEmcDbMaker::clear(){
  printf("%s::clear()\n",GetName());
  nFound=0;

  int i;

  for(i=0; i<EEindexMax; i++)
    byIndex[i].clear();

  int j;
  for(i=0;i<mxAdcCrate;i++) {
    if(byCrate[i]==NULL) continue;
    for(j=0;j<mxAdcChan;j++)
      byCrate[i][j]=0;
  }

  if(mDbFiber) delete [] mDbFiber;
  nFiber=0;
  mDbFiberConfBlob=0;

  nFound=0;
  mDbADCconf[0]=0;
  for(i=0; i<mNSector; i++) {// clear pointers old DB tables
     mDbADCconf [i]=0;
     mDbPMTcal  [i]=0;
     mDbPMTped  [i]=0;
     mDbPMTstat [i]=0;
    mDbsectorID[i]=-1;
  }


  //................ old .............
  // clear old DB tables  ...................

  for(i=0; i<EEindexMax; i++)
    mDbItem1[i].clear();
  

  for(i=0;i<mxAdcCrate;i++) {
    if(mLookup[i]==NULL) continue;
    for(j=0;j<mxAdcChan;j++)
      mLookup[i][j]=0;
  }
  
}


//__________________________________________________
//__________________________________________________
//__________________________________________________

Int_t  StEEmcDbMaker::InitRun  (int runumber){
  printf("\n\nInitRun :::::: %s\n\n\n",GetName());

  printf("%s::use(flav='%s', mask='%s')\n",GetName(),dbFlavor.flavor,dbFlavor.nameMask);

  //... new  
  clear();
  mReloadDb();

 //............  reload all lookup tables ...............
  int is;
  for(is=0; is< mNSector; is++) {
    mOptimizeMapping(is);
    //reloadDbOthers(secID);
  }

  mOptimizeFibers();

  // exportAscii();

  //  assert(3==8);
   //............... old

  // mOptimizeDb();


  printf("%s::InitRun()  Found %d EEMC related tables for the present time stamp\n",GetName(),nFound);

  return kStOK;
}  


//__________________________________________________
//__________________________________________________

void  StEEmcDbMaker::mReloadDb  (){


  printf("%s::reloadDb using TimeStamp from 'StarDb'=%p or 'db'=%p \n",GetName(),(void*)GetMaker("StarDb"),(void*)GetMaker("db"));
  

  St_db_Maker* mydb = (St_db_Maker*)GetMaker("StarDb");
  if(mydb==0) mydb = (St_db_Maker*)GetMaker("db");
  assert(mydb);

  if(myTimeStampDay==0) { // use oryginal timestamp of event   
    
#if 0
    StEvent *stEvent= (StEvent *) GetInputDS("StEvent"); 
    assert(stEvent);     
    printf("StEvent time=%d, ID=%d, runID=%d\n",(int)stEvent->time(),(int)stEvent->id(),(int)stEvent->runId());
#endif
    
    StEvtHddr* fEvtHddr = (StEvtHddr*)GetDataSet("EvtHddr");
    printf("use EvtHddr actual event time stamp= %d, yyyy/mm/dd=%d hh/mm/ss=%d\n",
	   (int)fEvtHddr->GetUTime(),fEvtHddr->GetDate(),fEvtHddr->GetTime());
  
    //  int time0; // (sec) GMT of the first event
    //  time0=fEvtHddr->GetUTime( ); //<<==== this is used by DB

  } else { // WARN only if you wish to overwrite the global time stamp 
    printf("replace  TimeStampDay to %d \n",myTimeStampDay);
    mydb->SetDateTime(myTimeStampDay,0); // set ~day & ~hour by hand
  }
  // mydb->SetDateTime(20021201,0); // set ~day & ~hour by hand


  printf("JB: access DB=\"%s\"  first time, use timeStamp=\n  ",dbName.Data());
  TDatime aa=mydb->GetDateTime();
  aa.Print();

  int ifl;
  TString mask="";
  for(ifl=0;ifl<2;ifl++) { // loop over flavors
    if(ifl==1) {
      if( dbFlavor.flavor[0]==0) continue; // drop flavor change
      printf("\n %s-->ifl=%d try flavor='%s' for mask='%s'\n",GetName(),ifl,dbFlavor.flavor,dbFlavor.nameMask);
      
      SetFlavor(dbFlavor.flavor,dbFlavor.nameMask);
      mask=dbFlavor.nameMask;
    }
    
    TDataSet *eedb=GetDataBase(dbName );
    if(eedb==0) {
      printf(" \n\n%s::InitRun()  Could not find %s\n\n",GetName(),dbName.Data());
      return ;
      // down-stream makers should check for presence of dataset
    }
    //eedb->ls(2);  
        
    int is;
    for(is=0; is< mNSector; is++) {
      int secID=is+mfirstSecID;
      
      mDbsectorID[is]=secID;
      getTable<St_eemcDbADCconf,eemcDbADCconf_st>(eedb,secID,"eemcADCconf",mask,mDbADCconf+is);
   
      getTable<St_eemcDbPMTcal,eemcDbPMTcal_st>(eedb,secID,"eemcPMTcal",mask,mDbPMTcal+is);
   
      
      getTable<St_eemcDbPMTped,eemcDbPMTped_st>(eedb,secID,"eemcPMTped",mask,mDbPMTped+is);
      
      
      getTable<St_eemcDbPMTstat,eemcDbPMTstat_st>(eedb,secID,"eemcPMTstat",mask,mDbPMTstat+is);
      
    } // end of loop over sectors
    
    // misc tables 
    
    getTable<St_kretDbBlobS,kretDbBlobS_st>(eedb,13,"eemcCrateConf",mask,&mDbFiberConfBlob);
    //printf("AdataS='%s'\n",mDbFiberConfBlob->dataS);
    
    
  }// end of loop over flavors
 
#if 0

  //tmp
  TDatime aa1=mydb->GetDateTime(); 
  if (aa1.GetDate()<20040101) xxx;

#endif

}

//--------------------------------------------------
//--------------------------------------------------
void StEEmcDbMaker::mOptimizeMapping(int is){

  printf("\n  conf ADC for sector=%d\n",mDbsectorID[is]); //tmp

  assert(mDbsectorID[is]>0);

  eemcDbADCconf_st *t= mDbADCconf[is];

  if(t==0) return;
  printf("  comment=%s\n",t->comment); //tmp

  int j;
  for(j=0;j<EEMCDbMaxAdc; j++) { // loop over channels
    char *name=t->name+j*EEMCDbMaxName;

    if(*name==EEMCDbStringDelim) continue;

    //printf("%d '%s'  %d %d\n",j,name,t->crate[j],t->channel[j]);
    // printf("%d   %d %d\n",j,t->crate[j],t->channel[j]);

    int key=EEname2Index(name);
    assert(key>=0 && key<EEindexMax);
    EEmcDbItem *x=&byIndex[key];
    if(!x->isEmpty()) {
      x->print();
      assert(x->isEmpty());
    }
    x->crate=t->crate[j];
    x->chan=t->channel[j];
    x->setName(name);
    x->key=key;
    x->setDefaultTube(minMapmtCrateID);
    // x->print();

    assert(x->crate>=0 && x->crate<mxAdcCrate);
    assert(x->chan>=0 && x->chan<mxAdcChan);
    assert(byCrate[x->crate]);// ERROR: duplicated crate ID from DB
    if(byCrate[x->crate][x->chan]) {
      printf("Fatal Error of eemc DB records: the same crate=%d / channel=%d entered twice for :\n",x->crate,x->chan);
      byCrate[x->crate][x->chan]->print(); // first time
      x->print(); // second time
      assert(1==2);
    }
    byCrate[x->crate][x->chan]=x;
  }
}

//--------------------------------------------------
//--------------------------------------------------
void StEEmcDbMaker::exportAscii(char *fname) const{
  printf("EEmcDb::exportAscii(\'%s') ...\n",fname);

  FILE * fd=fopen(fname,"w");
  assert(fd);
  // fd=stdout;

  int nTot=0;

  fprintf(fd,"# EEmcDb::exportAscii()\ttime stamp   : %d / %s",(int)myTimeStampUnix,
          ctime((const time_t *)&myTimeStampUnix));
  fprintf(fd,"# see StRoot/StEEmcDbMaker/EEmcDbItem::exportAscii()  for definition\n");

  int j;
  
  fprintf(fd,"%d  #fibers: {name,crID,crIDswitch,fiber,nCh,nHead,type,useIt}\n",nFiber);
  for(j=0;j<nFiber;j++) 
    mDbFiber[j].exportAscii(fd);

  fprintf(fd,"#tw/pre/post:  {name,crate,chan,sec,plane,strip,gain,ped,thr,stat,fail,tube,key}\n");
  fprintf(fd,"#or \n");
  fprintf(fd,"#smd: {name,crate,chan,sec,sub,eta,gain,ped,thr,stat,fail,tube,key}\n");
 

  for(j=0;j<EEindexMax; j++) { // loop over channels
    const  EEmcDbItem *x=byIndex+j;
    if(x->isEmpty())continue;
    x->exportAscii(fd);
    nTot++;
  }
  printf("        nTot=%d, done\n",nTot);
  fclose(fd);
}


 
//__________________________________________________
//__________________________________________________
//__________________________________________________

void  StEEmcDbMaker::mOptimizeFibers  (){
  assert(mDbFiberConfBlob);
  assert(nFiber==0);
  
  //  printf("dataS='%s'\n",mDbFiberConfBlob->dataS);
  char *blob=mDbFiberConfBlob->dataS;
  
  blob=strtok(blob,";"); // init iterator
  if(strstr(blob,"<ver1>")==0) {
    printf("%s::mOptimizeFibers() FATAL, missing opening key for DB mDbFiberConfBlob->dataS\n",GetName());
    assert(2==3); // beginning of record, tmp
  }
  
  int i=0;
  int icr=0;
  while((blob=strtok(0,";"))) {  // advance by one nam{
    i++;
    if(strstr(blob,"<#>")) continue; // ignore some records
    if(strstr(blob,"</ver1>")) goto done; // end of record, tmp
    
    // printf("i=%d -->'%s' \n",i,blob);
    if(nFiber==0) {
      nFiber=atoi(blob);
      mDbFiber=new EEmcDbCrate[ nFiber];
      printf("%s::mOptimizeFibers() map %d fibers to crates\n",GetName(),nFiber);
      icr=0;
      continue;
    }
    assert(icr<nFiber);
    mDbFiber[icr].setAll(blob);
    mDbFiber[icr].print();
    icr++;
  };

  printf("%s::mOptimizeFibers() FATAL, missing terminating key for DB mDbFiberConfBlob->dataS\n",GetName());
  assert(3==4);

 done:
  assert(icr==nFiber);
  return;
} 


//_________________________________________________________
//_________________________________________________________
//_________________________________________________________

Int_t StEEmcDbMaker::Make(){
  
  //  printf("\n\nMake :::::: %s\n\n\n",GetName());

  return kStOK;

}


//--------------------------------------------------
//--------------------------------------------------
const  EEmcDbItem*  StEEmcDbMaker::getByCrate(int crateID, int channel) {
  // crateID counts from 1, channel from 0 
  int type=0;
  int max=0;
  // printf("cr=%d ch=%d\n",crateID, channel);
  if(crateID>=minTwCrateID && crateID<=maxTwCrateID) {
    // Towers
    type =1;
    max=maxTwCrateCh;
    if(channel>=max) return 0; // not all data blocks are used 

  } else if (crateID>=minMapmtCrateID && crateID<=maxMapmtCrateID ){
    //MAPMT
    type =2;
    max=maxMapmtCrateCh;
  } else if (crateID>=17 && crateID<=46 ){
    return 0;  //BTOW
  }

  // printf("id=%d  type=%d ch=%d\n",crateID,type,channel);
  //printf(" p=%p \n",byCrate[crateID]);

  assert(type);
  assert( byCrate[crateID]);
  assert(channel>=0);
  assert(channel<max);
  return byCrate[crateID][channel];
}



//_________________________________________________________
//_________________________________________________________
//_________________________________________________________

template <class St_T, class T_st> void StEEmcDbMaker 
::getTable(TDataSet *eedb, int secID, TString tabName, TString mask,  T_st** outTab ){

  //  printf("\n\n%s ::TTT --> %s, size=%d\n\n\n",GetName(),tabName.Data(),sizeof(T_st));

  //   printf("\n\n%s ::TTT --> mask='%s' p=%p ss=%d\n",tabName.Data(),mask.Data(),*outTab,tabName.Contains(mask));

  if(!mask.IsNull() && !tabName.Contains(mask)) return ;
  char name[1000];
  if(secID<13) 
    sprintf(name,"sector%2.2d/%s",secID,tabName.Data());
  else
    sprintf(name,"misc/%s",tabName.Data());


  printf("request=%s==>", name);
  St_T *ds= (St_T *)eedb->Find(name);
  if(ds==0) {
    printf(" not Found in DB, continue \n");
    return ;
  }

  if(ds->GetNRows()!=1) {
    printf(" no records\n");
    return ;
  }
  
  T_st *tab=(T_st *) ds->GetArray();

  if(tab==0) {
    printf(" GetArray() failed\n");
    return  ;
  }

  *outTab=tab;
  printf("'%s'\n",(*outTab)->comment);

  nFound++;
  return ; // copy the whole s-struct to allow flavor change;
}

//================================================
//  O L D  C O D  T O  B e   FIXED
//================================================


//__________________________________________________
//__________________________________________________
//__________________________________________________

const StEEmcDbIndexItem1*  
StEEmcDbMaker::getT(int sec, char sub, int eta){
  char name[20];
  sprintf(name,"%2.2dT%c%2.2d",sec,sub,eta);
  int key=EEname2Index(name);
  return mDbItem1+key;  
}

const StEEmcDbIndexItem1*  
StEEmcDbMaker::getP(int sec, char sub, int eta){
  char name[20];
  sprintf(name,"%2.2dP%c%2.2d",sec,sub,eta);
  int key=EEname2Index(name);
  return mDbItem1+key;  
}

const StEEmcDbIndexItem1*  
StEEmcDbMaker::getQ(int sec, char sub, int eta){
  char name[20];
  sprintf(name,"%2.2dQ%c%2.2d",sec,sub,eta);
  int key=EEname2Index(name);
  return mDbItem1+key;  
}

const StEEmcDbIndexItem1*  
StEEmcDbMaker::getR(int sec, char sub, int eta){
  char name[20];
  sprintf(name,"%2.2dR%c%2.2d",sec,sub,eta);
  int key=EEname2Index(name);
  return mDbItem1+key;  
}

const StEEmcDbIndexItem1*  
StEEmcDbMaker::getU(int sec, int strip ) {
  char name[20];
  sprintf(name,"%2.2dU%3.3d",sec,strip);
  int key=EEname2Index(name);
  return mDbItem1+key;
}

const StEEmcDbIndexItem1*  
StEEmcDbMaker::getV(int sec, int strip ) {
  char name[20];
  sprintf(name,"%2.2dV%3.3d",sec,strip);
  int key=EEname2Index(name);
  return mDbItem1+key;
}





//__________________________________________________
//__________________________________________________
//__________________________________________________

const StEEmcDbIndexItem1*  
StEEmcDbMaker::getByIndex(int key){
  assert(key>=0);
  assert(key<EEindexMax);
  return mDbItem1+key;  
}

//__________________________________________________
//__________________________________________________
//__________________________________________________

const StEEmcDbIndexItem1*  
StEEmcDbMaker::get(int crate, int channel){
  assert(crate>=0);
  assert(crate<mxAdcCrate);
  assert(channel>=0);
  assert(channel<mxAdcChan);
  
  assert( mLookup[crate]);

  return mLookup[crate][channel];  
}
 
//__________________________________________________
//__________________________________________________
//__________________________________________________

void  StEEmcDbMaker::mOptimizeDb(){
  
  int i, j;
  printf("\noptimizeDb :::::: %s\n\n",GetName());
  if(nFound<=0) {
    printf("\n\nWARN : no relevant records were in db, makes no sense to use %s maker for any work, JB\n\n",GetName());
    return;
  }


  // primary information: crate,chan <--> element name
  for(i=0; i<mNSector; i++) {
    eemcDbADCconf_st *t= mDbADCconf[i];
    if(t==0) continue;
    
    for(j=0;j<EEMCDbMaxAdc; j++) { // loop within sector
      char *name=t->name+j*EEMCDbMaxName;
      //      printf("jjj i=%d j=%d %d %d '%s' kill!\n",i,j,t->slot[j],t->channel[j],name);// continue;
      if(*name==EEMCDbStringDelim) continue;

      //      printf("aaa %d %d\n",t->slot[j],t->channel[j]);
      // validate entries
      //tmp      assert(t->slot[j]>=0 && t->slot[j]<EEMC_MaxAdcSlot);
      //tmp assert(t->channel[j]>=0 && t->channel[j]<EEMC_MaxAdcChan);

      int key=EEname2Index(name);
      // store valid entry
      mDbItem1[key].crate=t->crate[j];
      mDbItem1[key].chan=t->channel[j];
      mDbItem1[key].setName(name);

      assert(t->crate[j]>=0 && t->crate[j]<mxAdcCrate);
      assert(t->channel[j]>=0 && t->channel[j]<mxAdcChan);
      assert(mLookup[t->crate[j]]);// wrong crate ID from DB
      if(mLookup[t->crate[j]][t->channel[j]]) {
	printf("Fatal Error of eemc DB records: the same crate=%d / channel=%d entered twice for :\n",t->crate[j],t->channel[j]);
	mLookup[t->crate[j]][t->channel[j]]->print(); // first time
	mDbItem1[key].print(); // second time
	assert(1==2);
      }
      mLookup[t->crate[j]][t->channel[j]]=&mDbItem1[key];
      
      //      if(j>300) break;
      // printf("Mapped %s -->index=%d -->crate/chan=%d/%d \n",mDbItem1[index].name,index,t->crate[j],t->channel[j]);
    }

  } 


  //---------------------------------------------------
  printf("\nAcquire secondary info for active elements ...\n");

  int key;
  for(key=0; key<EEindexMax; key++){//main loop over all pixels
    if(mDbItem1[key].chan<0) continue;
    StEEmcDbIndexItem1 *item=mDbItem1+key;

    char *name=item->name;
    int secID=atoi(name);
    // printf("update %s in sec=%d \n",name,secID);


    for(i=0; i<EEindexMax; i++) {
      if(secID==mDbsectorID[i]) break;
    }
    assert(i<EEindexMax ); // sector not loaded from DB ???, sth is wrong

    eemcDbPMTcal_st *cal= mDbPMTcal[i];
    if(cal==0) continue; // DB data for this sector not loaded from DB
    
    for(j=0;j<EEMCDbMaxPmt; j++) { // loop within sector
      char name1[EEMCDbMaxName];
      strncpy(name1,cal->name+j*EEMCDbMaxName, EEMCDbMaxName-1);
      if(name1[0]==EEMCDbStringDelim) break;
      name1[EEMCDbMaxName-1]=0;
      char *p=strstr(name1,item->name);
      if(p==0) continue;
      mDbItem1[key].gain=cal->gain[j];
      mDbItem1[key].hv=cal->hv[j];
      //if(strchr(name1,'T')==0)
      //    printf(" Axx=%s, index=%d j=%d  gain=%f hv=%f c1=%d c2\%d\n",name1,j,index,cal->gain[j],cal->hv[j], name1[0], name1[1]) ;
      break;
    }
    
    eemcDbPMTped_st *ped= mDbPMTped[i];
    if(ped==0) continue; // DB data for this sector not loaded from DB
    
    for(j=0;j<EEMCDbMaxAdc; j++) { // loop within sector
      char name1[EEMCDbMaxName];
      strncpy(name1,ped->name+j*EEMCDbMaxName, EEMCDbMaxName-1);
      if(name1[0]==EEMCDbStringDelim) break;
      name1[EEMCDbMaxName-1]=0;
      char *p=strstr(name1,item->name);
      if(p==0) continue;
      mDbItem1[key].ped=ped->ped[j];
      mDbItem1[key].thr=ped->ped[j]+KsigOverPed*ped->sig[j];
      break;
    }
    
    eemcDbPMTstat_st *stat= mDbPMTstat[i];
    if(stat==0) continue; // DB data for this sector not loaded from DB
    
    for(j=0;j<EEMCDbMaxAdc; j++) { // loop within sector
     char name1[EEMCDbMaxName];
      strncpy(name1,stat->name+j*EEMCDbMaxName, EEMCDbMaxName-1);
      if(name1[0]==EEMCDbStringDelim) break;
      name1[EEMCDbMaxName-1]=0;
      char *p=strstr(name1,item->name);
      if(p==0) continue;
      mDbItem1[key].stat=stat->stat[j];
      mDbItem1[key].fail=stat->fail[j];
      break;
    }
    
  }// end of loop over index

}

//__________________________________________________
//__________________________________________________
//__________________________________________________

void  StEEmcDbMaker::mPrintItems  (){

  printf("\n\nprintChan :::::: %s\n\nChan   crate -->  name\n ",GetName());

  // int i=0,j=0;
#if 0
  for(i=0; i<EEMC_MaxAdcSlot; i++) 
    for(j=0; j<EEMC_MaxAdcChan; j++) {
     char* name= DbChan2name[i][j];
     if(name[0]==0) continue;
     printf("%d  %d  %s\n",i,j,name);
    }


  printf("\nInverse relation  \n nameHashIndex --> slot + chan\n");
  for(i=0; i<EEMC_MaxNameHash; i++){ 
    if(DbName2chan[i].chan<0) continue;
    printf("%d   %d  %d \n",i, DbName2chan[i].slot, DbName2chan[i].chan);
  }

#endif
  return;

#if 0
  //  int i,j;
  printf("test:  chan,slot <-->  name <-->index\n ");
  for(i=0; i<EEMC_MaxAdcSlot; i++) 
    for(j=0; j<EEMC_MaxAdcChan; j++) {
     char* name= DbChan2name[i][j];
     if(name[0]==0) continue;
     printf("test %d  %d  %s\n",i,j,name);
     int chan,slot;
     name2chan(name,slot,chan);
     char name1[1000];
     chan2name(slot,chan,name1);
     assert(strstr(name,name1)); // consistency check

     //tmp     int k=name2HashIndex(name);
     //tmp assert(strstr(DbName2chan[k].name,name1));
     
    }

#endif
  printf("test OK\n");

  
}




// $Log: StEEmcDbMaker.cxx,v $
// Revision 1.25  2004/04/04 06:10:37  balewski
// *** empty log message ***
//
// Revision 1.24  2004/03/30 04:44:57  balewski
// *** empty log message ***
//
// Revision 1.23  2004/03/28 04:09:08  balewski
// storage of EEMC raw data, not finished
//
// Revision 1.22  2004/03/19 21:31:53  balewski
// new EEMC data decoder
//
// Revision 1.21  2004/01/06 21:19:34  jwebb
// Added methods for accessing preshower, postshower and SMD info.
//
// Revision 1.20  2003/11/20 16:01:25  balewski
// towards run4
//
// Revision 1.19  2003/10/03 22:44:27  balewski
// fix '$' problem in db-entries name
//
// Revision 1.18  2003/09/11 05:49:17  perev
// ansi corrs
//
// Revision 1.17  2003/09/02 19:02:49  balewski
// fix for TMemeStat
//
// Revision 1.16  2003/08/27 03:26:45  balewski
// flavor option added:  myMk1->setPreferedFlavor("set-b","eemcPMTcal");
//
// Revision 1.15  2003/08/26 03:02:30  balewski
// fix of pix-stat and other
//
// Revision 1.14  2003/08/25 17:57:12  balewski
// use teplate to access DB-tables
//
// Revision 1.13  2003/08/22 20:52:20  balewski
// access to stat-table
//
// Revision 1.12  2003/08/02 01:02:17  perev
// change %d to %p int printf
//
// Revision 1.11  2003/07/18 18:31:46  perev
// test for nonexistance of XXXReader added
//
// Revision 1.10  2003/04/27 23:08:13  balewski
// clean up of daq-reader
//
// Revision 1.9  2003/04/25 14:42:00  jeromel
// Minor change in messaging
//
// Revision 1.8  2003/04/16 20:33:51  balewski
// small fixes in eemc daq reader
//
// Revision 1.7  2003/04/02 20:42:23  balewski
// tower-->tube mapping
//
// Revision 1.6  2003/03/26 21:28:02  balewski
// fix
//
// Revision 1.5  2003/03/26 15:26:23  balewski
// add print()
//
// Revision 1.4  2003/03/07 15:35:44  balewski
// towards EEMC daq reader
//
// Revision 1.3  2003/02/18 22:01:40  balewski
// fixes
//
// Revision 1.2  2003/02/18 19:55:53  balewski
// add pedestals
//
// Revision 1.1  2003/01/28 23:18:34  balewski
// start
//
// Revision 1.5  2003/01/06 17:09:21  balewski
// DB-fix
//
// Revision 1.4  2003/01/03 23:37:56  balewski
// move to robinson
//
// Revision 1.3  2002/12/05 14:22:24  balewski
// cleanup, time stamp fixed
//
// Revision 1.2  2002/12/04 13:39:04  balewski
// remove dependency on dbase/
//
// Revision 1.1  2002/11/30 20:01:26  balewski
// start DB interface for EEMC RELATED ROUTINES
//


#if 0  
  // test of flavor
  {
    St_db_Maker* mydb = (St_db_Maker*)GetMaker("StarDb");
    mydb->SetDateTime(20030814,0); // set ~day & ~hour by hand
    printf("\nJB:test of flavor, use time stamp=");
    (mydb->GetDateTime()).Print();

    TDataSet *eedb1=GetDataBase("TestScheme/emc");
    assert(eedb1);

    St_eemcDbPMTcal *ds= (St_eemcDbPMTcal *)eedb1->Find("sector04/eemcPMTcal");
    assert(ds);
    eemcDbPMTcal_st *tab1=(eemcDbPMTcal_st *) ds->GetArray();
    assert(tab1);
    
    printf("1) p=%p tab1->comment=%s\n",tab1,tab1->comment);    

    printf("\n change flavor\n");
    SetFlavor("setb","eemcPMTcal");
    TDataSet *eedb2=GetDataBase("TestScheme/emc");
    assert(eedb2);

    ds= (St_eemcDbPMTcal *)eedb2->Find("sector04/eemcPMTcal");
    assert(ds);
    
    eemcDbPMTcal_st *tab=(eemcDbPMTcal_st *) ds->GetArray();
    assert(tab);

    printf("2) p=%p tab->comment=%s\n",tab,tab->comment);
    printf("1)\' p=%p tab1->comment=%s\n",tab1,tab1->comment);    
 

  }
  // end of flavor test
  assert(1==5);

#endif
