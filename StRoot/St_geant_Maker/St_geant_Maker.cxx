// $Id: St_geant_Maker.cxx,v 1.37 1999/04/19 06:29:30 nevski Exp 
// $Id: St_geant_Maker.cxx,v 1.41 1999/07/03 22:40:11 fine Exp $
// $Log: St_geant_Maker.cxx,v $
// Revision 1.41  1999/07/03 22:40:11  fine
// St_geant_Maker::Work - workaround of LINUX compiler problem
//
// Revision 1.40  1999/04/30 15:17:03  perev
// SetOutput added to announce Geometry exists
//
// Revision 1.39  1999/04/29 19:29:27  nevski
// SetInputFile returns status
//
// Revision 1.38  1999/04/20 21:40:17  nevski
// all shapes are going via Victors hash
//
// Revision 1.37  1999/04/19 06:29:30  nevski
// update of user parameter extraction
//
// Revision 1.36  1999/04/19 06:25:35  nevski
// update of user parameter extraction
//
// Revision 1.35  1999/04/15 20:36:40  fine
// St_geant::Work() was void becomes St_Node *
//
// Revision 1.34  1999/04/12 23:17:11  fine
// Unique postion ID has been introduced
//
// Revision 1.33  1999/04/09 23:52:48  nevski
// checking 3 volume parameters now
//
// Revision 1.32  1999/04/08 00:39:08  fine
// Work metod - workaround for ROOT bug PCON definition
//
// Revision 1.31  1999/04/07 12:59:45  fine
// Fixed bug for PCON and PGON shapes
//
// Revision 1.30  1999/04/06 19:40:08  nevski
// variable size volumes
//
// Revision 1.29  1999/03/22 14:45:23  nevski
// geometry tree corrected
//
// Revision 1.28  1999/03/20 22:43:05  perev
// Do(trig)
//
// Revision 1.27  1999/03/11 00:15:22  perev
// St_geant_Maker in new maker schema
//
// Revision 1.26  1999/03/04 19:32:16  nevski
// esm/eem corrected
//
// Revision 1.25  1999/02/24 17:12:27  fine
// St_Table::New has been activated
//
// Revision 1.24  1999/02/23 18:59:50  nevski
// SVT 4th layer added to svt hit table
//
// Revision 1.23  1999/02/22 23:55:57  fine
// St_geant_Maker::rootmaptable is prepaed to use St_TableNew(), not activated yet
//
// Revision 1.22  1999/02/22 20:51:25  fisyak
// Mismatch between ctb/tof
//
// Revision 1.21  1999/02/22 19:27:20  fisyak
// add gtrigi and gtigc
//
// Revision 1.20  1999/02/20 20:23:45  fisyak
// Fix Aeast
//
// Revision 1.18  1999/02/19 14:41:00  fisyak
// Set kIsNotOwn Bit for geometry tables
//
// Revision 1.17  1999/02/18 15:44:47  fisyak
// Cleanup warinings
//
// Revision 1.16  1999/02/17 22:42:07  fisyak
// fix Linux parameters
//
// Revision 1.15  1999/02/17 15:55:38  fisyak
// Add GSTAR to ROOT geometry tables transformation
//
// Revision 1.14  1999/02/16 18:15:45  fisyak
// Check in the latest updates to fix them
//
// Revision 1.13  1999/02/12 17:57:01  nevski
// particle table
//
// Revision 1.12  1999/02/12 14:18:27  nevski
// merging 2 mods
//
// Revision 1.5  1999/01/10 20:37:31  fisyak
// Give access to Zebra
//
// Revision 1.4  1999/01/05 01:37:02  fisyak
// Intermeidate version with St_Node
//
// Revision 1.3  1999/01/03 20:56:35  fisyak
// Remove St_geom_Maker
//
// Revision 1.7  1998/12/25 21:02:13  nevski
// Add Set/Get method
//
// Revision 1.6  1998/12/17 14:38:00  fisyak
// Change default to no Higz window
//
// Revision 1.5  1998/12/16 20:56:24  fisyak
// Add gstar to ROOT
//
// Revision 1.4  1998/12/12 00:21:15  fisyak
// Remove gstar for the moment
//
// Revision 1.3  1998/12/12 00:18:00  fisyak
// Remove gstar for the moment
//
// Revision 1.2  1998/12/04 19:36:47  fisyak
// Add Pavel/Ruben gstar interface
//
// Revision 1.1  1998/10/31 00:28:31  fisyak
// Makers take care about branches
//
// Revision 1.6  1998/10/06 18:00:29  perev
// cleanup
//
// Revision 1.5  1998/10/02 13:46:08  fine
// DataSet->DataSetIter
//
// Revision 1.4  1998/08/14 15:25:58  fisyak
// add options
//
// Revision 1.3  1998/08/10 02:32:07  fisyak
// Clean up
//
// Revision 1.2  1998/07/20 15:08:15  fisyak
// Add tcl and tpt
//
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//               St_geant_Maker class for Makers                        //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "St_geant_Maker.h"
#include "StChain.h"
#include "St_DataSetIter.h"
#include "St_Table.h"
#include <iostream.h>
#include <stdio.h>
#include <string.h>
#include "GtHash.h"
#include "TGeometry.h"
#include "TMaterial.h"
#include "TMixture.h"
#include "TString.h"
#include "TInterpreter.h"
#include "TClassTable.h"    
#include "St_Node.h"
#include "TMath.h"
#include "TBRIK.h"
#include "TTRD1.h"
#include "TTRD2.h"
#include "TTRAP.h"
#include "TTUBE.h"
#include "TTUBS.h"
#include "TCONE.h"
#include "TCONS.h"
#include "TSPHE.h"
#include "TPARA.h"
#include "TPGON.h"
#include "TPCON.h"
#include "TELTU.h"
//     #include "THYPE.h"
#include "TGTRA.h"
#include "TCTUB.h"
#include "TGeant3.h"
#include "St_g2t_run_Table.h"
#include "St_g2t_event_Table.h"
#include "St_g2t_gepart_Table.h"
#include "St_g2t_vertex_Table.h"
#include "St_g2t_track_Table.h"

#include "St_DataSetIter.h"
#include "g2r/St_g2t_get_kine_Module.h"
#include "g2r/St_g2t_svt_Module.h"
#include "g2r/St_g2t_tpc_Module.h"
#include "g2r/St_g2t_mwc_Module.h"
#include "g2r/St_g2t_ftp_Module.h"
#include "g2r/St_g2t_ctb_Module.h"
#include "g2r/St_g2t_tof_Module.h"
#include "g2r/St_g2t_rch_Module.h"
#include "g2r/St_g2t_emc_Module.h"
#include "g2r/St_g2t_smd_Module.h"
#include "g2r/St_g2t_eem_Module.h"
#include "g2r/St_g2t_esm_Module.h"
#include "g2r/St_g2t_zdc_Module.h"
#include "g2r/St_g2t_vpd_Module.h"
#include "g2r/St_g2t_particle_Module.h"

common_gcbank *cbank;
common_quest  *cquest; 
common_gclink *clink; 
common_gccuts *ccuts; 
common_gcflag *cflag; 
common_gckine *ckine; 
common_gcking *cking; 
common_gcmate *cmate; 
common_gctmed *ctmed; 
common_gctrak *ctrak; 
common_gctpol *ctpol; 
common_gcvolu *cvolu; 
common_gcnum  *cnum; 
common_gcsets *csets; 

Int_t *z_iq, *z_lq; 
Float_t *z_q; 
Int_t   nlev;
#ifdef F77_NAME
#define gfnhit_ F77_NAME(gfnhit,GFNHIT)
#define csjcal_ F77_NAME(csjcal,CSJCAL)
#define csaddr_ F77_NAME(csaddr,CSADDR)
#endif
# define csaddr csaddr_
# define csjcal csjcal_
typedef long int (*addrfun)(); 
extern "C" void type_of_call *csaddr_(char *name, int l77name=0);
extern "C" long int type_of_call csjcal_(
                            addrfun *fun, /* addres of external routine */
                            int  *narg,   /* number   of arguments      */
                            ...);         /* other narg arguments       */

static Int_t irot = 0;
static St_Node *topnode=0;
typedef struct {
  Float_t par[50];
} params;
typedef struct {
  Float_t lseen, lstyle, lwidth, lcolor, lfill;
} attributes;

#define gfnhit gfnhit_
#define csaddr csaddr_
#define csjcal csjcal_

extern "C" void     type_of_call  gfnhit_(char*,char*,int*,int,int);
extern "C" void     type_of_call  agnzgete_(int* ILK,int* IDE,
             int* NPART,int* IRUN,int* IEVT,char* CGNAM,
             float* VERT,int* IWTFL,float* WEIGH);
/*
* Input : ILK   - Link number  : 1 = primary, 2 = secondary (obsolete)    *
*         IDE   - ID of event in gate ( ZEBRA IDN)                        *
* Output: NPART - Number of particles in event record                     *
*         IRUN  - run number as recorded by generator                     *
*         IEVT  - event number as recorded by generator                   *
*         CGNAM - generator name                                          *
*         VERT(4)- x,y,z,t of event (metres,seconds or mm,mm/c)           *
*         IWTFL - weight flag                                             *
*         WEIGH - event weight                                            *
*/
ClassImp(St_geant_Maker)

St_DataSet *St_geant_Maker::fgGeom = 0;
//_____________________________________________________________________________
St_geant_Maker::St_geant_Maker(const Char_t *name):
StMaker(name){
  nwgeant = 2000000;
  nwpaw   =       0;
  iwtype  =       0;
  fgGeom = new St_DataSet("geom");  
  m_ConstSet->Add(fgGeom);
  SetOutput(fgGeom);	//Declare this "geom" for output
  fEvtHddr = new StEvtHddr(m_ConstSet);
  SetOutput(fEvtHddr);	//Declare this "EvtHddr" for output
}

//_____________________________________________________________________________
St_geant_Maker::~St_geant_Maker(){
}
//_____________________________________________________________________________
Int_t St_geant_Maker::Init(){
// Initialize GEANT
  
  if (! TGeant3::fgGeant) {
    PrintInfo();
    new TGeant3("Geant","C++ Interface to Geant3",nwgeant,nwpaw,iwtype); 
  }
// Create Histograms    
  return StMaker::Init();
}
//_____________________________________________________________________________
Int_t St_geant_Maker::Make()
{
    Int_t    nhits,nhit1,nhit2,link=1,ide=1,npart,irun,ievt,iwtfl;
    Float_t  vert[4],weigh;

    Char_t   cgnam[20];
    int iRes = 0; if(iRes) {/*touch*/};
  
    agstroot_();
    Do("trig");

    // check EoF
    if (cquest->iquest[0]) {return kStEOF;}

    // empty g2t_event
    St_g2t_event *g2t_event = new St_g2t_event("g2t_event",1);  
    m_DataSet->Add(g2t_event);
    agnzgete_(&link,&ide,&npart,&irun,&ievt,cgnam,vert,&iwtfl,&weigh);

    fEvtHddr->SetRunNumber(irun);
    fEvtHddr->SetEventNumber(ievt);
    fEvtHddr->SetEventType(cgnam);

    if (npart>0) 
    {  
      St_particle  *particle   = new St_particle("particle",npart);
      m_DataSet->Add(particle);  iRes = g2t_particle(particle);
//    =======================

      particle_st *p = particle->GetTable();
      if (p->isthep == 10 && p->idhep  == 9999999) 
      {
	fEvtHddr->SetBImpact  (p->phep[0]);
	fEvtHddr->SetPhImpact (p->phep[1]);
	fEvtHddr->SetGenerType(p->phep[2]);
	fEvtHddr->SetCenterOfMassEnergy(p->phep[3]);
	Int_t west = (int)p->phep[4];
	Int_t east = (int)(1000.*p->phep[4]-1000.*((float)west));
	fEvtHddr->SetAWest(west);
	fEvtHddr->SetAEast(east);
	fEvtHddr->SetRunNumber(p->vhep[0]);
	fEvtHddr->SetEventNumber(p->vhep[1]);
	ULong_t  t = p->jdahep[1];
	if (t > 99999) t = 0;
	fEvtHddr->SetDateTime(p->jdahep[0],t);
	fEvtHddr->SetProdDateTime();
      }
    }
    St_g2t_vertex  *g2t_vertex  = new St_g2t_vertex("g2t_vertex",cnum->nvertx);
    m_DataSet->Add(g2t_vertex);
    St_g2t_track   *g2t_track   = new St_g2t_track ("g2t_track",cnum->ntrack);
    m_DataSet->Add(g2t_track);

    iRes = g2t_get_kine(g2t_vertex,g2t_track);
    
    
    //---------------------- inner part -------------------------//

    gfnhit_ ("SVTH","SVTD", &nhit1, 4,4);
    gfnhit_ ("SVTH","SFSD", &nhit2, 4,4);
    nhits=nhit1+nhit2;
    if (nhits>0) { 
      St_g2t_svt_hit *g2t_svt_hit = new St_g2t_svt_hit("g2t_svt_hit",nhits);
      m_DataSet->Add(g2t_svt_hit);

      iRes = g2t_svt(g2t_track,g2t_svt_hit);
//	     ===============================
    }

    gfnhit_ ("TPCH","TPAD", &nhits, 4,4);
    if (nhits>0){ 
      St_g2t_tpc_hit *g2t_tpc_hit = new St_g2t_tpc_hit("g2t_tpc_hit",nhits);
      m_DataSet->Add(g2t_tpc_hit);

      iRes = g2t_tpc(g2t_track,g2t_tpc_hit);
//	     ==============================
    }

    gfnhit_ ("TPCH","TMSE", &nhits, 4,4);
    if (nhits>0) { 
      St_g2t_mwc_hit *g2t_mwc_hit = new St_g2t_mwc_hit("g2t_mwc_hit",nhits);
      m_DataSet->Add(g2t_mwc_hit);
      iRes = g2t_mwc(g2t_track,g2t_mwc_hit);
//	     ==============================
    }

    gfnhit_ ("FTPH","FSEC", &nhits, 4,4);
    if (nhits>0){
      St_g2t_ftp_hit *g2t_ftp_hit = new St_g2t_ftp_hit("g2t_ftp_hit",nhits);
      m_DataSet->Add(g2t_ftp_hit);
      iRes = g2t_ftp(g2t_track,g2t_ftp_hit);
//           ===============================
    }

    gfnhit_ ("BTOH","BXSA", &nhits, 4,4);
    if (nhits>0) { 
      St_g2t_ctf_hit *g2t_ctb_hit = new St_g2t_ctf_hit("g2t_ctb_hit",nhits);
      m_DataSet->Add(g2t_ctb_hit);
      iRes = g2t_ctb(g2t_track,g2t_ctb_hit);
//           ==============================
    }

    gfnhit_ ("BTOH","BCSB", &nhits, 4,4);
    if (nhits>0) {
      St_g2t_ctf_hit *g2t_tof_hit = new St_g2t_ctf_hit("g2t_tof_hit",nhits);
      m_DataSet->Add(g2t_tof_hit);
      iRes = g2t_tof(g2t_track,g2t_tof_hit);
//           ==============================
    }

    gfnhit_ ("RICH","RGAP", &nhit1, 4,4);
    gfnhit_ ("RICH","RCSI", &nhit2, 4,4);
    nhits=nhit1+nhit2;
    if (nhits>0) {
      St_g2t_rch_hit *g2t_rch_hit = new St_g2t_rch_hit("g2t_rch_hit",nhits);
      m_DataSet->Add(g2t_rch_hit);
      iRes = g2t_rch(g2t_track,g2t_rch_hit);
//           ==============================
    }
    
    //---------------------- calorimeters -------------------------//
    gfnhit_ ("CALH","CSUP", &nhits, 4,4);
    if (nhits>0) {
      St_g2t_emc_hit *g2t_emc_hit = new St_g2t_emc_hit("g2t_emc_hit",nhits);
      m_DataSet->Add(g2t_emc_hit);
      iRes = g2t_emc(g2t_track,g2t_emc_hit);
//           ==============================
    }

    gfnhit_ ("CALH","CSDA", &nhits, 4,4);
    if (nhits>0) {
      St_g2t_emc_hit *g2t_smd_hit = new St_g2t_emc_hit("g2t_smd_hit",nhits);
      m_DataSet->Add(g2t_smd_hit);
      iRes = g2t_smd(g2t_track,g2t_smd_hit);
//           ==============================
    }

    gfnhit_ ("ECAH","ESCI", &nhits, 4,4);
    if (nhits>0) {
      St_g2t_emc_hit *g2t_eem_hit = new St_g2t_emc_hit("g2t_eem_hit",nhits);
      m_DataSet->Add(g2t_eem_hit);
      iRes = g2t_eem(g2t_track,g2t_eem_hit);
//           ==============================
    }

    gfnhit_ ("ECAH","EXSE", &nhits, 4,4);
    if (nhits>0) {
      St_g2t_emc_hit *g2t_esm_hit = new St_g2t_emc_hit("g2t_esm_hit",nhits);
      m_DataSet->Add(g2t_esm_hit);
      iRes = g2t_esm(g2t_track,g2t_esm_hit);
//           ==============================
    }

    gfnhit_ ("VPDH","VRAD", &nhits, 4,4);
    if (nhits>0) {
      St_g2t_vpd_hit *g2t_vpd_hit = new St_g2t_vpd_hit("g2t_vpd_hit",nhits);
      m_DataSet->Add(g2t_vpd_hit);
      iRes = g2t_vpd(g2t_track,g2t_vpd_hit);
//           ==============================
    }

    gfnhit_ ("ZCAH","QSCI", &nhits, 4,4);
    if (nhits>0) {
      St_g2t_emc_hit *g2t_zdc_hit = new St_g2t_emc_hit("g2t_zdc_hit",nhits);
      m_DataSet->Add(g2t_zdc_hit);
      iRes = g2t_zdc(g2t_track,g2t_zdc_hit);
//           ==============================
    }
//------------------------all bloody detectors done--------------------//
#if 0
    Char_t *g2t = "g2t_";
    Int_t  narg = 0;
    addrfun address  = (addrfun ) csaddr(g2t,strlen(g2t));
    if (address) csjcal(&address,&narg);
#endif

  if (cflag->ieorun) {return kStEOF;} 
  else               {return kStOK;}
}
//_____________________________________________________________________________
void St_geant_Maker::LoadGeometry(Char_t *option){
  Init(); 
  if (strlen(option)) Do (option); 
  geometry_();
}
//_____________________________________________________________________________
void St_geant_Maker::PrintInfo(){
  printf("**************************************************************\n");
  printf("* $Id: St_geant_Maker.cxx,v 1.41 1999/07/03 22:40:11 fine Exp $\n");
  printf("**************************************************************\n");
  if (Debug()) StMaker::PrintInfo();
}
//_____________________________________________________________________________
void St_geant_Maker::Draw()
{ 
  int    idiv=2,Ldummy,one=1,zero=0,iw=1;
  Char_t   *path=" ",*opt="IN";
  dzddiv_ (&idiv,&Ldummy,path,opt,&one,&zero,&one,&iw,1,2);
}
//_____________________________________________________________________________
void St_geant_Maker::Do(const Char_t *job)
{  
  Init();
  int l=strlen(job);
  if (l) kuexel_(job,l);
}
//_____________________________________________________________________________
void St_geant_Maker::G2root()
{  
  TRotMatrix *rotm=0;
  Char_t     astring[20];
  Int_t      jmate=clink->jmate;
  Int_t      nmate=0;   
  if (jmate) nmate=z_iq[jmate-2];
  
  if (!gGeometry) gGeometry=new TGeometry("STAR","STAR GEANT3 ROOT geometry");
  //-----------List of Materials and Mixtures--------------
  TMaterial *newmat = 0;
  TMixture *newmixt = 0;
  for (Int_t imat=1; imat<= nmate; imat++)
  {
    Int_t jma = z_lq[jmate-imat];
    if (! jma) continue;

    Int_t nmixt = (Int_t) z_q[jma+11];
    TString MatName((const Char_t *) &(z_iq[jma+1]), 20); 
    TString Matname(MatName.Strip());
    Int_t nm = TMath::Abs(nmixt);
    // Case of a simple matrial
    if (nm <= 1) 
    {
      sprintf (astring,"mat%i",imat);
      TString Astring(astring);
      if (z_q[jma+6] < 1.0 && z_q[jma+7] < 1.0) 
      {
	newmat = new TMaterial ((Char_t *)Astring.Data(),
				(Char_t *)Matname.Data(), 0, 0, 0);
      }
      else 
      {
	newmat = new TMaterial ((Char_t *)Astring.Data(),
				(Char_t *)Matname.Data(), 
				z_q[jma+6], z_q[jma+7], z_q[jma+8]);
      }
    }
    else {
      Int_t jmixt = z_lq[jma-5];
      sprintf (astring,"mix%i",imat);
      TString Astring(astring);
      newmixt = new TMixture ((Char_t *)Astring.Data(),(Char_t *)Matname.Data(),nmixt);
      for (Int_t im=1; im <= nm; im++){
	newmixt->DefineElement(im-1, z_q[jmixt+im], z_q[jmixt+nm+im], z_q[jmixt+2*nm+im]);
      }
    }
  }
  //-----------List of Rotation matrices--------------
  Int_t   jrotm   = clink->jrotm; 
  Int_t   nrotm   = 0;   if (jrotm)  nrotm  = z_iq[jrotm-2]; 
  for (irot=1; irot<=nrotm; irot++) {
    Int_t jr = z_lq[jrotm-irot];
    if (! jr) continue;
    sprintf(astring,"rotm%i",irot);
    rotm = new TRotMatrix(astring,astring,z_q[jr+11],z_q[jr+12],
			  z_q[jr+13],z_q[jr+14],
			  z_q[jr+15],z_q[jr+16]);
  }
  //---------- Shapes ---------------------

  Int_t   jvolum = clink->jvolum;
  Int_t   nvolum = 0;   if (jvolum) nvolum = z_iq[jvolum-2];
  Int_t   ivo    = 0;

  for (ivo = 1; ivo <= nvolum; ivo++)
  { Int_t jvo = z_lq[jvolum-ivo];
    if (!jvo) continue;
    TShape*  t;
    TString  name((const Char_t *) &(z_iq[jvolum+ivo]), 4);
    t = (TShape *) gGeometry->GetListOfShapes()->FindObject(name.Data());
    if (!t) {t = MakeShape(&name,ivo);}
  }

//----------- Nodes -------------------  
  Int_t Nlevel = 0;
  Int_t Names[15];
  Int_t Numbers[15];
  ivo = 1;
  TString  name((const Char_t *) &(z_iq[jvolum+ivo]), 4);
  TShape*  shape = (TShape *) gGeometry->GetListOfShapes()->FindObject(name.Data());
  if (!shape) {shape = MakeShape(&name,ivo);}
  topnode = new St_Node(name.Data(), name.Data(), shape);
  Names[0] = z_iq[jvolum+ivo];
  Numbers[0] = 1;
  St_Node *node = 0;
  node = MakeNode(&name, ivo, Nlevel, Names, Numbers);
}

//_____________________________________________________________________________
St_Node *St_geant_Maker::MakeNode(TString *name, Int_t ivo, Int_t Nlevel, Int_t *Names, Int_t *Numbers){
  St_Node *node = 0;
  Int_t   jvolum  = clink->jvolum;
  Int_t jvo = z_lq[jvolum-ivo];
  if (jvo) {
    node = (St_Node *) topnode->FindObject(name->Data());
    if (! node) {
      TShape *shape = (TShape *) gGeometry->GetListOfShapes()->FindObject(name->Data());
      if (!shape ) {shape = MakeShape(name,ivo);}
      node = new St_Node(name->Data(), name->Data(), shape);
    }

    Int_t nin =(Int_t) z_q[jvo+3];
    if (nin > 0) 
    {
      Nlevel++;
      for (Int_t in=1; in<= nin; in++) 
      {
	Int_t jin   =        z_lq[jvo-in];
	Int_t ivom  = (Int_t) z_q[jin+2];
	Int_t nuser = (Int_t) z_q[jin+3];
	TString  namem((const Char_t *) &(z_iq[jvolum+ivom]), 4);

	Names[Nlevel] = z_iq[jvolum+ivom];
	Numbers[Nlevel] = nuser;
	Int_t   nlevv = Nlevel+1;
	Int_t   Ierr;
	Float_t xx[3], theta1,phi1, theta2,phi2, theta3,phi3, type;

	glvolu (&nlevv, &Names[0], &Numbers[0], &Ierr);

	gfxzrm_ (&Nlevel, &xx[0],&xx[1],&xx[2], 
                          &theta1,&phi1, &theta2,&phi2, &theta3,&phi3, &type);
        St_Node *newnode = (St_Node *) topnode->FindObject(namem.Data());

	if (!newnode) 
        {  newnode = MakeNode(&namem, ivom, nlevv, Names, Numbers);  }

	irot++;
	Char_t ss[12];
	sprintf(ss,"rotm%i",irot);
	TRotMatrix *rotm = new TRotMatrix(ss,ss, 
                           theta1,phi1, theta2,phi2, theta3,phi3);
	node->Add(newnode,xx[0],xx[1],xx[2],rotm);
      }
    }
    if (nin < 0) {
      Nlevel++;
    }
    if (nin == 0) {Nlevel--;}
  }
  return node;
}
//_____________________________________________________________________________
TShape *St_geant_Maker::MakeShape(TString *name, Int_t ivo){
  // make geant3 volume
  typedef enum {BOX=1,TRD1,TRD2,TRAP,TUBE,TUBS,CONE,CONS,SPHE,PARA,
		PGON,PCON,ELTU,HYPE,GTRA=28,CTUB} shapes;
  Int_t jvolum  = clink->jvolum;
  Int_t jvo = z_lq[jvolum-ivo];
  TShape*  t;
  shapes   shape  = (shapes) z_q[jvo+2];
  Int_t    numed  = (Int_t)  z_q[jvo+4];
  Int_t    npar   = (Int_t)  z_q[jvo+5];
  params  *p      = (params *)&z_q[jvo+7];
  attributes *att = (attributes *)(&z_q[jvo+7] + npar);
  Int_t    jtmed  = clink->jtmed;
  Int_t    jtm    =          z_lq[jtmed-numed];
  Int_t    nmat   =          (int)z_q[jtm+6];
  Int_t    jmate  = clink->jmate;
  Int_t    jma    =          z_lq[jmate-nmat];
  Int_t    nmixt  = (Int_t)  z_q[jma+11];
  Int_t    nm     = TMath::Abs(nmixt);

  Char_t   astring[20];
  if (nm <= 1)  sprintf (astring,"mat%i",nmat); 
  else          sprintf (astring,"mix%i",nmat);   

  TString Astring(astring);
  t = (TShape *) gGeometry->GetListOfShapes()->FindObject(name->Data());
  if (!t) {
    switch (shape) {
    case BOX:  t = new TBRIK((Char_t *) name->Data(),"BRIK",(Char_t *) Astring.Data(),
			     p->par[0],p->par[1],p->par[2]);      
    break;
    case TRD1: t = new TTRD1((Char_t *) name->Data(),"TRD1",(Char_t *) Astring.Data(),
			     p->par[0],p->par[1],p->par[2],p->par[3]);
    break;
    case TRD2: t = new TTRD2((Char_t *) name->Data(),"TRD2",(Char_t *) Astring.Data(),
			     p->par[0],p->par[1],p->par[2],p->par[3],p->par[4]);
    break;
    case TRAP: t = new TTRAP((Char_t *) name->Data(),"TRAP",(Char_t *) Astring.Data(),
			     p->par[0],p->par[1],p->par[2],p->par[3],p->par[4],
			     p->par[5],p->par[6],p->par[7],p->par[8],p->par[9],
			     p->par[10]);
    break;
    case TUBE: t = new TTUBE((Char_t *) name->Data(),"TUBE",(Char_t *) Astring.Data(),
			     p->par[0],p->par[1],p->par[2]); 
    break;
    case TUBS: t = new TTUBS((Char_t *) name->Data(),"TUBS",(Char_t *) Astring.Data(),
			     p->par[0],p->par[1],p->par[2],p->par[3],p->par[4]);
    break;
    case CONE: t = new TCONE((Char_t *) name->Data(),"CONE",(Char_t *) Astring.Data(),
			     p->par[0],p->par[1],p->par[2],p->par[3],p->par[4]);
    break;
    case CONS: t = new TCONS((Char_t *) name->Data(),"CONS",(Char_t *) Astring.Data(),
			     p->par[0],p->par[1],p->par[2],p->par[3],p->par[4],
			     p->par[5],p->par[6]);
    break;
    case SPHE: t = new TSPHE((Char_t *) name->Data(),"SPHE",(Char_t *) Astring.Data(),
			     p->par[0],p->par[1],p->par[2],p->par[3],p->par[4],
			     p->par[5]);
    break;
    case PARA: t = new TPARA((Char_t *) name->Data(),"PARA",(Char_t *) Astring.Data(),
			     p->par[0],p->par[1],p->par[2],p->par[3],p->par[4],
			     p->par[5]);
    break;
    case PGON: t = new TPGON((Char_t *) name->Data(),"PGON",(Char_t *) Astring.Data(),
			     p->par[0],p->par[1],p->par[2],p->par[3]);
    break;
    case PCON: t = new TPCON((Char_t *) name->Data(),"PCON",(Char_t *) Astring.Data(),
			     p->par[0],p->par[1],p->par[2]);
    break;
    case ELTU: t = new TELTU((Char_t *) name->Data(),"ELTU",(Char_t *) Astring.Data(),
			     p->par[0],p->par[1],p->par[2]);
    break;
    //      case HYPE: t = new THYPE((Char_t *) name->Data(),"HYPE",(Char_t *) Astring.Data(),
    //			       p->par[0],p->par[1],p->par[2],p->par[3]);
    //      break;
    case GTRA: t = new TGTRA((Char_t *) name->Data(),"GTRA",(Char_t *) Astring.Data(),
			     p->par[0],p->par[1],p->par[2],p->par[3],p->par[4],
			     p->par[5],p->par[6],p->par[7],p->par[8],p->par[9],
			     p->par[10],p->par[11]); 
    break;
    case CTUB: t = new TCTUB((Char_t *) name->Data(),"CTUB",(Char_t *) Astring.Data(),
			     p->par[0],p->par[1],p->par[2],p->par[3],p->par[4],
			     p->par[5],p->par[6],p->par[7],p->par[8],p->par[9],
			     p->par[10]);
    break;
    //      default:   t = new TBRIK((Char_t *) name->Data(),"BRIK",(Char_t *) Astring.Data(),
    //			       p->par[0],p->par[1],p->par[2]);
    //      break;

    default: assert(0);

    } 
    if (att->lseen  != 1) t->SetVisibility(att->lseen);
    if (att->lstyle != 1) t->SetLineStyle(att->lstyle);
    if (att->lwidth != 1) t->SetLineWidth(att->lwidth);
    if (att->lcolor != 1) t->SetLineColor(att->lcolor);
    if (att->lfill  != 1) t->SetFillStyle(att->lfill);
  }
  return t;
}
//_____________________________________________________________________________
void St_geant_Maker::Call(const Char_t *name)
{  
  Int_t  narg = 0;
  addrfun address  = (addrfun ) csaddr((char*)name,strlen(name));
  if (address) csjcal(&address,&narg);
}
//_____________________________________________________________________________
St_Node *St_geant_Maker::Work()
{  
  struct  Medium 
    { Char_t name[20]; Int_t nmat, isvol, ifield; Float_t fieldm; };
  struct  Volume
    { Char_t name[4],nick[4]; Int_t npar; Float_t par[50]; };

  St_Node   *node=0;
  Float_t   *volu=0, *position=0, *mother=0, *p=0;
  Int_t     who=0, copy=0, npar=0;
  Int_t     nvol=cnum->nvolum;
  Float_t   theta1,phi1, theta2,phi2, theta3,phi3, type;
  TObjArray nodes(nvol+1);

  new TGeometry("STAR","nash STAR");
  GtHash *H = new GtHash;
 
  printf(" looping on agvolume \n");
  //   ===============================================================
  while (agvolume_(&node,&volu,&position,&mother,&who,&copy,&p,&npar)) 
  { // ===============================================================
  
    typedef enum {BOX=1,TRD1,TRD2,TRAP,TUBE,TUBS,CONE,CONS,SPHE,PARA,
                        PGON,PCON,ELTU,HYPE,GTRA=28,CTUB} shapes;
    TShape*  t;
    shapes   shape   = (shapes) volu[1];
    Int_t    nin     = 0;
    //   Int_t    medium  = (Int_t)  volu[3]; 
    Int_t    np      = (Int_t)  volu[4];
    Float_t* p0      = volu+6;
    Float_t* att     = volu+6+np;
    Char_t   name[]  = {0,0,0,0,0};
    Char_t   nick[]  = {0,0,0,0,0};
    float    xx[3]   = {0.,0.,0.};
    St_Node *newNode = 0;
    if (mother)  nin = (Int_t) mother[2];
    St_Node *Hp      = 0;

    strncpy(nick,(const Char_t*)&cvolu->names[cvolu->nlevel-1],4);
    strncpy(name,(const Char_t*)(volu-5),4);

    Hp = (St_Node *) H->GetPointer(p,npar+1);
    if (Hp)  newNode = Hp; 
    else
      { // printf(" creating object %s  %f  %f  %f \n", name,p[0],p[1],p[2]);
      switch (shape) 
      { case BOX:  t=new TBRIK(nick,"BRIK","void",
                         p[0],p[1],p[2]);                         break;
        case TRD1: t=new TTRD1(nick,"TRD1","void",
                         p[0],p[1],p[2],p[3]);                    break;
        case TRD2: t=new TTRD2(nick,"TRD2","void",
                         p[0],p[1],p[2],p[3],p[4]);               break;
        case TRAP: t=new TTRAP(nick,"TRAP","void",
                         p[0],p[1],p[2],p[3],p[4],p[5],
                         p[6],p[7],p[8],p[9],p[10]);              break;
        case TUBE: t=new TTUBE(nick,"TUBE","void",
                         p[0],p[1],p[2]);                         break;
        case TUBS: t=new TTUBS(nick,"TUBS","void",
                         p[0],p[1],p[2],p[3],p[4]);               break;
        case CONE: t=new TCONE(nick,"CONE","void",
                         p[0],p[1],p[2],p[3],p[4]);               break;
        case CONS: t=new TCONS(nick,"CONS","void",    // take care !
                         p[0],p[1],p[2],p[3],p[4],p[5],p[6]);     break;
//                         p[1],p[2],p[3],p[4],p[0],p[5],p[6]);     break;
        case SPHE: t=new TSPHE(nick,"SPHE","void",
                         p[0],p[1],p[2],p[3],p[4],p[5]);          break;
        case PARA: t=new TPARA(nick,"PARA","void",
                         p[0],p[1],p[2],p[3],p[4],p[5]);          break;
        case PGON: t=new TPGON(nick,"PGON","void",p[0],p[1],p[2],p[3]);  
                   { Float_t *pp = p+4;
                     for (Int_t i=0; i<p[3]; i++) {
                          Float_t z    = *pp++;
                          Float_t rmin = *pp++;
                          Float_t rmax = *pp++;
                         ((TPCON *)t)->DefineSection(i,z,rmin,rmax);
// this is because of a compiler bug on Linux (VF 030699)
//                         (( TPGON*)t)->DefineSection(i,*pp++,*pp++,*pp++);
                     }
                   }                                              break;
        case PCON: t=new TPCON(nick,"PCON","void",p[0],p[1],p[2]);
                   { Float_t *pp = p+3;
                     for (Int_t i=0; i<p[2]; i++) {
                          Float_t z    = *pp++;
                          Float_t rmin = *pp++;
                          Float_t rmax = *pp++;
                         ((TPCON *)t)->DefineSection(i,z,rmin,rmax);
// this is because of a compiler bug on Linux (VF 030699)
//                         ((TPCON *)t)->DefineSection(i,*pp++,*pp++,*pp++);
                     }
                   }                                              break;
        case ELTU: t=new TELTU(nick,"ELTU","void",
                         p[0],p[1],p[2]);                         break;
//      case HYPE: t=new THYPE(nick,"HYPE","void",
//                       p[0],p[1],p[2],p[3]);                    break;
        case GTRA: t=new TGTRA(nick,"GTRA","void",
                         p[0],p[1],p[2],p[3],p[4],p[5],
                         p[6],p[7],p[8],p[9],p[10],p[11]);        break;
        case CTUB: t=new TCTUB(nick,"CTUB","void",
                         p[0],p[1],p[2],p[3],p[4],p[5],
                         p[6],p[7],p[8],p[9],p[10]);              break;
        default:   t=new TBRIK(nick,"BRIK","void",
                         p[0],p[1],p[2]);                         break;
      };
      t->SetLineColor(att[4]);
 
      // to build a compressed tree, name should be checked for repetition
      newNode = new St_Node(name,nick,t);
//      newNode -> SetVisibility(ENodeSEEN(MapGEANT2StNodeVis(att[1])));
      newNode -> SetVisibility((St_Node::ENodeSEEN)St_Node::MapGEANT2StNodeVis(att[1]));
      H->SetPointer(newNode);
    }

    if (node)
    {  gfxzrm_ (&nlev, &xx[0],&xx[1],&xx[2], &theta1,&phi1, 
                       &theta2,&phi2, &theta3,&phi3, &type);
       TRotMatrix *matrix=GetMatrix(theta1,phi1,theta2,phi2,theta3,phi3);
       node->Add(newNode,xx[0],xx[1],xx[2],matrix,UInt_t(copy));
    }
    node = newNode;
  };

  fNode=node;
  gGeometry->GetListOfNodes()->Add(node);
  return GetNode();
}

//------------------------------------------------------------------------
static Bool_t CompareMatrix(TRotMatrix &a,TRotMatrix &b)
{  double *pa=a.GetMatrix(); double *pb=b.GetMatrix();
   for (int i=0; i<9; i++)  if (pa[i]!=pb[i]) return kFALSE;
   return kTRUE;
}

TRotMatrix *St_geant_Maker::GetMatrix(float thet1, float phii1,
                                      float thet2, float phii2,
                                      float thet3, float phii3)
{  char mname[20];
   THashList *list = gGeometry->GetListOfMatrices();
   int n=list->GetSize(); sprintf(mname,"matrix%d",n+1);
   TRotMatrix *pattern=new TRotMatrix(mname,mname,
                                      thet1,phii1,thet2,phii2,thet3,phii3);
   
   TRotMatrix *matrix=0; TIter nextmatrix(list);
   while ((matrix=(TRotMatrix *) nextmatrix())) 
   { if (matrix!=pattern) 
     { if (CompareMatrix(*matrix,*pattern)) 
       { list->Remove(pattern); delete pattern; return matrix; }
   } }
   return pattern;
}
//------------------------------------------------------------------------
void type_of_call rootmaptable_(Char_t *Cdest,Char_t *Table, Char_t* Spec, 
                                                      Int_t *k, Char_t *iq)
{ 
   St_geant_Maker::RootMapTable(Cdest,Table, Spec, k, iq); 
}
//------------------------------------------------------------------------
void St_geant_Maker::RootMapTable(Char_t *Cdest,Char_t *Table, Char_t* Spec, 
                                                      Int_t *k, Char_t *iq)
{
  TString TableName(Table); 
  TString t = TableName.Strip();
  t.ToLower();

  // Use St_Table::New(...)  when it is available as follows:
  St_Table *table =  St_Table::New(t.Data(),t.Data(),iq,*k);
  if (table) {fgGeom->Add(table); table->SetBit(kIsNotOwn);}
  else       cout << "Dictionary for table :" << t.Data() 
                  << " has not been defined yet. Skip it" 
                  << endl;
}
//------------------------------------------------------------------------
void  St_geant_Maker::SetDebug(EDebugLevel dbl)
{
  StMaker::SetDebug(dbl);
  if (GetDebug()) { Do("debug on;"); } else {Do("debug off;"); }
}
//------------------------------------------------------------------------
Int_t St_geant_Maker::SetInputFile(const char *file)
{
  fInputFile = file;
  TString kuip("gfile p "); kuip += fInputFile;
  Do((const char*)kuip); 
  if (cquest->iquest[0]) {return kStEOF;}
  return kStOK;
}
//------------------------------------------------------------------------

