/***************************************************************************
 *
 * $Id: StEstMaker.cxx,v 1.6 2001/02/16 15:17:43 lmartin Exp $
 *
 * Author: PL,AM,LM,CR (Warsaw,Nantes)
 ***************************************************************************
 *
 * Description: Main methods for StEstMaker
 *
 ***************************************************************************
 *
 * $Log: StEstMaker.cxx,v $
 * Revision 1.6  2001/02/16 15:17:43  lmartin
 * SSD off by default. cout replaced by gMessMgr.
 *
 * Revision 1.5  2001/02/07 19:16:29  caines
 * Fix sun non compilation for non-fixed size array
 *
 * Revision 1.4  2001/01/31 16:52:19  lmartin
 * mParams[]->debug replaced by mDebug.
 * phi and z params for StEstIndexGeom remove from StEstParams.
 *
 * Revision 1.3  2001/01/31 15:05:58  caines
 * Added check to BFChain evaluation option to decide wehter to set Idealtracking on
 *
 * Revision 1.2  2001/01/25 17:54:17  lmartin
 * Divorced from the real tracking code.
 * Initialize the StEstParams and StEstSegments objects controling the tracking.
 * Instantiate a StEstTracker object and calls the initializing, running and saving
 * methods of this object
 *
 * Revision 1.1  2000/12/07 11:14:21  lmartin
 * First CVS commit
 *
 **************************************************************************/
#include "StMessMgr.h"
#include "StEstMaker.h"
#include "StEstTracker.h"
#include "StEstParams.hh"
#include "StSvtClassLibrary/StSvtHybridCollection.hh"
#include "tables/St_dst_vertex_Table.h"
#include "tables/St_svg_geom_Table.h"
#include "tables/St_svg_shape_Table.h"
#include "tables/St_svg_config_Table.h"
#include "tables/St_scs_spt_Table.h"
#include "tables/St_egr_egrpar_Table.h"
#include "tables/St_tpt_track_Table.h" 
#include "tables/St_tcl_tphit_Table.h" 
#include "tables/St_tte_eval_Table.h" 
#include "tables/St_stk_track_Table.h" 
#include "tables/St_sgr_groups_Table.h" 
#include "tables/St_svm_evt_match_Table.h" 

ClassImp(StEstMaker)

StEstMaker::StEstMaker(const char* name):StMaker(name) {

}

StEstMaker::~StEstMaker() {

}

Int_t StEstMaker::Finish() {

  return StMaker::Finish();

}

Int_t StEstMaker::Init(){
  int i,j;

  gMessMgr->Info("StEstMaker::Init START");

  // creating the egr_par table.
  m_egr_egrpar = new St_egr_egrpar("egr_egrpar",1); {
    egr_egrpar_st row;
    //
    memset(&row,0,m_egr_egrpar->GetRowSize());
    row.debug[0]         =          1; // flags for debug printing ;
    row.debug[1]         =          0;
    row.debug[2]         =          0;
    row.debug[3]         =          0;
    row.debug[4]         =          0;
    row.debug[5]         =          0;
    row.debug[6]         =          0;
    row.debug[7]         =          0;
    row.debug[8]         =          0;
    row.minfit   =          2; // min no. of points on track ;
    row.mxtry    =         10; // max no. of attempts to fit ;
    row.useglobal = 2; // set if to usematching to be used ;
    row.usetpc   =  1; // set if TPC used in refit ;
    row.useemc   =          0; // set if EMC used in refit ;
    row.usesvt   =          0; // set if SVT used in refit ;
    row.usetof   =          0; // set if TOF used in refit ;
    row.usevert  =          0; // Set if primary vertex used in refit ;
    row.prob[0]  =        -200; // probability cut in fit ;
    row.prob[1]  =        -100;
    //    row.prob[0]  =        10; // probability cut in fit ;
    //    row.prob[1]  =        10;
//     row.prob[0]  =        -200; // probability cut in fit ;
    //     row.prob[1]  =        -100;
    row.svtchicut        =  0; // SVT chi2 cut for adding SVT-only tracks ;
    m_egr_egrpar->AddAt(&row,0);
  }
  
  AddRunCont(m_egr_egrpar);
 
  m_egrpar_h = new table_head_st[1];
  m_egrpar_h[0].maxlen=1;
  m_egrpar_h[0].nok=1;


  mNPass = 5;
  //  mNPass = 1;
  mIdealTracking=0;

 // ideal tracking: mIdealTracking = 1
    mIdealTracking = 1;
  mDebugLevel = 0;

  mParams = new StEstParams*[mNPass];
  for (i=0;i<mNPass;i++) mParams[i] = new StEstParams;

  // default settings, may be overridden by SetParams:
  for (i=0;i<mNPass;i++) {
    for (j=0;j<4;j++) {
      mParams[i]->nneighbours[j] = 2;
      mParams[i]->ntotbranch[j] = 6;
      mParams[i]->onoff[j] = 1;
      mParams[i]->share[j] = 5;
    }
    mParams[i]->onoff[3] = 0;
    mParams[i]->nbranch[3] = 3;
    mParams[i]->nbranch[2] = 2;
    mParams[i]->nbranch[1] = 1;
    mParams[i]->nbranch[0] = 1;

    mParams[i]->maxtpchits=50;
    mParams[i]->maxsvthits=8;    
    mParams[i]->maxbranches=100;     

    mParams[i]->lrad[0][0] = 6.125;
    mParams[i]->lrad[0][1] = 7.185;
    mParams[i]->lrad[1][0] = 10.185;
    mParams[i]->lrad[1][1] = 11.075;
    mParams[i]->lrad[2][0] = 13.995;
    mParams[i]->lrad[2][1] = 14.935;
    mParams[i]->lrad[3][0] = 23;
    mParams[i]->lrad[3][1] = 23;
  }	
    
  mParams[4]->ptmin = 0.1;
  mParams[4]->ptmax = 0.2;
  mParams[3]->ptmin = 0.2;
  mParams[3]->ptmax = 0.4;
  mParams[2]->ptmin = 0.4;
  mParams[2]->ptmax = 0.7;
  mParams[1]->ptmin = 0.7;
  mParams[1]->ptmax = 1.0;  
  mParams[0]->ptmin = 1.0;
  mParams[0]->ptmax = 100;

  mParams[0]->geomcutl[3] = 1.0;
  mParams[0]->geomcutl[2] = 0.5;
  mParams[0]->geomcutl[1] = 0.2;
  mParams[0]->geomcutl[0] = 0.2;
  mParams[0]->geomcutw[3] = 1.0;
  mParams[0]->geomcutw[2] = 0.5;
  mParams[0]->geomcutw[1] = 0.2;
  mParams[0]->geomcutw[0] = 0.2;

  mParams[1]->geomcutl[3] = 1.0;
  mParams[1]->geomcutl[2] = 0.5;
  mParams[1]->geomcutl[1] = 0.2;
  mParams[1]->geomcutl[0] = 0.2;
  mParams[1]->geomcutw[3] = 1.0;
  mParams[1]->geomcutw[2] = 0.5;
  mParams[1]->geomcutw[1] = 0.2;
  mParams[1]->geomcutw[0] = 0.2;
  
  mParams[2]->geomcutl[3] = 1.5;
  mParams[2]->geomcutl[2] = 0.5;
  mParams[2]->geomcutl[1] = 0.2;
  mParams[2]->geomcutl[0] = 0.2;
  mParams[2]->geomcutw[3] = 1.5;
  mParams[2]->geomcutw[2] = 0.5;
  mParams[2]->geomcutw[1] = 0.2;
  mParams[2]->geomcutw[0] = 0.2;
  
  mParams[3]->geomcutl[3] = 3.0;
  mParams[3]->geomcutl[2] = 0.5;
  mParams[3]->geomcutl[1] = 0.2;
  mParams[3]->geomcutl[0] = 0.2;
  mParams[3]->geomcutw[3] = 3.0;
  mParams[3]->geomcutw[2] = 0.5;
  mParams[3]->geomcutw[1] = 0.2;
  mParams[3]->geomcutw[0] = 0.2;
  
  mParams[4]->geomcutl[3] = 5.;
  mParams[4]->geomcutl[2] = 0.5;
  mParams[4]->geomcutl[1] = 0.2;
  mParams[4]->geomcutl[0] = 0.2;
  mParams[4]->geomcutw[3] = 5.;
  mParams[4]->geomcutw[2] = 0.5;
  mParams[4]->geomcutw[1] = 0.2;
  mParams[4]->geomcutw[0] = 0.2;


  // superpass settings

  mNSuperPass = 1;
  mSegments = new StEstSegments*[mNSuperPass];
  for (i=0;i<mNSuperPass;i++) mSegments[i] = new StEstSegments;

  mSegments[0]->chisqcut = 300;
  mSegments[0]->minhits=3;
  mSegments[0]->rminTPC=500;
  mSegments[0]->minTPChits=0;
  mSegments[0]->slay[3]=1;
  mSegments[0]->slay[2]=2;
  mSegments[0]->slay[1]=2;
  mSegments[0]->slay[0]=2;
  
//   mSegments[1]->chisqcut = 100;
//   mSegments[1]->minhits=3;
//   mSegments[1]->rminTPC=500;
//   mSegments[1]->minTPChits=0;
//   mSegments[1]->slay[3]=1;
//   mSegments[1]->slay[2]=1;
//   mSegments[1]->slay[1]=1;
//   mSegments[1]->slay[0]=1;

//   mSegments[2]->chisqcut = 30;
//   mSegments[2]->minhits=1;
//   mSegments[2]->rminTPC=500;
//   mSegments[2]->minTPChits=0;
//   mSegments[2]->slay[3]=1;
//   mSegments[2]->slay[2]=1;
//   mSegments[2]->slay[1]=1;
//   mSegments[2]->slay[0]=1;
  

//   mSegments[3]->chisqcut = 30;
//   mSegments[3]->minhits=2;
//   mSegments[3]->rminTPC=500;
//   mSegments[3]->minTPChits=0;
//   mSegments[3]->slay[3]=1;
//   mSegments[3]->slay[2]=1;
//   mSegments[3]->slay[1]=1;
//   mSegments[3]->slay[0]=1;

//   mSegments[4]->chisqcut = 40;
//   mSegments[4]->minhits=2;
//   mSegments[4]->rminTPC=100;
//   mSegments[4]->minTPChits=0;
//   mSegments[4]->slay[3]=1;
//   mSegments[4]->slay[2]=1;
//   mSegments[4]->slay[1]=1;
//   mSegments[4]->slay[0]=1;
  
  

  PrintSettings();
  gMessMgr->Info("StEstMaker::Init STOP");
  return kStOK;

}

void StEstMaker::PrintSettings() {
  // Print the tracking parameter settings.

  long j;

  gMessMgr->Info()<<"*********** Main Est Settings ************** \t\t\t\t"<<endm;
  gMessMgr->Info()<<"layer 0123 on(1)/off(0) : "
		  <<mParams[0]->onoff[0]<<" "
		  <<mParams[0]->onoff[1]<<" "
		  <<mParams[0]->onoff[2]<<" "
		  <<mParams[0]->onoff[3]<<"\t\t\t\t\t"<<endm;
  gMessMgr->Info()<<"number of passes : "<<mNPass<<"\t\t\t\t\t\t\t"<<endm;
  gMessMgr->Info()<<"See StEstMaker.cxx for more details on the pass parameters \t\t"<<endm;
  gMessMgr->Info()<<"number of superpasses : "<<mNSuperPass<<"\t\t\t\t\t\t"<<endm;
  gMessMgr->Info()<<"pass min hits(SVT) hitpattern max chi min hits(TPC) max r0(TPC) \t"<<endm;

  for (j=0;j<mNSuperPass;j++) 
    gMessMgr->Info()<<"  "<<j<<"\t"
		    <<mSegments[j]->minhits<<"\t\t"
		    <<mSegments[j]->slay[0] 
		    <<mSegments[j]->slay[1] 
		    <<mSegments[j]->slay[2] 
		    <<mSegments[j]->slay[3]<<"\t"
		    <<mSegments[j]->chisqcut<<"\t\t"
		    <<mSegments[j]->minTPChits<<"\t"
		    <<mSegments[j]->rminTPC<<"\t\t"<<endm;
  gMessMgr->Info()<<"******************************************** \t\t\t\t"<<endm;
}


Int_t StEstMaker::Make() {
  PrintInfo();

  const Int_t maxNofTracks = 50000;

  // Creating the output tables
  St_stk_track     *svttrk     = new St_stk_track("EstSvtTrk",maxNofTracks);
  AddData(svttrk);
  St_sgr_groups     *svtgrps   = new St_sgr_groups("EstGroups",maxNofTracks*4);
  AddData(svtgrps);
  St_svm_evt_match  *EstMatch  = new St_svm_evt_match("EstMatch",maxNofTracks);
  AddData(EstMatch);

  // Getting the input tables
  St_dst_vertex  *preVertex =0;
  preVertex = (St_dst_vertex *)GetDataSet("preVertex/.data/preVertex"); 

  St_DataSetIter       local(GetInputDB("svt"));
  // Getting the geometry and configuration tables
  St_svg_geom*   Stsvggeom  =0;
  
  St_DataSet *svt = GetDataSet("StSvtAnalResults");
  StSvtHybridCollection* SvtCluColl =0;
  if( svt)
    SvtCluColl = (StSvtHybridCollection*)(svt->GetObject());
  
  if( SvtCluColl){
    if(  !strncmp(SvtCluColl->getConfiguration(), "Y1L", strlen("Y1L"))){
      Stsvggeom        = (St_svg_geom  *) local("svgpars/geomy1l");
    }
  }
  
  if(!Stsvggeom)  Stsvggeom = (St_svg_geom *)local("svgpars/geom");
  if (!Stsvggeom) return kStWarn;

  St_svg_shape*   Stsvgshape =0;
  Stsvgshape = (St_svg_shape *)local("svgpars/shape");
  if (!Stsvgshape) return kStWarn;
  
  St_svg_config*   Stsvgconf =0;
  Stsvgconf = (St_svg_config *)local("svgpars/config");
  if (!Stsvgconf) return kStWarn;

  //Getting the SVT/SDD hit table
  St_scs_spt*   Stscsspt=0;
  svt  = GetInputDS("svt_hits");

  Stscsspt = (St_scs_spt *)svt->Find("scs_spt");
  if (!Stscsspt) { 
    gMessMgr->Warning("No SVT/SSD hits !");
    return kStWarn;
  }
  
  //Getting the TPC hit table
  St_tcl_tphit*   Sttphit=0;
  St_DataSet* tpc  = GetInputDS("tpc_hits");

  Sttphit = (St_tcl_tphit *)tpc->Find("tphit");
  if (!Sttphit) return kStWarn;

  //Getting the TPC track table
  St_tpt_track*   Sttptrack=0;
  tpc  = GetInputDS("tpc_tracks");

  Sttptrack = (St_tpt_track *)tpc->Find("tptrack");
  if (!Sttptrack) return kStWarn;


  //Getting the TPC evaluation table
  St_tte_eval*   Stevaltrk=0;
  St_g2t_track*   Stg2ttrack=0;
  St_g2t_vertex*   Stg2tvertex=0;
  if (mIdealTracking==1) {
    Stevaltrk = (St_tte_eval *)tpc->Find("evaltrk");
    St_DataSet *geant  = GetInputDS("geant");
    Stg2ttrack = (St_g2t_track *)geant->Find("g2t_track");
    Stg2tvertex = (St_g2t_vertex *)geant->Find("g2t_vertex");
  }
  if ((!Stevaltrk||!Stg2ttrack||!Stg2tvertex)&&mIdealTracking==1) {
    gMessMgr->Warning("Evaluation table(s) not found ! IdealTracking reset to 0");
    mIdealTracking=0;
  }

  gMessMgr->Info()<<"IdealTracking="<<mIdealTracking<<" DebugLevel="<<mDebugLevel<<endm;

  gMessMgr->Info()<<"StEstMaker : Constructing a Tracker"<<endm;
  StEstTracker* Tracker = new StEstTracker(mNPass,
					   mNSuperPass,
					   mIdealTracking,
					   mDebugLevel,
					   mParams,
					   mSegments,
					   m_egr_egrpar,
					   m_egrpar_h);

  gMessMgr->Info()<<"StEstMaker : Making the Wafer and Hit objects"<<endm;
  Tracker->SVTInit(Stsvggeom,
		   Stsvgshape,
		   Stsvgconf,
		   Stscsspt);

  gMessMgr->Info()<<"StEstMaker : Making a Vertex object"<<endm;
  Tracker->VertexSetup(preVertex);


  gMessMgr->Info()<<"StEstMaker : Making the Track objects"<<endm;
  Tracker->TPCInit(Sttptrack,Sttphit);
  Tracker->BranchInit();

  if (mIdealTracking==1) {
    gMessMgr->Info()<<"StEstMaker : Preparing the evaluation"<<endm;
    Tracker->SetupMc(Stscsspt,
		     Stevaltrk,
		     Stg2ttrack,
		     Stg2tvertex);
  }

  gMessMgr->Info()<<"StEstMaker : Doing the tracking"<<endm;
  Tracker->DoTracking();

  gMessMgr->Info()<<"StEstMaker : Saving into tables"<<endm;
  Tracker->EsttoGlobtrk(svttrk,
			svtgrps,
			EstMatch);

  gMessMgr->Info()<<"StEstMaker : Cleaning up"<<endm;
  Tracker->CleanUp();
  delete Tracker;
  return kStOK;

}
