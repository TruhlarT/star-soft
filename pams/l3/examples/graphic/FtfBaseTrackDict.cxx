//
// File generated by rootcint at Fri May 19 13:19:38 2000.
// Do NOT change. Changes will be lost next time file is generated
//
#include "FtfBaseTrackDict.h"

#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TError.h"

//______________________________________________________________________________
TBuffer &operator>>(TBuffer &buf, FtfBaseTrack *&obj)
{
   // Read a pointer to an object of class FtfBaseTrack.

   ::Error("FtfBaseTrack::operator>>", "objects not inheriting from TObject need a specialized operator>> function"); if (obj) { }
   return buf;
}

//______________________________________________________________________________
void FtfBaseTrack::Streamer(TBuffer &R__b)
{
   // Stream an object of class FtfBaseTrack.

   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(); if (R__v) { }
      //R__b.ReadArray(firstHit);
      //R__b.ReadArray(lastHit);
      //R__b.ReadArray(currentHit);
      R__b >> bField;
      R__b >> id;
      R__b >> flag;
      R__b >> innerMostRow;
      R__b >> outerMostRow;
      R__b >> nHits;
      R__b >> nDedx;
      R__b >> q;
      R__b.ReadStaticArray(chi2);
      R__b >> dedx;
      R__b >> pt;
      R__b >> phi0;
      R__b >> psi;
      R__b >> r0;
      R__b >> tanl;
      R__b >> z0;
      R__b >> length;
      R__b >> dpt;
      R__b >> dpsi;
      R__b >> dz0;
      R__b >> eta;
      R__b >> dtanl;
      //R__b.ReadArray(para);
   } else {
      R__b.WriteVersion(FtfBaseTrack::IsA());
      //R__b.WriteArray(firstHit, __COUNTER__);
      //R__b.WriteArray(lastHit, __COUNTER__);
      //R__b.WriteArray(currentHit, __COUNTER__);
      R__b << bField;
      R__b << id;
      R__b << flag;
      R__b << innerMostRow;
      R__b << outerMostRow;
      R__b << nHits;
      R__b << nDedx;
      R__b << q;
      R__b.WriteArray(chi2, 2);
      R__b << dedx;
      R__b << pt;
      R__b << phi0;
      R__b << psi;
      R__b << r0;
      R__b << tanl;
      R__b << z0;
      R__b << length;
      R__b << dpt;
      R__b << dpsi;
      R__b << dz0;
      R__b << eta;
      R__b << dtanl;
      //R__b.WriteArray(para, __COUNTER__);
   }
}

//______________________________________________________________________________
void FtfBaseTrack::ShowMembers(TMemberInspector &R__insp, char *R__parent)
{
   // Inspect the data members of an object of class FtfBaseTrack.

   TClass *R__cl  = FtfBaseTrack::IsA();
   Int_t   R__ncp = strlen(R__parent);
   if (R__ncp || R__cl || R__insp.IsA()) { }
   R__insp.Inspect(R__cl, R__parent, "*firstHit", &firstHit);
   R__insp.Inspect(R__cl, R__parent, "*lastHit", &lastHit);
   R__insp.Inspect(R__cl, R__parent, "*currentHit", &currentHit);
   R__insp.Inspect(R__cl, R__parent, "bField", &bField);
   R__insp.Inspect(R__cl, R__parent, "id", &id);
   R__insp.Inspect(R__cl, R__parent, "flag", &flag);
   R__insp.Inspect(R__cl, R__parent, "innerMostRow", &innerMostRow);
   R__insp.Inspect(R__cl, R__parent, "outerMostRow", &outerMostRow);
   R__insp.Inspect(R__cl, R__parent, "nHits", &nHits);
   R__insp.Inspect(R__cl, R__parent, "nDedx", &nDedx);
   R__insp.Inspect(R__cl, R__parent, "q", &q);
   R__insp.Inspect(R__cl, R__parent, "chi2[2]", chi2);
   R__insp.Inspect(R__cl, R__parent, "dedx", &dedx);
   R__insp.Inspect(R__cl, R__parent, "pt", &pt);
   R__insp.Inspect(R__cl, R__parent, "phi0", &phi0);
   R__insp.Inspect(R__cl, R__parent, "psi", &psi);
   R__insp.Inspect(R__cl, R__parent, "r0", &r0);
   R__insp.Inspect(R__cl, R__parent, "tanl", &tanl);
   R__insp.Inspect(R__cl, R__parent, "z0", &z0);
   R__insp.Inspect(R__cl, R__parent, "length", &length);
   R__insp.Inspect(R__cl, R__parent, "dpt", &dpt);
   R__insp.Inspect(R__cl, R__parent, "dpsi", &dpsi);
   R__insp.Inspect(R__cl, R__parent, "dz0", &dz0);
   R__insp.Inspect(R__cl, R__parent, "eta", &eta);
   R__insp.Inspect(R__cl, R__parent, "dtanl", &dtanl);
   R__insp.Inspect(R__cl, R__parent, "*para", &para);
}

/********************************************************
* FtfBaseTrackDict.cxx
********************************************************/

#ifdef G__MEMTEST
#undef malloc
#endif

extern "C" void G__cpp_reset_tagtableFtfBaseTrackDict();

extern "C" void G__set_cpp_environmentFtfBaseTrackDict() {
  G__add_compiledheader("TROOT.h");
  G__add_compiledheader("TMemberInspector.h");
  G__add_compiledheader("../inc/FtfBaseTrack.h");
  G__cpp_reset_tagtableFtfBaseTrackDict();
}
extern "C" int G__cpp_dllrevFtfBaseTrackDict() { return(51111); }

/*********************************************************
* Member function Interface Method
*********************************************************/

/* FtfBaseTrack */
static int G__FtfBaseTrack_fitHelix_2_0(G__value *result7,G__CONST char *funcname,struct G__param *libp,int hash) {
      G__letint(result7,105,(long)((FtfBaseTrack*)(G__getstructoffset()))->fitHelix());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__FtfBaseTrack_fitCircle_3_0(G__value *result7,G__CONST char *funcname,struct G__param *libp,int hash) {
      G__letint(result7,105,(long)((FtfBaseTrack*)(G__getstructoffset()))->fitCircle());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__FtfBaseTrack_fitLine_4_0(G__value *result7,G__CONST char *funcname,struct G__param *libp,int hash) {
      G__letint(result7,105,(long)((FtfBaseTrack*)(G__getstructoffset()))->fitLine());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__FtfBaseTrack_getCurrentHit_5_0(G__value *result7,G__CONST char *funcname,struct G__param *libp,int hash) {
      G__letint(result7,85,(long)((FtfBaseTrack*)(G__getstructoffset()))->getCurrentHit());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__FtfBaseTrack_getPara_6_0(G__value *result7,G__CONST char *funcname,struct G__param *libp,int hash) {
      G__letint(result7,85,(long)((FtfBaseTrack*)(G__getstructoffset()))->getPara());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__FtfBaseTrack_getErrorsCircleFit_7_0(G__value *result7,G__CONST char *funcname,struct G__param *libp,int hash) {
      G__letint(result7,105,(long)((FtfBaseTrack*)(G__getstructoffset()))->getErrorsCircleFit((double)G__double(libp->para[0]),(double)G__double(libp->para[1])
,(double)G__double(libp->para[2])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__FtfBaseTrack_arcLength_8_0(G__value *result7,G__CONST char *funcname,struct G__param *libp,int hash) {
      G__letdouble(result7,100,(double)((FtfBaseTrack*)(G__getstructoffset()))->arcLength((double)G__double(libp->para[0]),(double)G__double(libp->para[1])
,(double)G__double(libp->para[2]),(double)G__double(libp->para[3])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__FtfBaseTrack_closestApproach_9_0(G__value *result7,G__CONST char *funcname,struct G__param *libp,int hash) {
      {
        Ftf3DHit *pobj,xobj=((FtfBaseTrack*)(G__getstructoffset()))->closestApproach((double)G__double(libp->para[0]),(double)G__double(libp->para[1]));
        pobj=new Ftf3DHit(xobj);
        result7->obj.i=(long)((void*)pobj); result7->ref=result7->obj.i;
        G__store_tempobject(*result7);
      }
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__FtfBaseTrack_extraRadius_0_1(G__value *result7,G__CONST char *funcname,struct G__param *libp,int hash) {
      {
        Ftf3DHit *pobj,xobj=((FtfBaseTrack*)(G__getstructoffset()))->extraRadius((double)G__double(libp->para[0]));
        pobj=new Ftf3DHit(xobj);
        result7->obj.i=(long)((void*)pobj); result7->ref=result7->obj.i;
        G__store_tempobject(*result7);
      }
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__FtfBaseTrack_extraRCyl_1_1(G__value *result7,G__CONST char *funcname,struct G__param *libp,int hash) {
      G__letint(result7,105,(long)((FtfBaseTrack*)(G__getstructoffset()))->extraRCyl(*(double*)G__Doubleref(&libp->para[0]),*(double*)G__Doubleref(&libp->para[1])
,*(double*)G__Doubleref(&libp->para[2]),*(double*)G__Doubleref(&libp->para[3])
,*(double*)G__Doubleref(&libp->para[4]),*(double*)G__Doubleref(&libp->para[5])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__FtfBaseTrack_intersectorZLine_2_1(G__value *result7,G__CONST char *funcname,struct G__param *libp,int hash) {
      G__letint(result7,105,(long)((FtfBaseTrack*)(G__getstructoffset()))->intersectorZLine((double)G__double(libp->para[0]),(double)G__double(libp->para[1])
,*(Ftf3DHit*)libp->para[2].ref));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__FtfBaseTrack_getClosest_3_1(G__value *result7,G__CONST char *funcname,struct G__param *libp,int hash) {
      {
        Ftf3DHit *pobj,xobj=((FtfBaseTrack*)(G__getstructoffset()))->getClosest((double)G__double(libp->para[0]),(double)G__double(libp->para[1])
,*(double*)G__Doubleref(&libp->para[2]),*(double*)G__Doubleref(&libp->para[3])
,*(double*)G__Doubleref(&libp->para[4]));
        pobj=new Ftf3DHit(xobj);
        result7->obj.i=(long)((void*)pobj); result7->ref=result7->obj.i;
        G__store_tempobject(*result7);
      }
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__FtfBaseTrack_getClosest_4_1(G__value *result7,G__CONST char *funcname,struct G__param *libp,int hash) {
      G__letint(result7,105,(long)((FtfBaseTrack*)(G__getstructoffset()))->getClosest(
(double)G__double(libp->para[0]),(double)G__double(libp->para[1])
,(double)G__double(libp->para[2]),(double)G__double(libp->para[3])
,(double)G__double(libp->para[4]),*(double*)G__Doubleref(&libp->para[5])
,*(double*)G__Doubleref(&libp->para[6])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__FtfBaseTrack_updateToRadius_5_1(G__value *result7,G__CONST char *funcname,struct G__param *libp,int hash) {
      G__setnull(result7);
      ((FtfBaseTrack*)(G__getstructoffset()))->updateToRadius((double)G__double(libp->para[0]));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__FtfBaseTrack_updateToClosestApproach_6_1(G__value *result7,G__CONST char *funcname,struct G__param *libp,int hash) {
      G__setnull(result7);
      ((FtfBaseTrack*)(G__getstructoffset()))->updateToClosestApproach((double)G__double(libp->para[0]),(double)G__double(libp->para[1]));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__FtfBaseTrack_phiRotate_7_1(G__value *result7,G__CONST char *funcname,struct G__param *libp,int hash) {
      G__letint(result7,105,(long)((FtfBaseTrack*)(G__getstructoffset()))->phiRotate((double)G__double(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__FtfBaseTrack_startLoop_8_1(G__value *result7,G__CONST char *funcname,struct G__param *libp,int hash) {
      G__setnull(result7);
      ((FtfBaseTrack*)(G__getstructoffset()))->startLoop();
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__FtfBaseTrack_nextHit_9_1(G__value *result7,G__CONST char *funcname,struct G__param *libp,int hash) {
      G__setnull(result7);
      ((FtfBaseTrack*)(G__getstructoffset()))->nextHit();
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__FtfBaseTrack_done_0_2(G__value *result7,G__CONST char *funcname,struct G__param *libp,int hash) {
      G__letint(result7,105,(long)((FtfBaseTrack*)(G__getstructoffset()))->done());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__FtfBaseTrack_Print_1_2(G__value *result7,G__CONST char *funcname,struct G__param *libp,int hash) {
      G__setnull(result7);
      ((FtfBaseTrack*)(G__getstructoffset()))->Print((int)G__int(libp->para[0]));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__FtfBaseTrack_DeclFileName_2_2(G__value *result7,G__CONST char *funcname,struct G__param *libp,int hash) {
      G__letint(result7,67,(long)((FtfBaseTrack*)(G__getstructoffset()))->DeclFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__FtfBaseTrack_DeclFileLine_3_2(G__value *result7,G__CONST char *funcname,struct G__param *libp,int hash) {
      G__letint(result7,105,(long)((FtfBaseTrack*)(G__getstructoffset()))->DeclFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__FtfBaseTrack_ImplFileName_4_2(G__value *result7,G__CONST char *funcname,struct G__param *libp,int hash) {
      G__letint(result7,67,(long)((FtfBaseTrack*)(G__getstructoffset()))->ImplFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__FtfBaseTrack_ImplFileLine_5_2(G__value *result7,G__CONST char *funcname,struct G__param *libp,int hash) {
      G__letint(result7,105,(long)((FtfBaseTrack*)(G__getstructoffset()))->ImplFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__FtfBaseTrack_Class_Version_6_2(G__value *result7,G__CONST char *funcname,struct G__param *libp,int hash) {
      G__letint(result7,115,(long)((FtfBaseTrack*)(G__getstructoffset()))->Class_Version());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__FtfBaseTrack_Class_7_2(G__value *result7,G__CONST char *funcname,struct G__param *libp,int hash) {
      G__letint(result7,85,(long)((FtfBaseTrack*)(G__getstructoffset()))->Class());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__FtfBaseTrack_IsA_8_2(G__value *result7,G__CONST char *funcname,struct G__param *libp,int hash) {
      G__letint(result7,85,(long)((const FtfBaseTrack*)(G__getstructoffset()))->IsA());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__FtfBaseTrack_ShowMembers_9_2(G__value *result7,G__CONST char *funcname,struct G__param *libp,int hash) {
      G__setnull(result7);
      ((FtfBaseTrack*)(G__getstructoffset()))->ShowMembers(*(TMemberInspector*)libp->para[0].ref,(char*)G__int(libp->para[1]));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__FtfBaseTrack_Streamer_0_3(G__value *result7,G__CONST char *funcname,struct G__param *libp,int hash) {
      G__setnull(result7);
      ((FtfBaseTrack*)(G__getstructoffset()))->Streamer(*(TBuffer*)libp->para[0].ref);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__FtfBaseTrack_Dictionary_1_3(G__value *result7,G__CONST char *funcname,struct G__param *libp,int hash) {
      G__setnull(result7);
      ((FtfBaseTrack*)(G__getstructoffset()))->Dictionary();
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic destructor
static int G__FtfBaseTrack_wAFtfBaseTrack_2_3(G__value *result7,G__CONST char *funcname,struct G__param *libp,int hash) {
   if(G__getaryconstruct())
     if(G__PVOID==G__getgvp())
       delete[] (FtfBaseTrack *)(G__getstructoffset());
     else
       for(int i=G__getaryconstruct()-1;i>=0;i--)
         delete (FtfBaseTrack *)((G__getstructoffset())+sizeof(FtfBaseTrack)*i);
   else  delete (FtfBaseTrack *)(G__getstructoffset());
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}


/* Setting up global function */

/*********************************************************
* Member function Stub
*********************************************************/

/* FtfBaseTrack */

/*********************************************************
* Global function Stub
*********************************************************/

/*********************************************************
* Get size of pointer to member function
*********************************************************/
class G__Sizep2memfuncFtfBaseTrackDict {
 public:
  G__Sizep2memfuncFtfBaseTrackDict() {p=&G__Sizep2memfuncFtfBaseTrackDict::sizep2memfunc;}
    size_t sizep2memfunc() { return(sizeof(p)); }
  private:
    size_t (G__Sizep2memfuncFtfBaseTrackDict::*p)();
};

size_t G__get_sizep2memfuncFtfBaseTrackDict()
{
  G__Sizep2memfuncFtfBaseTrackDict a;
  G__setsizep2memfunc((int)a.sizep2memfunc());
  return((size_t)a.sizep2memfunc());
}


/*********************************************************
* virtual base class offset calculation interface
*********************************************************/

   /* Setting up class inheritance */

/*********************************************************
* Inheritance information setup/
*********************************************************/
extern "C" void G__cpp_setup_inheritanceFtfBaseTrackDict() {

   /* Setting up class inheritance */
}

/*********************************************************
* typedef information setup/
*********************************************************/
extern "C" void G__cpp_setup_typetableFtfBaseTrackDict() {

   /* Setting up typedef entry */
   G__search_typename2("Char_t",99,-1,0,
-1);
   G__setnewtype(-1,"Signed Character 1 byte",0);
   G__search_typename2("UChar_t",98,-1,0,
-1);
   G__setnewtype(-1,"Unsigned Character 1 byte",0);
   G__search_typename2("Short_t",115,-1,0,
-1);
   G__setnewtype(-1,"Signed Short integer 2 bytes",0);
   G__search_typename2("UShort_t",114,-1,0,
-1);
   G__setnewtype(-1,"Unsigned Short integer 2 bytes",0);
   G__search_typename2("Int_t",105,-1,0,
-1);
   G__setnewtype(-1,"Signed integer 4 bytes",0);
   G__search_typename2("UInt_t",104,-1,0,
-1);
   G__setnewtype(-1,"Unsigned integer 4 bytes",0);
   G__search_typename2("Seek_t",105,-1,0,
-1);
   G__setnewtype(-1,"File pointer",0);
   G__search_typename2("Long_t",108,-1,0,
-1);
   G__setnewtype(-1,"Signed long integer 8 bytes",0);
   G__search_typename2("ULong_t",107,-1,0,
-1);
   G__setnewtype(-1,"Unsigned long integer 8 bytes",0);
   G__search_typename2("Float_t",102,-1,0,
-1);
   G__setnewtype(-1,"Float 4 bytes",0);
   G__search_typename2("Double_t",100,-1,0,
-1);
   G__setnewtype(-1,"Float 8 bytes",0);
   G__search_typename2("Text_t",99,-1,0,
-1);
   G__setnewtype(-1,"General string",0);
   G__search_typename2("Bool_t",98,-1,0,
-1);
   G__setnewtype(-1,"Boolean (0=false, 1=true)",0);
   G__search_typename2("Byte_t",98,-1,0,
-1);
   G__setnewtype(-1,"Byte (8 bits)",0);
   G__search_typename2("Version_t",115,-1,0,
-1);
   G__setnewtype(-1,"Class version identifier",0);
   G__search_typename2("Option_t",99,-1,0,
-1);
   G__setnewtype(-1,"Option string",0);
   G__search_typename2("Ssiz_t",105,-1,0,
-1);
   G__setnewtype(-1,"String size",0);
   G__search_typename2("Real_t",102,-1,0,
-1);
   G__setnewtype(-1,"TVector and TMatrix element type",0);
   G__search_typename2("VoidFuncPtr_t",89,-1,0,
-1);
   G__setnewtype(-1,"pointer to void function",0);
   G__search_typename2("FreeHookFun_t",89,-1,0,
-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("ReAllocFun_t",81,-1,0,
-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("ReAllocCFun_t",81,-1,0,
-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("Axis_t",102,-1,0,
-1);
   G__setnewtype(-1,"Axis values type",0);
   G__search_typename2("Stat_t",100,-1,0,
-1);
   G__setnewtype(-1,"Statistics type",0);
}

/*********************************************************
* Data Member information setup/
*********************************************************/

   /* Setting up class,struct,union tag member variable */

   /* FtfBaseTrack */
static void G__setup_memvarFtfBaseTrack(void) {
   G__tag_memvar_setup(G__get_linked_tagnum(&G__FtfBaseTrackDictLN_FtfBaseTrack));
   { FtfBaseTrack *p; p=(FtfBaseTrack*)0x1000; if (p) { }
   G__memvar_setup((void*)NULL,108,0,0,-1,-1,-1,4,"G__virtualinfo=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->firstHit)-(long)(p)),89,0,0,-1,-1,-1,1,"firstHit=",0,"First hit belonging to track");
   G__memvar_setup((void*)((long)(&p->lastHit)-(long)(p)),89,0,0,-1,-1,-1,1,"lastHit=",0,"Last  hit belonging to track");
   G__memvar_setup((void*)((long)(&p->currentHit)-(long)(p)),89,0,0,-1,-1,-1,1,"currentHit=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->bField)-(long)(p)),100,0,0,-1,-1,-1,1,"bField=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->id)-(long)(p)),105,0,0,-1,-1,-1,1,"id=",0,"primary key ");
   G__memvar_setup((void*)((long)(&p->flag)-(long)(p)),115,0,0,-1,-1,-1,1,"flag=",0,"Primaries flag=1, Secondaries flag=0      ");
   G__memvar_setup((void*)((long)(&p->innerMostRow)-(long)(p)),99,0,0,-1,-1,-1,1,"innerMostRow=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->outerMostRow)-(long)(p)),99,0,0,-1,-1,-1,1,"outerMostRow=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->nHits)-(long)(p)),115,0,0,-1,-1,-1,1,"nHits=",0,"Number of points assigned to that track");
   G__memvar_setup((void*)((long)(&p->nDedx)-(long)(p)),115,0,0,-1,-1,-1,1,"nDedx=",0,"Number of points used for dEdx");
   G__memvar_setup((void*)((long)(&p->q)-(long)(p)),115,0,0,-1,-1,-1,1,"q=",0,"charge ");
   G__memvar_setup((void*)((long)(&p->chi2)-(long)(p)),100,0,0,-1,-1,-1,1,"chi2[2]=",0,"chi squared of the momentum fit ");
   G__memvar_setup((void*)((long)(&p->dedx)-(long)(p)),100,0,0,-1,-1,-1,1,"dedx=",0,"dE/dx information ");
   G__memvar_setup((void*)((long)(&p->pt)-(long)(p)),100,0,0,-1,-1,-1,1,"pt=",0,"pt (transverse momentum) at (r,phi,z) ");
   G__memvar_setup((void*)((long)(&p->phi0)-(long)(p)),100,0,0,-1,-1,-1,1,"phi0=",0,"azimuthal angle of the first point ");
   G__memvar_setup((void*)((long)(&p->psi)-(long)(p)),100,0,0,-1,-1,-1,1,"psi=",0,"azimuthal angle of the momentum at (r,.. ");
   G__memvar_setup((void*)((long)(&p->r0)-(long)(p)),100,0,0,-1,-1,-1,1,"r0=",0,"r (in cyl. coord.) for the first point ");
   G__memvar_setup((void*)((long)(&p->tanl)-(long)(p)),100,0,0,-1,-1,-1,1,"tanl=",0,"tg of the dip angle at (r,phi,z) ");
   G__memvar_setup((void*)((long)(&p->z0)-(long)(p)),100,0,0,-1,-1,-1,1,"z0=",0,"z coordinate of the first point ");
   G__memvar_setup((void*)((long)(&p->length)-(long)(p)),100,0,0,-1,-1,-1,1,"length=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->dpt)-(long)(p)),100,0,0,-1,-1,-1,1,"dpt=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->dpsi)-(long)(p)),100,0,0,-1,-1,-1,1,"dpsi=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->dz0)-(long)(p)),100,0,0,-1,-1,-1,1,"dz0=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->eta)-(long)(p)),100,0,0,-1,-1,-1,1,"eta=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->dtanl)-(long)(p)),100,0,0,-1,-1,-1,1,"dtanl=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->para)-(long)(p)),89,0,0,-1,-1,-1,1,"para=",0,"Parameters pointer     ");
   G__memvar_setup((void*)NULL,85,0,0,G__get_linked_tagnum(&G__FtfBaseTrackDictLN_TClass),-1,-2,4,"fgIsA=",0,(char*)NULL);
   }
   G__tag_memvar_reset();
}

extern "C" void G__cpp_setup_memvarFtfBaseTrackDict() {
}
/***********************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
***********************************************************/

/*********************************************************
* Member function information setup for each class
*********************************************************/
static void G__setup_memfuncFtfBaseTrack(void) {
   /* FtfBaseTrack */
   G__tag_memfunc_setup(G__get_linked_tagnum(&G__FtfBaseTrackDictLN_FtfBaseTrack));
   G__memfunc_setup("fitHelix",829,G__FtfBaseTrack_fitHelix_2_0,105,-1,-1,0,0,1,1,0,"",(char*)NULL,(void*)NULL,0);
   G__memfunc_setup("fitCircle",917,G__FtfBaseTrack_fitCircle_3_0,105,-1,-1,0,0,1,1,0,"",(char*)NULL,(void*)NULL,0);
   G__memfunc_setup("fitLine",715,G__FtfBaseTrack_fitLine_4_0,105,-1,-1,0,0,1,1,0,"",(char*)NULL,(void*)NULL,0);
   G__memfunc_setup("getCurrentHit",1352,G__FtfBaseTrack_getCurrentHit_5_0,85,G__get_linked_tagnum(&G__FtfBaseTrackDictLN_FtfBaseHit),-1,0,0,1,1,0,"",(char*)NULL,(void*)NULL,0);
   G__memfunc_setup("getPara",708,G__FtfBaseTrack_getPara_6_0,85,G__get_linked_tagnum(&G__FtfBaseTrackDictLN_FtfPara),-1,0,0,1,1,0,"",(char*)NULL,(void*)NULL,0);
   G__memfunc_setup("getErrorsCircleFit",1842,G__FtfBaseTrack_getErrorsCircleFit_7_0,105,-1,-1,0,3,1,1,0,
"d - - 0 - a d - - 0 - b "
"d - - 0 - r",(char*)NULL,(void*)NULL,0);
   G__memfunc_setup("arcLength",920,G__FtfBaseTrack_arcLength_8_0,100,-1,-1,0,4,1,1,0,
"d - - 0 - x1 d - - 0 - y1 "
"d - - 0 - x2 d - - 0 - y2",(char*)NULL,(void*)NULL,0);
   G__memfunc_setup("closestApproach",1579,G__FtfBaseTrack_closestApproach_9_0,117,G__get_linked_tagnum(&G__FtfBaseTrackDictLN_Ftf3DHit),-1,0,2,1,1,0,
"d - - 0 - xBeam d - - 0 - yBeam",(char*)NULL,(void*)NULL,0);
   G__memfunc_setup("extraRadius",1164,G__FtfBaseTrack_extraRadius_0_1,117,G__get_linked_tagnum(&G__FtfBaseTrackDictLN_Ftf3DHit),-1,0,1,1,1,0,"d - - 0 - r",(char*)NULL,(void*)NULL,0);
   G__memfunc_setup("extraRCyl",926,G__FtfBaseTrack_extraRCyl_1_1,105,-1,-1,0,6,1,1,0,
"d - - 1 - r d - - 1 - phi "
"d - - 1 - z d - - 1 - rc "
"d - - 1 - xc d - - 1 - yc",(char*)NULL,(void*)NULL,0);
   G__memfunc_setup("intersectorZLine",1684,G__FtfBaseTrack_intersectorZLine_2_1,105,-1,-1,0,3,1,1,0,
"d - - 0 - a d - - 0 - b "
"u 'Ftf3DHit' - 1 - cross",(char*)NULL,(void*)NULL,0);
   G__memfunc_setup("getClosest",1053,G__FtfBaseTrack_getClosest_3_1,117,G__get_linked_tagnum(&G__FtfBaseTrackDictLN_Ftf3DHit),-1,0,5,1,1,0,
"d - - 0 - xBeam d - - 0 - yBeam "
"d - - 1 - rc d - - 1 - xc "
"d - - 1 - yc",(char*)NULL,(void*)NULL,0);
   G__memfunc_setup("getClosest",1053,G__FtfBaseTrack_getClosest_4_1,105,-1,-1,0,7,1,1,0,
"d - - 0 - xBeam d - - 0 - yBeam "
"d - - 0 - rc d - - 0 - xc "
"d - - 0 - yc d - - 1 - xClosest "
"d - - 1 - yClosest",(char*)NULL,(void*)NULL,0);
   G__memfunc_setup("updateToRadius",1454,G__FtfBaseTrack_updateToRadius_5_1,121,-1,-1,0,1,1,1,0,"d - - 0 - r",(char*)NULL,(void*)NULL,0);
   G__memfunc_setup("updateToClosestApproach",2385,G__FtfBaseTrack_updateToClosestApproach_6_1,121,-1,-1,0,2,1,1,0,
"d - - 0 - xBeam d - - 0 - yBeam",(char*)NULL,(void*)NULL,0);
   G__memfunc_setup("phiRotate",944,G__FtfBaseTrack_phiRotate_7_1,105,-1,-1,0,1,1,1,0,"d - - 0 - deltaPhi",(char*)NULL,(void*)NULL,0);
   G__memfunc_setup("startLoop",968,G__FtfBaseTrack_startLoop_8_1,121,-1,-1,0,0,1,1,0,"",(char*)NULL,(void*)NULL,1);
   G__memfunc_setup("nextHit",740,G__FtfBaseTrack_nextHit_9_1,121,-1,-1,0,0,1,1,0,"",(char*)NULL,(void*)NULL,3);
   G__memfunc_setup("done",422,G__FtfBaseTrack_done_0_2,105,-1,-1,0,0,1,1,0,"",(char*)NULL,(void*)NULL,1);
   G__memfunc_setup("Print",525,G__FtfBaseTrack_Print_1_2,121,-1,-1,0,1,1,1,0,"i - - 0 - level",(char*)NULL,(void*)NULL,0);
   G__memfunc_setup("DeclFileName",1145,G__FtfBaseTrack_DeclFileName_2_2,67,-1,-1,0,0,1,1,1,"",(char*)NULL,(void*)NULL,0);
   G__memfunc_setup("DeclFileLine",1152,G__FtfBaseTrack_DeclFileLine_3_2,105,-1,-1,0,0,1,1,0,"",(char*)NULL,(void*)NULL,0);
   G__memfunc_setup("ImplFileName",1171,G__FtfBaseTrack_ImplFileName_4_2,67,-1,-1,0,0,1,1,1,"",(char*)NULL,(void*)NULL,0);
   G__memfunc_setup("ImplFileLine",1178,G__FtfBaseTrack_ImplFileLine_5_2,105,-1,-1,0,0,1,1,0,"",(char*)NULL,(void*)NULL,0);
   G__memfunc_setup("Class_Version",1339,G__FtfBaseTrack_Class_Version_6_2,115,-1,G__defined_typename("Version_t"),0,0,1,1,0,"",(char*)NULL,(void*)NULL,0);
   G__memfunc_setup("Class",502,G__FtfBaseTrack_Class_7_2,85,G__get_linked_tagnum(&G__FtfBaseTrackDictLN_TClass),-1,0,0,1,1,0,"",(char*)NULL,(void*)NULL,0);
   G__memfunc_setup("IsA",253,G__FtfBaseTrack_IsA_8_2,85,G__get_linked_tagnum(&G__FtfBaseTrackDictLN_TClass),-1,0,0,1,1,8,"",(char*)NULL,(void*)NULL,1);
   G__memfunc_setup("ShowMembers",1132,G__FtfBaseTrack_ShowMembers_9_2,121,-1,-1,0,2,1,1,0,
"u 'TMemberInspector' - 1 - insp C - - 0 - parent",(char*)NULL,(void*)NULL,1);
   G__memfunc_setup("Streamer",835,G__FtfBaseTrack_Streamer_0_3,121,-1,-1,0,1,1,1,0,"u 'TBuffer' - 1 - b",(char*)NULL,(void*)NULL,1);
   G__memfunc_setup("Dictionary",1046,G__FtfBaseTrack_Dictionary_1_3,121,-1,-1,0,0,1,1,0,"",(char*)NULL,(void*)NULL,0);
   // automatic destructor
   G__memfunc_setup("~FtfBaseTrack",1294,G__FtfBaseTrack_wAFtfBaseTrack_2_3,(int)('y'),-1,-1,0,0,1,1,0,"",(char*)NULL,(void*)NULL,1);
   G__tag_memfunc_reset();
}


/*********************************************************
* Member function information setup
*********************************************************/
extern "C" void G__cpp_setup_memfuncFtfBaseTrackDict() {
}

/*********************************************************
* Global variable information setup for each class
*********************************************************/
extern "C" void G__cpp_setup_globalFtfBaseTrackDict() {

   /* Setting up global variables */
   G__resetplocal();


   G__resetglobalenv();
}

/*********************************************************
* Global function information setup for each class
*********************************************************/
extern "C" void G__cpp_setup_funcFtfBaseTrackDict() {
   G__lastifuncposition();


   G__resetifuncposition();
}

/*********************************************************
* Class,struct,union,enum tag information setup
*********************************************************/
/* Setup class/struct taginfo */
G__linked_taginfo G__FtfBaseTrackDictLN_TClass = { "TClass" , 99 , -1 };
G__linked_taginfo G__FtfBaseTrackDictLN_FtfBaseTrack = { "FtfBaseTrack" , 99 , -1 };
G__linked_taginfo G__FtfBaseTrackDictLN_Ftf3DHit = { "Ftf3DHit" , 99 , -1 };
G__linked_taginfo G__FtfBaseTrackDictLN_FtfBaseHit = { "FtfBaseHit" , 99 , -1 };
G__linked_taginfo G__FtfBaseTrackDictLN_FtfPara = { "FtfPara" , 99 , -1 };

/* Reset class/struct taginfo */
extern "C" void G__cpp_reset_tagtableFtfBaseTrackDict() {
  G__FtfBaseTrackDictLN_TClass.tagnum = -1 ;
  G__FtfBaseTrackDictLN_FtfBaseTrack.tagnum = -1 ;
  G__FtfBaseTrackDictLN_Ftf3DHit.tagnum = -1 ;
  G__FtfBaseTrackDictLN_FtfBaseHit.tagnum = -1 ;
  G__FtfBaseTrackDictLN_FtfPara.tagnum = -1 ;
}

extern "C" void G__cpp_setup_tagtableFtfBaseTrackDict() {

   /* Setting up class,struct,union tag entry */
   G__tagtable_setup(G__get_linked_tagnum(&G__FtfBaseTrackDictLN_FtfBaseTrack),sizeof(FtfBaseTrack),-1,1,(char*)NULL,G__setup_memvarFtfBaseTrack,G__setup_memfuncFtfBaseTrack);
}
extern "C" void G__cpp_setupFtfBaseTrackDict() {
  G__check_setup_version(51111,"G__cpp_setupFtfBaseTrackDict()");
  G__set_cpp_environmentFtfBaseTrackDict();
  G__cpp_setup_tagtableFtfBaseTrackDict();

  G__cpp_setup_inheritanceFtfBaseTrackDict();

  G__cpp_setup_typetableFtfBaseTrackDict();

  G__cpp_setup_memvarFtfBaseTrackDict();

  G__cpp_setup_memfuncFtfBaseTrackDict();
  G__cpp_setup_globalFtfBaseTrackDict();
  G__cpp_setup_funcFtfBaseTrackDict();

   if(0==G__getsizep2memfunc()) G__get_sizep2memfuncFtfBaseTrackDict();
  return;
}
class G__cpp_setup_initFtfBaseTrackDict {
  public:
    G__cpp_setup_initFtfBaseTrackDict() { G__add_setup_func("FtfBaseTrackDict",&G__cpp_setupFtfBaseTrackDict); }
   ~G__cpp_setup_initFtfBaseTrackDict() { G__remove_setup_func("FtfBaseTrackDict"); }
};
G__cpp_setup_initFtfBaseTrackDict G__cpp_setup_initializerFtfBaseTrackDict;

