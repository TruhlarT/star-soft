// $Id: St_tcl_Maker.cxx,v 1.28 1999/03/11 20:40:18 ward Exp $
// $Log: St_tcl_Maker.cxx,v $
// Revision 1.28  1999/03/11 20:40:18  ward
// Add code for cluster morphology.
//
// Revision 1.27  1999/03/04 14:05:59  sakrejda
// table of sequences increased
//
// Revision 1.26  1999/03/03 00:29:04  sakrejda
// size of the tables reduced following wasted space diagnostics
//
// Revision 1.25  1999/03/02 19:50:42  sakrejda
// Histograms cleaned up
//
// Revision 1.24  1999/03/01 18:53:32  sakrejda
// hit eveluation switchable
//
// Revision 1.23  1999/02/27 23:10:48  sakrejda
// auxiliary hit table eliminated
//
// Revision 1.22  1999/02/26 17:25:30  kathy
// fix histograms
//
// Revision 1.21  1999/02/25 03:36:05  sakrejda
// Threshold lowered, was set for the test data
//
// Revision 1.20  1999/02/19 16:30:25  fisyak
// sanitary check
//
// Revision 1.19  1999/02/16 01:53:57  fisyak
// Make sure that tfs does not run if there tss
//
// Revision 1.18  1999/02/10 20:57:39  kathy
// added histograms to Maker
//
// Revision 1.17  1999/01/20 23:59:56  fisyak
// Just clean up
//
// Revision 1.16  1999/01/08 23:18:30  sakrejda
// index  table created only once and only for the mc run
//
// Revision 1.15  1999/01/02 19:08:22  fisyak
// Add ctf
//
// Revision 1.14  1998/12/18 18:37:16  fisyak
// account module changes
//
// Revision 1.13  1998/12/16 22:19:19  fisyak
// New tfs
//
// Revision 1.12  1998/12/04 15:31:50  fisyak
// Add g2t_vertex for tcl
//
// Revision 1.11  1998/10/31 00:26:22  fisyak
// Makers take care about branches
//
// Revision 1.10  1998/10/06 18:00:48  perev
// cleanup
//
// Revision 1.9  1998/09/18 14:35:31  fisyak
// Fix makers
//
// Revision 1.8  1998/09/15 20:55:27  fisyak
// Split St_DataSet -> St_DataSet + St_DataSetIter
//
// Revision 1.7  1998/08/26 12:15:10  fisyak
// Remove asu & dsl libraries
//
// Revision 1.6  1998/08/18 14:05:04  fisyak
// Add to bfc dst
//
// Revision 1.5  1998/08/14 15:25:41  fisyak
// Move out tpg from run
//
// Revision 1.4  1998/08/10 02:34:34  fisyak
// Add St_laser_Maker
//
// Revision 1.3  1998/08/07 19:34:55  fisyak
// Add St_run_Maker
//
// Revision 1.2  1998/07/21 01:04:39  fisyak
// Clean up
//
// Revision 1.1  1998/07/21 00:36:46  fisyak
// tcl and tpt
//
//////////////////////////////////////////////////////////////////////////
//                                                                      //
// St_tcl_Maker class for Makers                                        //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
#include <iostream.h>
#include <stdlib.h>
#include "St_tcl_Maker.h"
#include "StChain.h"
#include "St_DataSetIter.h"
#include "St_XDFFile.h"
#include "tpc/St_tpg_main_Module.h"
#include "tpc/St_tcl_Module.h"
#include "tpc/St_tph_Module.h"
#include "tpc/St_xyz_newtab_Module.h"
#include "tpc/St_tte_hit_match_Module.h"
#include "tpc/St_tfs_g2t_Module.h"
#include "tpc/St_tfs_filt_Module.h"
#include "TH1.h"

ClassImp(St_tcl_Maker)
  
  //_____________________________________________________________________________
  St_tcl_Maker::St_tcl_Maker(const char *name, const char *title):
    StMaker(name,title){
  drawinit=kFALSE;
}
//_____________________________________________________________________________
St_tcl_Maker::~St_tcl_Maker(){
}
//_____________________________________________________________________________
Int_t St_tcl_Maker::Init(){
  // Create tables
  St_DataSetIter       local(gStChain->DataSet("params"));
  // geometry parameters
  St_DataSet *tpc = local("tpc");
  if (! tpc)  tpc = local.Mkdir("tpc");
  St_DataSet *tpgpar = local("tpc/tpgpar");
  if (tpgpar){
    St_DataSetIter partable(tpgpar);
    m_tpg_pad_plane = (St_tpg_pad_plane *) partable("tpg_pad_plane");
    m_tpg_detector  = (St_tpg_detector  *) partable("tpg_detector");
    if (!(m_tpg_pad_plane && m_tpg_detector)) {
      cout << "TPC geometry parameter tables are incomplete."<< endl;
      SafeDelete(tpgpar);
    }
    m_tpg_pad       = (St_tpg_pad       *) partable("tpg_pad");
    if (!m_tpg_pad) {
      m_tpg_pad       = new St_tpg_pad("tpg_pad",1); partable.Add(m_tpg_pad);
    }
    Int_t res = tpg_main(m_tpg_pad_plane,m_tpg_detector,m_tpg_pad); 
  }
  // tcl parameters
  St_DataSet *tclpars = local("tpc/tclpars");
  if (tclpars){
    St_DataSetIter partable(tclpars);
    m_tcl_sector_index = (St_tcl_sector_index *) partable("tcl_sector_index");
    m_tclpar           = (St_tcl_tclpar *) partable("tclpar");
    m_type             = (St_tcl_tpc_index_type *) partable("type");
    if (!(m_tcl_sector_index && m_tclpar && m_type)) {
      cout << " St_tcl_Maker:  clustering parameters have not been initialized" << endl;
      SafeDelete(tclpars);
    }
  }
   St_DataSet *tsspars = local("tpc/tsspars");
   if (tsspars){
       St_DataSetIter partable(tsspars);
       m_tsspar = (St_tss_tsspar *) partable("tsspar");
       if (!m_tsspar) {
         cout << "TPC tss parameter tables are incomplete."<< endl;  
         SafeDelete(tsspars);
       }
       else {
	 tss_tsspar_st *tsspar = m_tsspar->GetTable();
         tsspar->threshold=1;
       }
   }
  // tfs parameters
  St_DataSet *tfspars = local("tpc/tfspars");
  if (tfspars){
    m_tfs_fspar = (St_tfs_fspar *) local("tpc/tfspars/tfs_fspar");
    m_tfs_fsctrl= (St_tfs_fsctrl*) local("tpc/tfspars/tfs_fsctrl");
  }
  // Create Histograms

  // for tph pam
  m_nseq_hit   = new TH1F("TclTphitNseq","num seq in hit",200,0.5,200.5);
  m_tpc_row    = new TH1F("TclTphitRow","tpc row num",2345,100.5,2445.5);
  m_x_of_hit   = new TH1F("TclTphitHitX","x dist of hits",50,-200.,200.);
  m_y_of_hit   = new TH1F("TclTphitHitY","y dist of hits",50,-200.,200.);
  m_z_of_hit   = new TH1F("TclTphitHitZ","z dist of hits",50,-250.,250.);
  m_charge_hit = new TH1F("TclTphitTotChargeHit","total charge in hit",100,0.,0.00004);

  // The following quantities are known only AFTER tracking
  //  m_alpha      = new TH1F("TclTphitAlpha","crossing angle in xy",50,-200.,200.);
  // m_phi        = new TH1F("TclTphitPhi","orientation of hit wrt padplane",64,0.,64.);
  // m_lambda     = new TH1F("TclTphitLambda","dip angle(radians)",64,0.,64.);

  // for tcl pam
  m_nseq_cluster = new TH1F("TclTpclusterNseqCluster"," num seq in cluster",100,0.5,200.5);
  m_nhits = new TH1F("TclTpclusterNhits"," estimated num overlapping hits in cluster",20,-0.5,19.5);
  
  return StMaker::Init();
}
Int_t St_tcl_Maker::FillOneRowOfMorphTable(int iClusterTbl,
        St_tcc_morphology *morph,
        int padrow,int sector,int nseq,int npix,int npad,
        unsigned int totChargeEq1,
        int maxCharge,float averageCharge,float meanPadPos,float meanTimePos,
        float padSigma1Eq5,float timeSigma1Eq6,
        float padTimeSigma1Eq7,float padSigma2Eq12,
        float timeSigma2Eq13,float padTimeSigma2Eq14,
        float ecc1Eq15,float ecc2Eq16,
        float linEcc1Eq8,float linEcc2Eq9) {
  tcc_morphology_st singlerow;
  singlerow.clusterId=iClusterTbl+1;
  singlerow.rowNumber=padrow;
  singlerow.sectorNumber=sector;
  singlerow.numberOfSequences=nseq;
  singlerow.numberOfPixels=npix;
  singlerow.numberOfPads=npad;
  singlerow.numberOfHits=0;  // will be filled later
  singlerow.totalCharge=totChargeEq1;
  singlerow.maxCharge=maxCharge;
  singlerow.averageCharge=averageCharge;
  singlerow.meanPadPosition=meanPadPos;
  singlerow.meanTimePosition=meanTimePos;
  singlerow.padSigma1=padSigma1Eq5;
  singlerow.timeSigma1=timeSigma1Eq6;
  singlerow.padTimeSigma1=padTimeSigma1Eq7;
  singlerow.padSigma2=padSigma2Eq12;
  singlerow.timeSigma2=timeSigma2Eq13;
  singlerow.padTimeSigma2=padTimeSigma2Eq14;
  singlerow.ecc1=ecc1Eq15;
  singlerow.ecc2=ecc2Eq16;
  singlerow.linEcc1=linEcc1Eq8;
  singlerow.linEcc2=linEcc2Eq9;
  singlerow.meanX=0;
  singlerow.meanY=0;
  singlerow.meanZ=0;
  singlerow.clusterFlag=0;
  morph->AddAt(&singlerow,iClusterTbl);
  return 0; // no error
}
// #define TCC_PAD 182
// #define TCC_BIN 512
#define CENTIMETERS_PER_TIME_BIN 0.4082
#define LINEARIZATION 1.2
Int_t St_tcl_Maker::CalculateQuadrupoleMoms(
        int padrow,int npad,int *pads,unsigned short charge[TCC_PAD][TCC_BIN],
        unsigned int *totChargeEq1,float *meanPadEq3,float *meanTimeEq4,
        float *padSigma1Eq5,float *timeSigma1Eq6,float *padTimeSigma1Eq7,
        float *padSigma2Eq12,float *timeSigma2Eq13,float *padTimeSigma2Eq14,
        float *ecc1Eq15,float *ecc2Eq16,
        float *linEcc1Eq8,float *linEcc2Eq9) { // Eq #s refer to SN0357
  int ii,jj;
  float alpha,beta,qq,centimetersPerPad,tanLinearizationFactor;

  tanLinearizationFactor=tan(LINEARIZATION);
  if(padrow<=13) centimetersPerPad=0.335; else centimetersPerPad=0.67;

  *totChargeEq1=0; *meanPadEq3=0; *meanTimeEq4=0;
  for(ii=npad-1;ii>=0;ii--) {
    for(jj=TCC_BIN-1;jj>=0;jj--) {
      *totChargeEq1+=charge[ii][jj];
      *meanPadEq3+=centimetersPerPad*pads[ii]*charge[ii][jj];
      *meanTimeEq4+=(jj+1)*CENTIMETERS_PER_TIME_BIN*charge[ii][jj];
    }
  }
  if((*totChargeEq1)>0) *meanPadEq3/=(*totChargeEq1);  else *meanPadEq3=0;
  if((*totChargeEq1)>0) *meanTimeEq4/=(*totChargeEq1); else *meanTimeEq4=0;

  *padSigma1Eq5=0; *timeSigma1Eq6=0; *padTimeSigma1Eq7=0;
  *padSigma2Eq12=0; *timeSigma2Eq13=0; *padTimeSigma2Eq14=0;
  for(ii=npad-1;ii>=0;ii--) {
    for(jj=TCC_BIN-1;jj>=0;jj--) {
      alpha=centimetersPerPad*pads[ii]-(*meanPadEq3);
      beta=(jj+1)*CENTIMETERS_PER_TIME_BIN-(*meanTimeEq4);
      qq=charge[ii][jj];
      *padSigma1Eq5      += alpha        * alpha        * qq ;
      *timeSigma1Eq6      += beta         * beta         * qq ;
      *padTimeSigma1Eq7  += alpha        * beta         * qq ;
      *padSigma2Eq12     += (alpha+beta) * (alpha+beta) * qq ;
      *timeSigma2Eq13     += (alpha-beta) * (alpha-beta) * qq ;
      *padTimeSigma2Eq14 += (alpha+beta) * (alpha-beta) * qq ;
    }
  }
  if((*totChargeEq1)>0) *padSigma1Eq5/=(*totChargeEq1);  else *padSigma1Eq5=0;
  if((*totChargeEq1)>0) *timeSigma1Eq6/=(*totChargeEq1);  else *timeSigma1Eq6=0;
  if((*totChargeEq1)>0) *padTimeSigma1Eq7/=(*totChargeEq1); else *padTimeSigma1Eq7=0;
  if((*totChargeEq1)>0) *padSigma2Eq12/=(*totChargeEq1);  else *padSigma2Eq12=0;
  if((*totChargeEq1)>0) *timeSigma2Eq13/=(*totChargeEq1);  else *timeSigma2Eq13=0;
  if((*totChargeEq1)>0) *padTimeSigma2Eq14/=(*totChargeEq1); else *padTimeSigma2Eq14=0;
  *padSigma2Eq12/=2;      // This represents the sqrt(2) in Eqs 10 and 11.
  *timeSigma2Eq13/=2;      // This represents the sqrt(2) in Eqs 10 and 11.
  *padTimeSigma2Eq14/=2;  // This represents the sqrt(2) in Eqs 10 and 11.

  *padSigma1Eq5=sqrt(*padSigma1Eq5);
  *timeSigma1Eq6=sqrt(*timeSigma1Eq6);
  // sometimes this is sqrt(-): *padTimeSigma1Eq7=sqrt(*padTimeSigma1Eq7);
  *padSigma2Eq12=sqrt(*padSigma2Eq12);
  *timeSigma2Eq13=sqrt(*timeSigma2Eq13);
  // sometimes this is sqrt(-): *padTimeSigma2Eq14=sqrt(*padTimeSigma2Eq14);

  if(*padSigma1Eq5!=0 && *timeSigma1Eq6 !=0) {
    *ecc1Eq15=(*padTimeSigma1Eq7)/((*padSigma1Eq5)*(*timeSigma1Eq6));
  } else *ecc1Eq15=0;
  if(*padSigma2Eq12!=0 && *timeSigma2Eq13!=0) {
    *ecc2Eq16=(*padTimeSigma2Eq14)/((*padSigma2Eq12)*(*timeSigma2Eq13));
  } else *ecc2Eq16=0;
  *linEcc1Eq8=tan(LINEARIZATION*(*ecc1Eq15))/tanLinearizationFactor;
  *linEcc2Eq9=tan(LINEARIZATION*(*ecc2Eq16))/tanLinearizationFactor;

  return 0; // OK.
}
Int_t St_tcl_Maker::cluster_morphology( Int_t sectorNumber,
      St_type_shortdata *pixel_data_in,
      St_type_shortdata *pixel_data_out,
      St_tcl_tpcluster *tpcluster,
      St_tcl_tp_seq *tpseq,St_tcc_morphology *morph) {
  type_shortdata_st *pixTbl;
  unsigned short charge[TCC_PAD][TCC_BIN];
  float meanPadEq3,meanTimeEq4,padSigma1Eq5,timeSigma1Eq6,padTimeSigma1Eq7,
      padSigma2Eq12,timeSigma2Eq13;
  float padTimeSigma2Eq14,ecc1Eq15,ecc2Eq16,linEcc1Eq8,linEcc2Eq9;
  tcl_tp_seq_st *seqTbl = (tcl_tp_seq_st*) tpseq->GetTable();
  int pixBeg,pixEnd,nseq,padrow,sector,seqCnt;
  int iPixTbl,nCluster,iClusterTbl,iSeqTbl;
  int maxCharge,whichPad,whichTimeBin,npad,pads[TCC_PAD];
  int ipad,numberOfPixels,ii,jj;
  unsigned int totChargeEq1;
  static int lastRowPrevTime=-1;
  nCluster=tpcluster->GetNRows();
  tcl_tpcluster_st *clusterTbl = (tcl_tpcluster_st*) tpcluster->GetTable();
  for(iClusterTbl=lastRowPrevTime+1;iClusterTbl<nCluster;iClusterTbl++) {
    if(iClusterTbl%473==0) {
      printf("St_tcl_Maker::cluster_morphology Sector %2d, %3d percent done\n",
             sectorNumber,(100*(iClusterTbl-lastRowPrevTime))/(nCluster-lastRowPrevTime));
    }
    sector=clusterTbl[iClusterTbl].tpc_row/100;
    if(sector!=sectorNumber) { printf("cluster table may be corrupted.\n"); return 1; }
    padrow=clusterTbl[iClusterTbl].tpc_row%100;
    if(padrow<1||padrow>45) { printf("padrow (%d) out of range.\n",padrow); return 2; }
    iSeqTbl=clusterTbl[iClusterTbl].jseq-1;
    nseq=clusterTbl[iClusterTbl].nseq;
    if(padrow<=13) pixTbl= pixel_data_in->GetTable();
    else           pixTbl=pixel_data_out->GetTable();
    npad=0; // count number of pads without assuming one sequence per pad
    memset((void*)charge,(char)0,(size_t)(sizeof(unsigned short)*TCC_PAD*TCC_BIN));
    maxCharge=0; numberOfPixels=0;
    for(seqCnt=0;seqCnt<nseq;seqCnt++) { // seqCnt is not table index, iSeqTbl is.

      // Calculate whichPad, index into pads[]
      for(ipad=npad-1;ipad>=0;ipad--) { if(pads[ipad]==seqTbl[iSeqTbl].secpad) { break; } }
      if(ipad>=0) whichPad=ipad;
      else { // create a new entry in pads[]
        if(npad>=TCC_PAD) return 55;
        whichPad=npad; pads[npad++]=seqTbl[iSeqTbl].secpad;
      }

      pixBeg=seqTbl[iSeqTbl].jpix-1;
      pixEnd=pixBeg+seqTbl[iSeqTbl].tdc_hi-seqTbl[iSeqTbl].tdc_low;

      if(seqTbl[iSeqTbl].tpc_row!=clusterTbl[iClusterTbl].tpc_row) return 3;

      for(iPixTbl=pixBeg;iPixTbl<=pixEnd;iPixTbl++) {
        whichTimeBin=seqTbl[iSeqTbl].tdc_low+iPixTbl-pixBeg;
        if(whichTimeBin<0||whichTimeBin>=TCC_BIN) return 81;
        charge[whichPad][whichTimeBin]=pixTbl[iPixTbl].data;
        if(maxCharge<pixTbl[iPixTbl].data) maxCharge=pixTbl[iPixTbl].data;
        numberOfPixels++;
      }
      iSeqTbl=seqTbl[iSeqTbl].next-1;
    }
    if(iSeqTbl!=-1) return 69;
    if(CalculateQuadrupoleMoms(
             padrow,npad,pads,charge,
             &totChargeEq1,&meanPadEq3,&meanTimeEq4,
             &padSigma1Eq5,&timeSigma1Eq6,&padTimeSigma1Eq7, &padSigma2Eq12,
             &timeSigma2Eq13,&padTimeSigma2Eq14, &ecc1Eq15,&ecc2Eq16,
             &linEcc1Eq8,&linEcc2Eq9)) return 111;
    if(FillOneRowOfMorphTable(iClusterTbl,morph,padrow,sector,nseq,numberOfPixels,
       npad,totChargeEq1,maxCharge,(float)((1.0*totChargeEq1)/numberOfPixels),
       meanPadEq3,meanTimeEq4,
       padSigma1Eq5,timeSigma1Eq6,padTimeSigma1Eq7,padSigma2Eq12,
             timeSigma2Eq13,padTimeSigma2Eq14,ecc1Eq15,ecc2Eq16,
             linEcc1Eq8,linEcc2Eq9
    )) return 102;
  }
  lastRowPrevTime=nCluster-1;
  return 0; // OK.
}
/*=====================================================================================
                   NOTES FOR FUNCTION cluster_morphology()
---------------+----------------+--------------+---------------------+-----------------
type           | wrapper name   | tableName    | range               | indexStep,
               |                |              |                     | index name
---------------+----------------+--------------+---------------------+-----------------
tcl_tpcluster  | tpcluster      | clusterTbl   | 1 to nok            | ++, iClusterTbl
---------------+----------------+--------------+---------------------+-----------------
tcl_tp_seq     | tpseq          | seqTable     | clusterTbl->jseq,   | tpseq[].next,
               |                |              | clusterTbl->nseq    | iSeqTbl
---------------+----------------+--------------+---------------------+-----------------
type_shortdata | pixel_data_out | pixTbl       | tpseq->jpix,        | ++,
               | or             |              | tpseq->tdc_hi-      | iPixTbl
               | pixel_data_in  |              | tpseq->tdc_low      |
---------------+----------------+--------------+---------------------+-----------------
=====================================================================================*/
//_____________________________________________________________________________
Int_t St_tcl_Maker::Make(){
  //  PrintInfo();
  const Int_t max_hit = 400000;
  St_DataSetIter local(m_DataSet);
  if (!m_DataSet->GetList()) {// If DataSet list empty then create it
    St_tcl_tphit     *tphit     = new St_tcl_tphit("tphit",max_hit);         local.Add(tphit);
    St_tcl_tphit_aux *tphitau   = new St_tcl_tphit_aux("tphitau",1);   local.Add(tphitau);
    //    St_tcl_tpc_index *index     = new St_tcl_tpc_index("index",max_hit);     local.Add(index);
    St_tcl_tpcluster *tpcluster = new St_tcl_tpcluster("tpcluster",max_hit); local.Add(tpcluster);
    St_tcc_morphology *morph = new St_tcc_morphology("morph",max_hit); local.Add(morph);
    St_tcl_tp_seq    *tpseq     = new St_tcl_tp_seq("tpseq",5*max_hit);      local.Add(tpseq);
    St_DataSet       *sector;
    St_DataSet       *raw_data_tpc = gStChain->DataSet("tpc_raw");
    Int_t sector_tot = 0;
    if (raw_data_tpc){// Row data exits -> make clustering
      St_DataSetIter next(raw_data_tpc);
      St_raw_sec_m  *raw_sec_m = (St_raw_sec_m *) next("raw_sec_m");
      while (sector=next()){// loop over sectors
	Char_t *name= 0;
	if (name = strstr(sector->GetName(),"Sector")) {
	  // look for the sector number
	  name  = strchr(name,'_')+1;
	  Int_t indx = atoi(name);
	  if (gStChain->Debug()) printf(" Sector = %d \n", indx);
	  tcl_sector_index_st *tcl_sector_index = m_tcl_sector_index->GetTable();
	  m_tcl_sector_index->SetNRows(1);
	  tcl_sector_index->CurrentSector = indx;
	  St_DataSetIter sect(sector);
	  St_raw_row         *raw_row_in     = (St_raw_row *) sect("raw_row_in");
	  St_raw_row         *raw_row_out    = (St_raw_row *) sect("raw_row_out");
	  St_raw_pad         *raw_pad_in     = (St_raw_pad *) sect("raw_pad_in");
	  St_raw_pad         *raw_pad_out    = (St_raw_pad *) sect("raw_pad_out");
	  St_raw_seq         *raw_seq_in     = (St_raw_seq *) sect("raw_seq_in");
	  St_raw_seq         *raw_seq_out    = (St_raw_seq *) sect("raw_seq_out");
	  St_type_shortdata  *pixel_data_in  = (St_type_shortdata *) sect("pixel_data_in");
	  St_type_shortdata  *pixel_data_out = (St_type_shortdata *) sect("pixel_data_out");
	  // tcl
          printf("Starting %20s for sector %2d.\n","tcl",indx);
	  Int_t tcl_res = tcl(m_tpg_pad_plane, m_tcl_sector_index, raw_sec_m,
                              raw_row_in, raw_pad_in, raw_seq_in, pixel_data_in,
                              raw_row_out,raw_pad_out,raw_seq_out,pixel_data_out,
                              tpcluster,tpseq);

          printf("Starting %20s for sector %2d.\n","cluster_morphology",indx);
          Int_t tcc_res = cluster_morphology( indx, pixel_data_in, pixel_data_out,
              tpcluster, tpseq, morph);
          if(tcc_res) { printf("ERROR %d, tcl maker\n",tcc_res); return kStErr; }

	  sector_tot++;
	  // tph
	  Int_t k = indx;
	  if (sector_tot == 1) k = -k;
	  tcl_sector_index->CurrentSector = k;
          printf("Starting %20s for sector %2d.\n","tph",indx);
	  Int_t tph_res =  tph(m_tcl_sector_index,m_tclpar,m_tsspar,
			       m_tpg_pad_plane,
			       pixel_data_in,pixel_data_out,
			       tpseq,tpcluster,tphit,tphitau);
	}
      }
      if (sector_tot && m_tclEvalOn) { //slow simulation exist
	cout << "start run_tte_hit_match" << endl;
	St_DataSetIter geant(gStChain->DataSet("geant"));
	St_g2t_tpc_hit *g2t_tpc_hit = (St_g2t_tpc_hit *) geant("g2t_tpc_hit");
        if (g2t_tpc_hit){//geant data exists too
	// create the index table, if any
	St_tcl_tpc_index  *index = (St_tcl_tpc_index *) local("index");
	if (!index) {index = new St_tcl_tpc_index("index",2*max_hit); local.Add(index);}
	
	Int_t Res_tte =  tte_hit_match(g2t_tpc_hit,index,m_type,tphit); 
        if (Res_tte !=  kSTAFCV_OK)  cout << "Problem with tte_hit_match.." << endl;
	cout << "finish run_tte_hit_match" << endl;
	}
      }
    }
    else {
    // Row data does not exit, check GEANT. if it does then use fast cluster simulation
      St_DataSetIter geant(gStChain->DataSet("geant"));
      St_g2t_tpc_hit *g2t_tpc_hit = (St_g2t_tpc_hit *) geant("g2t_tpc_hit");
      St_g2t_track   *g2t_track   = (St_g2t_track   *) geant("g2t_track");
      St_g2t_vertex  *g2t_vertex  = (St_g2t_vertex  *) geant("g2t_vertex");
      if (g2t_tpc_hit && g2t_track){
	// create the index table, if any
	St_tcl_tpc_index  *index = (St_tcl_tpc_index *) local("index");
	if (!index) {index = new St_tcl_tpc_index("index",2*max_hit); local.Add(index);}
	cout << "start tfs_run" << endl;
	Int_t Res_tfs_g2t =   tfs_g2t(g2t_tpc_hit, g2t_track, g2t_vertex,
				      m_tfs_fspar,m_tfs_fsctrl,
				      index, m_type, tphit);
	if (Res_tfs_g2t !=  kSTAFCV_OK){cout << "Problem running tfs_g2t..." << endl;}
	else {
	  Int_t Res_tfs_filt = tfs_filt(tphit);
	  if ( Res_tfs_filt !=  kSTAFCV_OK){cout << " Problem running tfs_filt..." << endl;} 
	}
	cout << "finish tfs_run" << endl;
      }
    }
  }
  //Histograms     
   MakeHistograms(); // clustering histograms
  return kStOK;
}
//_____________________________________________________________________________
void St_tcl_Maker::PrintInfo(){
  printf("**************************************************************\n");
  printf("* $Id: St_tcl_Maker.cxx,v 1.28 1999/03/11 20:40:18 ward Exp $\n");
  //  printf("* %s    *\n",m_VersionCVS);
  printf("**************************************************************\n");
  if (gStChain->Debug()) StMaker::PrintInfo();
}

//----------------------------------------------------------------------

void St_tcl_Maker::MakeHistograms() {
  // Create an iterator
  St_DataSetIter tpc_hits(m_DataSet);
  //Get the table:
  St_tcl_tphit *ptphh = 0;
  St_tcl_tpcluster *ptpcl =0;
  ptphh  = (St_tcl_tphit *) tpc_hits["tphit"];
  ptpcl  = (St_tcl_tpcluster *) tpc_hits["tpcluster"];

  //  cout << " **** NOW MAKING HISTOGRAMS FOR TCL !!!!! " << endl;
  if (ptphh) {
    tcl_tphit_st *r = ptphh->GetTable();
    for(Int_t i=0; i<ptphh->GetNRows();i++,r++){
      Float_t tphit_z      = r->z;
      Float_t tphit_x      = r->x;
      Float_t tphit_y      = r->y;
      Float_t tphit_lambda = r->lambda;
      Float_t tphit_alpha  = r->alpha;
      Float_t tphit_phi    = r->phi;
      Int_t tphit_nseq   = r->nseq;
      Int_t tphit_row    = r->row;
      Float_t tphit_q      = r->q;
        m_nseq_hit->Fill(tphit_nseq);
        m_tpc_row->Fill(tphit_row);
        m_x_of_hit->Fill(tphit_x);
        m_y_of_hit->Fill(tphit_y);
        m_z_of_hit->Fill(tphit_z);
        m_charge_hit->Fill(tphit_q);
	//        m_alpha->Fill(tphit_alpha);
	//        m_phi->Fill(tphit_phi);
	//        m_lambda->Fill(tphit_lambda);
    }
  }
  if (ptpcl) {
    tcl_tpcluster_st *r2 = ptpcl->GetTable();
    for(Int_t i=0; i<ptpcl->GetNRows();i++,r2++){
     Int_t tpcl_nseq = r2->nseq;
     Int_t tpcl_nhits = r2->nhits;
     m_nseq_cluster->Fill(tpcl_nseq);
     m_nhits->Fill(tpcl_nhits);
    }
  }

}

