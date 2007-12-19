#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/*********************************************************************
 * $Id: L2btowCalAlgo08.cxx,v 1.1 2007/12/19 02:30:18 balewski Exp $
 * \author Jan Balewski, IUCF, 2006 
 *********************************************************************
 * Descripion:
  Reco of mono- & di-jets in L2 using BTOW+ETOW
  depends on L2-DB class 
 *********************************************************************
 */


#ifdef  IS_REAL_L2  //in l2-ana  environment
  #include "../L2algoUtil/L2EmcDb.h"
  #include "../L2algoUtil/L2Histo.h"
#else
  #include "L2EmcDb.h"
  #include "L2Histo.h"
  #include "L2EmcGeom.h"
#endif

#include "L2btowCalAlgo08.h"

/************************
the _only_ copy of L2event for all L2-algos
**************************/
L2event2008  globL2event2008;
/*************************/

//=================================================
//=================================================
L2btowCalAlgo08::L2btowCalAlgo08(const char* name, L2EmcDb* db, L2EmcGeom *geoX, char* outDir)  :  L2VirtualAlgo2008( name,  db,  outDir) { 
  /* called one per days
     all memory allocation must be done here
  */

  geom=geoX; assert(geom);

  setMaxHist(32);
  createHisto();
  
  // map L2event variables for _write_
  mEve_btow_hit=globL2event2008.btow_hit;
}

/* ========================================
  ======================================== */
int 
L2btowCalAlgo08::initRunUser( int runNo, int *rc_ints, float *rc_floats) {

 
  // unpack params from run control GUI
  par_dbg       =  rc_ints[0];
  par_gainType  =  rc_ints[1];
  par_nSigPed   =  rc_ints[2];

  par_twEneThres = rc_floats[0];
  par_hotEtThres = rc_floats[1];;
 
  if (mLogFile) { 
    fprintf(mLogFile,"L2%s algorithm initRun(R=%d), compiled: %s , %s\n params:\n",getName(),mRunNumber,__DATE__,__TIME__);
    fprintf(mLogFile," - use BTOW=%d,  gain Ideal=%d or Offline=%d, debug=%d\n",
	    par_gainType>=kGainIdeal, par_gainType==kGainIdeal, par_gainType==kGainOffline, par_dbg);
    fprintf(mLogFile," - thresholds: ADC-ped> %d*sigPed .AND. energy>%.2f GeV \n", par_nSigPed, par_twEneThres);

    fprintf(mLogFile," - hot tower thresholds:  ET/GeV=%.2f\n",par_hotEtThres);
  }

  // verify consistency of input params
  int kBad=0;
  kBad+=0x00001 * (par_gainType<kGainZero || par_gainType>kGainOffline);
  kBad+=0x00002 * (par_nSigPed<2 || par_nSigPed>5);
  kBad+=0x00004 * (par_twEneThres<0.1 ||  par_twEneThres>1.5);
  if (mLogFile) {
    fprintf(mLogFile,"initRun() params checked for consistency, Error flag=0x%04x\n",kBad);
  }
  
  if(kBad) return kBad;

  // clear content of all histograms
  int i;
  for (i=0; i<mxHA;i++) if(hA[i])hA[i]->reset();

  // upadate title of histos
  char txt[1000];
  sprintf(txt,"BTOW tower, E_T>%.2f GeV (input); x: BTOW RDO index=chan*30+fiber; y: counts",par_hotEtThres);
  hA[10]->setTitle(txt);
  
  sprintf(txt,"BTOW tower, Et>%.2f GeV (input); x: BTOW softID",par_hotEtThres);
  hA[11]->setTitle(txt);
  sprintf(txt,"BTOW tower, Et>%.2f GeV (input); x: eta bin, [-1,+1];  y: phi bin ~ TPC sector",par_hotEtThres);
  hA[12] ->setTitle(txt);
  
  sprintf(txt,"#BTOW towers / event , Et>%.2f GeV; x: # BTOW towers; y: counts",par_hotEtThres);
  hA[14] ->setTitle(txt);
  
  // re-caluclate geometry properties
  geom->btow.clear(); 
  int nB=0; /* counts # of unmasekd towers */ 
  int nBg=0; /* counts # of reasonable calibrated towers */ 
  int nEneThr=0, nPedThr=0; //BTOW count # of towers above & below threshold
  if(par_gainType>=kGainIdeal)  // this disables the whole loop below
  for(i=0; i<EmcDbIndexMax; i++) {
    const L2EmcDb::EmcCDbItem *x=mDb->getByIndex(i);
    if(mDb->isEmpty(x)) continue;  /* dropped not mapped  channels */
    /*....... B A R R E L  .................*/
    if (!mDb->isBTOW(x) ) continue; /* drop if not BTOW */
    if(x->fail) continue;          /* dropped masked channels */
    if(x->gain<=0) continue;       /* dropped uncalibrated towers , tmp */
    nB++;   

    float adcThres=x->ped+par_nSigPed* fabs(x->sigPed);
    float otherThr=x->ped+par_twEneThres*x->gain;
    //    if(strstr("01tg34",x->name))  printf("%s g=%f  adcThrEne=%.1f  adcThrAbovePed=%.1f  rdo=%d\n",x->name,x->gain,adcThres,otherThr,x->rdo);

    if(adcThres<otherThr) { //use energy threshold if higher
      adcThres=otherThr;
      nEneThr++;
    } else {
      nPedThr++;
    }
    
    /* use rdo index to match RDO order in the ADC data banks */    
    if(x->eta<=0 || x->eta>BtowGeom::mxEtaBins) return -90;
    int ietaTw= (x->eta-1); /* correct */

    // use ideal gains for now, hardcoded
    assert(par_gainType==kGainIdeal); // offline gains not implemented - should be changed here, Jan
    geom->btow.gain2Ene_rdo[x->rdo]=geom->btow.idealGain2Ene[ietaTw];
    geom->btow.gain2ET_rdo[x->rdo]=geom->getIdealAdc2ET();
    
    geom->btow.thr_rdo[x->rdo]=(int) (adcThres);
    geom->btow.ped_rdo[x->rdo]=(int) (x->ped);
    nBg++;      
  }
  
  if (mLogFile) {
    fprintf(mLogFile,"  found  towers working=%d calibrated=%d, based on ASCII DB\n",nB,nBg);
    fprintf(mLogFile,"  thresh defined by energy=%d  or NsigPed=%d \n",nEneThr, nPedThr);
  }

  return 0; //OK


}               

/* ========================================
  ======================================== */
void 
L2btowCalAlgo08::computeBtow(int flag, int inpL2EveId, int bemcIn, ushort *rawAdc){
  // special case, code below will trurn off regular compute(), must have one exit  at the end
  computeStart(flag, inpL2EveId);

  clearEvent(); /* large price tag in kTicks */
  int nTower=0; /* counts mapped & used ADC channels */
  int nHotTower=0;
  if(bemcIn && par_gainType>kGainZero) { // EVEVEVEVEVE
    // ............process this event ...............
    short rdo;
    int adc; // pedestal subtracted
    float et;
    ushort *thr=geom->btow.thr_rdo;
    ushort *ped=geom->btow.ped_rdo;
    float *gain2ET=geom->btow.gain2ET_rdo;
    float *gain2Ene=geom->btow.gain2Ene_rdo;
    HitTower *hit=globL2event2008. btow_hit;
    for(rdo=0; rdo<BtowGeom::mxRdo; rdo++){
      if(rawAdc[rdo]<thr[rdo])continue;
      adc=rawAdc[rdo]-ped[rdo];  //do NOT correct for common pedestal noise
      et=adc/gain2ET[rdo]; 
      hit->rdo=rdo;
      hit->adc=adc;
      hit->et=et;
      hit->ene=adc/gain2Ene[rdo]; 
      hit++;
      nTower++; 
      // only monitoring
      // if(par_dbg>0) printf("pro rdo=%d adc=%d  nTw=%d\n",rdo,adc,tmpNused);
      if(et >par_hotEtThres) {
	hA[10]->fill(rdo);
	nHotTower++;
      }
    }
    globL2event2008.btow_hitSize=nTower;
    
    // QA histos
    hA[13]->fill(nTower);
    hA[14]->fill(nHotTower);
  
  } // EVEVEVEVEVE

  // debugging should be off for any time critical computation
  if(par_dbg>0){
     printf("L2-%s-compute: set adcL size=%d, get=%d\n",getName(),nTower,*globEve_btow_hitSize);
   printf("dbg=%s: found  nTw=%d\n",getName(),nTower);
    if(par_dbg>0) print1();
    print2();
  } 
  
  computeStop();

} 

/* ========================================
  ======================================== */
void 
L2btowCalAlgo08::computeUser(int flag, int inpL2EveId){
  printf("computeUser-%s FATAL CRASH\n If you see this message it means l2new is very badly misconfigured \n and L2-btow-calib algo was not executed properly\n before calling other individual L2-algos. \n\n l2new will aborted now - fix the code, Jan B.\n",getName());
  assert(1==2);
}


/* ========================================
  ======================================== */
void
L2btowCalAlgo08::finishRunUser() {  /* called once at the end of the run */
  // do whatever you want, log-file & histo-file are still open

  // serach for hot tower, re-project histos vs. other representations
 int bHotSum=1,bHotId=-1;
 const int *data20=hA[10]->getData();
 const L2EmcDb::EmcCDbItem *xB=mDb->getByIndex(402); // some wired default?
  
  int i;
  for(i=0; i<EmcDbIndexMax; i++) {
    const L2EmcDb::EmcCDbItem *x=mDb->getByIndex(i);
    if(mDb->isEmpty(x)) continue;
    if (!mDb->isBTOW(x) ) continue;
    int softId=atoi(x->tube+2);
    int ieta= (x->eta-1);
    int iphi= (x->sec-1)*10 + x->sub-'a' ;
    //  if(data20[x->rdo]>20) { mDb->printItem(x); printf("softID=%d\n",softId);}
    hA[11]->fillW(softId,data20[x->rdo]);
    hA[12]->fillW(ieta, iphi,data20[x->rdo]);
    if(bHotSum<data20[x->rdo]) {
      bHotSum=data20[x->rdo];
      bHotId=softId;
      xB=x;
    }
  }
  
  if (mLogFile){
    fprintf(mLogFile,"#BTOW_hot tower _candidate_ (bHotSum=%d of %d eve) :, softID %d , crate %d , chan %d , name %s\n",bHotSum,mEventsInRun,bHotId,xB->crate,xB->chan,xB->name);
  }
  
}


//=======================================
//=======================================
void 
L2btowCalAlgo08::createHisto() {
  memset(hA,0,sizeof(hA));
  
  // BTOW  raw spectra
  hA[10]=new L2Histo(10,"btow hot tower 1", 4800); // title upadted in initRun
  hA[11]=new L2Histo(11,"btow hot tower 2", 4800); // title upadted in initRun
  hA[12]=new L2Histo(12,"btow hot tower 3", 40,120); // title upadted in initRun  
  hA[13]=new L2Histo(13,"BTOW #tower w/ energy /event; x: # BTOW towers; y: counts", 100); 
  hA[14]=new L2Histo(14,"# hot towers/event", 100); 
  
}

//=======================================
//=======================================
void 
L2btowCalAlgo08::clearEvent(){
  globL2event2008.btow_hitSize=0;
}


/* ========================================
  ======================================== */
void 
L2btowCalAlgo08::print1(){ // full ADC array
 }

  
/* ========================================
  ======================================== */
void 
L2btowCalAlgo08::print2(){ 
  int i;
  printf("pr2-%s: ---BTOW ADC list--- size=%d\n",getName(),*globEve_btow_hitSize);
  const HitTower *hit=globEve_btow_hit;
  for(i=0;i< *globEve_btow_hitSize;i++,hit++) {
    int adc=hit->adc;
    int rdo=hit->rdo;
    float et=hit->et;
    float ene=hit->ene;
    printf("  btow: i=%2d rdo=%4d  adc=%d  et=%.3f  ene=%.3f\n",i,rdo,adc,et,ene);
  }

}

/**********************************************************************
  $Log: L2btowCalAlgo08.cxx,v $
  Revision 1.1  2007/12/19 02:30:18  balewski
  new L2-btow-calib-2008

  Revision 1.1  2007/11/19 22:18:25  balewski
  most L2algos provide triggerID's

 
*/


