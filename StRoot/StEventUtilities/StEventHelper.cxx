#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "TROOT.h"
#include "TClass.h"
#include "TBaseClass.h"
#include "TDataMember.h"
#include "TMethod.h"
#include "TMethodArg.h"
#include "TDataType.h"
#include "Api.h"
#include "TMemberInspector.h"
#include "TExMap.h"
#include "TCollection.h"
#include "TRegexp.h"
#include "TRandom.h"
#include "TError.h"
#include "TPoints3DABC.h"
#include "TSystem.h"
#include "TPad.h"
#include "TView.h"

#include "StEvent.h"
#include "StHit.h"
#include "StTrack.h"
#include "StTrackNode.h"
#include "StVertex.h"
#include "StTrackGeometry.h"
#include "StTrackDetectorInfo.h"
// For L3 filter
#include "StarClassLibrary/BetheBloch.h"
#include "StEvent/StDedxPidTraits.h"
// For coloring filter
#include "StEventTypes.h"
#include "StProbPidTraits.h"
#include "StTpcDedxPidAlgorithm.h"
#include "THelixTrack.h"

#define  __EVENTHELPER_ONLY__
#include "StEventHelper.h"
#undef   __EVENTHELPER_ONLY__

void Break(){printf("InBreak\n");}


class StEventInspector : public TMemberInspector {
public:
StEventInspector(TExMap *map,Int_t &count,const char *opt="");
virtual ~StEventInspector(){delete fSkip;};
virtual void Inspect(TClass* cl, const char* parent, const char* name, const void* addr);
        void CheckIn(TObject *obj,const char *bwname="");

Int_t &fCount;
TExMap *fMap;
TRegexp *fSkip;
TString fOpt;

};      

//______________________________________________________________________________
StEventInspector::StEventInspector(TExMap *map,Int_t &count,const char *opt):fCount(count)
{  
  fMap = map;
  fSkip = 0;
  fOpt = opt;
  if (fOpt.Length()) fSkip = new TRegexp(fOpt.Data());
}
//______________________________________________________________________________
void StEventInspector::Inspect(TClass* kl, const char* tit , const char* name, const void* addr)
{
  if(tit && strchr(tit,'.'))	return ;

  TString ts;

  if (!kl) return;
  if (name[0] == '*') name++;
  int ln = strcspn(name,"[ ");
  TString iname(name,ln);
  const char *iName=iname.Data();
  if (iName[1]=='P' && strcmp(iName,"fParent"       )==0) 	return;
  if (iName[0]=='G' && strcmp(iName,"G__virtualinfo")==0)	return;

  G__ClassInfo *classInfo = kl->GetClassInfo();  	
  if (!classInfo)		return;
  G__ClassInfo &cl = *classInfo;


// 		Browse data members
  G__DataMemberInfo m(cl);
  int found=0;
  const char *mName=0;
  while (m.Next()) {	// MemberLoop
     mName = m.Name();
     if (mName[1] != iName[1])	continue;
     if (strcmp(mName,iName) ) 	continue;
     found = 1; break;
  }     
  assert(found);

  // we skip: non TObjects
  //  - the member G__virtualinfo inserted by the CINT RTTI system

  long prop = m.Property() | m.Type()->Property();
  if (prop & G__BIT_ISFUNDAMENTAL) 	return;
  if (prop & G__BIT_ISSTATIC) 		return;
  if (prop & G__BIT_ISENUM) 		return;
  if (strcmp(m.Type()->Fullname(),"TObject") && !m.Type()->IsBase("TObject"))
  					return;

  int  size = sizeof(void*);
  if (!(prop&G__BIT_ISPOINTER)) size = m.Type()->Size(); 

  int nmax = 1;
  if (prop & G__BIT_ISARRAY) {
    for (int dim = 0; dim < m.ArrayDim(); dim++) nmax *= m.MaxIndex(dim);
  }

  for(int i=0; i<nmax; i++) {
    char *ptr = (char*)addr + i*size;
    TObject *obj = (prop&G__BIT_ISPOINTER) ? *((TObject**)ptr) : (TObject*)ptr;
    if (!obj) 		continue;
    const char *bwname = obj->ClassName();
    if (!bwname[0] || strcmp(bwname,obj->ClassName())==0) {
      bwname = name;
	int l = strcspn(bwname,"[ ");
	if (bwname[l]=='[') {
          char cbuf[12]; sprintf(cbuf,"[%02d]",i);
          ts.Replace(0,999,bwname,l);
          ts += cbuf;
          bwname = (const char*)ts;
      }  
    }  

    CheckIn(obj,bwname);

  }

}    
//______________________________________________________________________________
void StEventInspector::CheckIn(TObject *obj,const char *bwname)
{
  if (!obj) return;
  TObject *inobj=0;
  if (obj->InheritsFrom(StRefArray::Class())) return;  
  if (obj->InheritsFrom( StObjLink::Class())) return;  
  int n;
  if (fSkip && (fSkip->Index(obj->ClassName(),&n)>=0))	return;   

  if (obj->InheritsFrom(TCollection::Class())){
    TCollection *tcol = (TCollection*)obj;  
    TIter next(tcol);
    while ((inobj=next())) {CheckIn(inobj);}  
    return;
  }

  if (obj->InheritsFrom(StXRef::Class())){

     Long_t &inmap = (*fMap)(TMath::Hash(&obj,sizeof(void*)),(Long_t)obj);
     if (inmap) return;
     inmap = 1;fCount++;
  }

  if (obj->InheritsFrom(StStrArray::Class())){
//     if (obj->IsA()==StSPtrVecTrackNode::Class()) Break();
     Long_t &inmap = (*fMap)(TMath::Hash(&obj,sizeof(void*)),(Long_t)obj);
     if (inmap) return;
     inmap = 2; fCount++;
     int vecobj = ( obj->IsA() == StSPtrVecObject::Class());  
//     printf("%8d %p %s::%s\n",fLevel,(void*)obj,obj->GetName(),bwname);
     StStrArray *arr = (StStrArray*)obj; 
     int sz = arr->size();
     for (int idx=0;idx<sz; idx++) {
       inobj = arr->at(idx);
       Int_t count = fCount;
       CheckIn(inobj);
       if (count==fCount && !vecobj) break;  //if no action was made, no sense to continue
     }
     return;
  }

  char cbuf[1000];*cbuf=0;
  StEventInspector insp(fMap,fCount);
  obj->ShowMembers(insp,cbuf);
}
   


//______________________________________________________________________________
ClassImp(StEventHelper)
//______________________________________________________________________________
StEventHelper::StEventHelper(const TObject *evt,const char *opt)
{
   fMap = new TExMap();
   fObject = 0;
   Reset(evt,opt);
}
//______________________________________________________________________________
StEventHelper::~StEventHelper()
{
   delete fMap; fMap=0;
   Clear();
}
//______________________________________________________________________________
void StEventHelper::Clear(Option_t *opt)
{
}
//______________________________________________________________________________
void StEventHelper::Reset(const TObject *evt,const char *opt)
{
   if (fObject == evt) return;
   fObject = (TObject *)evt;
   Clear();
   fMap->Delete();
   if (!fObject) return;
   int kount=0;
   StEventInspector insp(fMap,kount,opt);
   char cbuf[1024];
   
   fObject->ShowMembers(insp,cbuf);
}
//______________________________________________________________________________
int StEventHelper::Kind(const TObject *to)
{
  static TClass *klass=0;
  static int who=0;
  int kind = 0;
  TClass *myClass=to->IsA(); 
  if (myClass!=klass) {
     klass = myClass; who = 0;
     if      (klass->InheritsFrom(      StHit::Class())) { who=kHIT;}
     else if (klass->InheritsFrom(    StTrack::Class())) { who=kTRK;}
     else if (klass->InheritsFrom(StPtrVecHit::Class())) { who=kHRR;}
     else if (klass->InheritsFrom(   StVertex::Class())) { who=kVTX;}
     else if (klass->InheritsFrom(  TObjArray::Class())) { who=kTRR;}
  }
  kind = who;
  if (kind==kHIT) {
    StHitHelper hh((StHit*)to);
    if (hh.IsUsed()) {kind|=kUSE;} else {kind|=kUNU;}
    if (hh.IsFit ())  kind|=kFIT;
    return kind;
  }
  return kind;
}
//______________________________________________________________________________
THelixTrack *StEventHelper::MyHelix(THelixTrack *myHlx,const StHelixD *evHlx)
{
  if (!myHlx) 	myHlx= new THelixTrack;
  double curv = evHlx->curvature();
  double phase = evHlx->phase();
  double dip   = evHlx->dipAngle();
  int h = evHlx->h();

  double myDir[3];
  myDir[0]= -sin(phase)*cos(dip);	
  myDir[1]=  cos(phase)*cos(dip);
  myDir[2]=             sin(dip);
  if (h<0) {myDir[0]=-myDir[0]; myDir[1]=-myDir[1];}
  double myX[3];
  myX[0]= evHlx->x(0.);
  myX[1]= evHlx->y(0.);
  myX[2]= evHlx->z(0.);
  
  myHlx->Set(myX,myDir,curv*h);
  double s = 10;
  double myXX[3];
  myHlx->Step(s,myXX);
  double diff = 0;
  diff += pow(myXX[0]-evHlx->x(s),2);
  diff += pow(myXX[1]-evHlx->y(s),2);
  diff += pow(myXX[2]-evHlx->z(s),2);
  diff = sqrt(diff);
  if (diff>1.e-5) {
  
    printf(" X %g %g\n",myXX[0]-myX[0],evHlx->x(s)-myX[0]);
    printf(" Y %g %g\n",myXX[1]-myX[1],evHlx->y(s)-myX[1]);
    printf(" Z %g %g\n",myXX[2]-myX[2],evHlx->z(s)-myX[2]);
    assert(diff<1.e-5);
  }
  return myHlx;		
}		
//______________________________________________________________________________
void StEventHelper::ls(Option_t* option) const
{
   typedef struct { int nb; int sz; const char *tenant; } QWE;
   QWE *qwe=0;

   TExMap map;
   TExMapIter  it(fMap); 
   Long_t key,val;
   while( it.Next(key,val) ) {
     if (val != 2) continue;
     StStrArray *a = (StStrArray *)key;
     Long_t &cnt = map((Long_t)a->IsA());
//     printf("%s %p\n",a->ClassName(),(void*)a);
     if (!cnt) {
       qwe = new QWE;
       cnt = (Long_t)qwe; 
       qwe->nb=0; qwe->sz=0;qwe->tenant=0;
     }
     qwe = (QWE*)cnt;
     qwe->nb++; qwe->sz += a->size();
     if (qwe->tenant==0 && a->size()) {
        TObject *to = a->front();
        if (to) qwe->tenant = to->ClassName();
     } 
 
   }
   TExMapIter  itt(&map);
   printf("\n      StEvent(%p)\n",(void*)fObject);

   while( itt.Next(key,val) ) {
     TObject *kl = (TObject *)key;
     qwe = (QWE*)val;
     printf ("%8d(%8d) - %s (%s)\n",qwe->nb,qwe->sz,kl->GetName(),qwe->tenant);
     delete qwe;
   }
   printf("\n");

}
//______________________________________________________________________________
TObjArray *StEventHelper::SelConts(const char *sel)
{
  TObjArray *tarr = new TObjArray;
  TRegexp reg(sel);

  TExMapIter  it(fMap); 
  Long_t key,val;
  while( it.Next(key,val) ) {
     if (val == 1) 	continue;
     StStrArray *a = (StStrArray *)key;
     if(a->size()==0)				continue;
     int n =0;
     if (reg.Index(a->ClassName(),&n)<0)	continue;   
     tarr->Add(a);
  }
  return tarr;   
}   
//______________________________________________________________________________
TObjArray *StEventHelper::SelTracks(const char*,int flag)
{
int trackTypes[]= {global, primary, tpt, secondary, estGlobal, estPrimary,-1};    

  TObjArray *conts = SelConts("^StSPtrVecTrackNode$");
  TObjArray *traks = new TObjArray();
  Int_t ilast = conts->GetLast();
  for (int idx=0;idx<=ilast;idx++) {
    StObjArray *arr = (StObjArray *)conts->At(idx);
    if (!arr)			continue;
    int ntrk = arr->size();
    if (!ntrk)			continue;
    for (int itrk=0;itrk<ntrk;itrk++) {
      StTrackNode *tn = (StTrackNode*)arr->at(itrk);
      if (!tn) 			continue;
      StTrack *trk = 0;int ity; int bty=kTGB;
      for (int jty=0;(ity=trackTypes[jty])>=0;jty++,bty<<=1){
        if (!(flag&bty))	continue;
        trk=tn->track(ity);
	if (!trk)		continue;
	if (trk->IsZombie()) 	break;
	traks->Add(trk);	break;
      }//end track types
    }//end StTrackNode's
  }// end  StSPtrVecTrackNode's        
  delete conts;
  return traks;
}
//______________________________________________________________________________
TObjArray *StEventHelper::SelHits(const char *RegEx, Int_t un)
{
//		un == used +2*nonused

  TObjArray *conts = SelConts(RegEx);
  TObjArray *hits = new TObjArray();
  Int_t ilast = conts->GetLast();
  
  for (int idx=0;idx<=ilast;idx++) {
    StObjArray *arr = (StObjArray *)conts->At(idx);
    if (!arr)		continue;
    int sz = arr->size();
    if (!sz)		continue;
    if (!arr->at(0)->InheritsFrom(StHit::Class())) continue;
    for(int ih=0;ih<sz; ih++) {
      StHit *hit = (StHit*)arr->at(ih);
      if (!hit) 	continue;
      int used = (hit->trackReferenceCount()!=0);
      int take = 0;
      if ( used && (un&kUSE)) take++;
      if (!used && (un&kUNU)) take++;
      if (take) hits->Add(hit);
    }
  }         
  delete conts;
  return hits;
}
//______________________________________________________________________________
TObjArray *StEventHelper::SelVertex(const char *sel,Int_t)
{
  
  TObjArray *conts = SelConts(sel);
  TObjArray *verts = new TObjArray();
  Int_t ilast = conts->GetLast();
  int nvtx =0;
  for (int idx=0;idx<=ilast;idx++) {
    StObjArray *arr = (StObjArray *)conts->At(idx);
    if (!arr)	continue;
    int sz = arr->size();
    if (!sz)	continue;
    for (int ivx=0; ivx<sz; ivx++) {
      StVertex *vx = (StVertex*)arr->at(ivx);
      if (!vx) 	continue;
      verts->Add(vx);
      nvtx++;
    }
  }
  delete conts;
  return verts;
}
//______________________________________________________________________________
TObjArray *StEventHelper::ExpandAndFilter(const TObject *eObj, int flag, TObjArray *out)
{
  // eobj - TObject of StEvent objects (StHit,StTrack,StVertex or TObjArray of above)
  if (!out) {out = new TObjArray;}
  TObject *eobj = (TObject*)eObj;
  
  int kind = Kind(eobj);
  if (kind&kHIT) {// input StHit
    if (!(flag&kHIT)) return out;
    int take=kind & (kUSE|kUNU|kFIT) &flag;
    if (take) out->Add(eobj);
    return out;
  }//endif  StHit

//-------------------------------------------------------------
  if (kind&kTRK) {// input StTrack
    if (flag&kTRK)  out->Add(eobj);
    if (!(flag&kHRR)) return out; 
    StTrack *trk = (StTrack*)eobj;
    StTrackHelper trkh(trk);
    out->Add((TObject*)trkh.GetHits());
    return out;
  }//endif StTrack

//-------------------------------------------------------------
  if (kind&kVTX) {// input StVertex
    if (flag&kVTX) out->Add(eobj);
    StVertex *vtx = (StVertex*)eobj;
    if (!(flag&(kTRK|kHRR))) return out;
    StVertexHelper  vtxh(vtx);
    int n = vtxh.GetNTracks();
    for (int i=-1;i<n;i++) {
      const TObject *to = vtxh.GetTrack(i);
      if (!to) continue;
      ExpandAndFilter(to,flag,out);
    }
    return out;
  }//endif StVertex
//-------------------------------------------------------------

  if (kind&kTRR) {  // input TObjArray
    TObjArray *inp = (TObjArray *)eobj;
    inp->Compress();
    int nbjs = inp->GetLast()+1;   
    if (!nbjs)	return 0;
    for (int i=0;i<nbjs;i++) {
      ExpandAndFilter(inp->At(i),flag,out);
    }
    return out;
  }// endif TObjArray

//-------------------------------------------------------------
  if (kind&kHRR) {  // input HitsArray
    if (!(flag&kHRR)) return out;
    out->Add(eobj);
    return out;
  }// endif HitsArray
  return 0;
}	
//______________________________________________________________________________
TObjArray *StEventHelper::MakePoints(TObjArray *inp, int flag)
{
static const Color_t plitra[]={kRed,kGreen,kBlue,kMagenta, kCyan};
static const int     nlitra  = sizeof(plitra)/sizeof(Color_t);
             int     ilitra=0;
  inp->Compress();
  int nbjs = inp->GetLast()+1;   
  if (!nbjs)	return 0;
  TObjArray *out = new TObjArray;out->SetOwner();
  StPoints3DABC  *p = 0;
  for (int i=0;i<nbjs;i++) {
    TObject *to = inp->At(i);
    int kind = Kind(to);
    if (!(kind&kHRR)) ilitra = (++ilitra)%nlitra;
    int take = (kind&flag);
    if (!take) 	continue;
    if (take&kHIT) take -=kHIT;
    if (!take) 	continue;

    p = 0;
    if      (kind&kHIT) p = new StHitPoints   ((StHit      *)to);
    else if (kind&kHRR) p = new StHitPoints   ((StPtrVecHit*)to);
    else if (kind&kTRK) p = new StTrackPoints ((StTrack    *)to);
    else if (kind&kVTX) p = new StVertexPoints((StVertex   *)to);
    if (!p) continue;
    p->SetUniqueID(plitra[ilitra]);
    out->Add(p);
  }// 

  return out;
}	



//______________________________________________________________________________
ClassImp(StPoints3DABC)
void StPoints3DABC::Add(StPoints3DABC *add)
{
  int n = add->fSize + fSize;
  if (n > fN) {
    if (n < fN*2) n = fN*2;
    Float_t *arr = new Float_t[n*3];
    memcpy(arr, fXYZ, fSize*3*sizeof(Float_t));
    delete [] fXYZ; fXYZ = arr; fN = n;
  }
  memcpy(fXYZ+fSize*3,add->fXYZ,add->fSize*3*sizeof(Float_t));
  fSize+=add->fSize;
}
//______________________________________________________________________________
ClassImp(StTrackPoints)
//______________________________________________________________________________
StTrackPoints::StTrackPoints(const StTrack *st,const char *name,const char *title)
:StPoints3DABC(name,title,st)
{
  Init();
}
//______________________________________________________________________________
void StTrackPoints::Init() 
{  
  if (fXYZ) return;
  float len = ((StTrack*)fObj)->length();   
  if (len <= 0.0001) {
    Warning("Init","Zero length %s(%p), IGNORED",fObj->ClassName(),(void*)fObj);
    MakeZombie();
    return;
  }
  
//  StTrackGeometry *geo = ((StTrack*)fObj)->geometry(); 
  StTrackGeometry *geo = ((StTrack*)fObj)->outerGeometry(); 
  Assert(geo);
  double curva = fabs(geo->curvature());
  double dip   = geo->dipAngle();
  fSize = abs(int(len*cos(dip)*curva*20))+2;   
  fN = fSize;
  fXYZ = new Float_t[fN*3];
  StPhysicalHelixD hel = geo->helix();
  Double_t step = len/(fSize-1);
  Double_t ss = 0;
  
//  for (int i =0;i<fSize;i++,ss+=step)
  for (int i =0;i<fSize;i++,ss-=step)
  {
     fXYZ[i*3+0] = hel.x(ss); 
     fXYZ[i*3+1] = hel.y(ss); 
     fXYZ[i*3+2] = hel.z(ss); 
  }
}
//______________________________________________________________________________
 Int_t StTrackPoints::DistancetoPrimitive(Int_t px, Int_t py)
{
//*-*-*-*-*-*-*Compute distance from POINT px,py to a 3-D points *-*-*-*-*-*-*
//*-*          =====================================================
//*-*
//*-*  Compute the closest distance of approach from POINT px,py to each SEGMENT
//*-*  of the polyline.
//*-*  Returns when the distance found is below DistanceMaximum.
//*-*  The distance is computed in pixels units.
//*-*
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

   enum {inaxis = 7,mindist=10};
   Float_t dist = 999999;

   Int_t puxmin = gPad->XtoAbsPixel(gPad->GetUxmin());
   Int_t puymin = gPad->YtoAbsPixel(gPad->GetUymin());
   Int_t puxmax = gPad->XtoAbsPixel(gPad->GetUxmax());
   Int_t puymax = gPad->YtoAbsPixel(gPad->GetUymax());

   TView *view = 0;
//*-*- return if POINT is not in the user area
   if (px < puxmin - inaxis) goto END;
   if (py > puymin + inaxis) goto END;
   if (px > puxmax + inaxis) goto END;
   if (py < puymax - inaxis) goto END;

   view = gPad->GetView();
   if (!view) 						goto END;
   
   {Int_t i;
   Float_t /*dpoint,*/alfa;
   Float_t xndc[3];
   Int_t x1,y1,x0,y0;
   Int_t pointSize = fN*3;
   view->WCtoNDC(fXYZ, xndc);
   x0 = gPad->XtoAbsPixel(xndc[0]);
   y0 = gPad->YtoAbsPixel(xndc[1]);

   float dif[2],difdif,cur[2],curcur,difcur;
   for (i=3;i<pointSize;i+=3) {
      view->WCtoNDC(fXYZ+i, xndc);
      x1     = gPad->XtoAbsPixel(xndc[0]);
      y1     = gPad->YtoAbsPixel(xndc[1]);
      dif[0] = x1-x0; dif[1]=y1-y0;
      cur[0] = x0-px; cur[1]=y0-py;
      difdif = (dif[0]*dif[0]+dif[1]*dif[1]);
      difcur = (dif[0]*cur[0]+dif[1]*cur[1]);
      curcur = cur[0]*cur[0]+cur[1]*cur[1];
      if (difdif<mindist*mindist) {
	if ((i+3)<pointSize) 				continue;
	dist = curcur; 					break;
      }
      alfa = -difcur/difdif;

      if (alfa<0.) {dist =  curcur; 			break;}

      x0=x1; y0=y1;
      if (alfa > 1.) {
	if (i+3 < pointSize) 				continue; 
        dist = (px-x1)*(px-x1) + (py-y1)*(py-y1);	break;
      }
      dist = curcur+alfa*(2*difcur+difdif*alfa);
       						      	break;
   }}
END:
   dist =  TMath::Sqrt(dist);
//VP   if (dist <= mindist) { dist = 0; gPad->SetSelected(fObj);}
   if (dist <= mindist) { dist = 0; gPad->SetSelected(this);}

   return Int_t(dist);
}

  
//______________________________________________________________________________
ClassImp(StVertexPoints)
//______________________________________________________________________________
StVertexPoints::StVertexPoints(const StVertex *sv,const char *name,const char *title)
:StPoints3DABC(name,title,sv)
{
  SetBit(1);
  fSize = 1; fN =1;
  fXYZ = new Float_t[3];
  fXYZ[0] = ((StVertex*)fObj)->position().x(); 
  fXYZ[1] = ((StVertex*)fObj)->position().y(); 
  fXYZ[2] = ((StVertex*)fObj)->position().z(); 
}
   
   
ClassImp(StHitPoints)
//______________________________________________________________________________
StHitPoints::StHitPoints(const StHit *sh,const char *name,const char *title)
:StPoints3DABC(name,title,sh)
{
  fSize = 1; fN =1;
  Init();
}
//______________________________________________________________________________
StHitPoints::StHitPoints(const StRefArray *ar,const char *name,const char *title)
:StPoints3DABC(name,title,ar)
{
  fSize = ar->size();
  fN = fSize;
  if (!fSize) return;
  fObj = (fSize==1) ? ar->front() : ar;
  Init();
}
//______________________________________________________________________________
void StHitPoints::Init() 
{  
  if (fXYZ) return;
  fXYZ = new Float_t[fN*3];
  
  for (int i =0;i<fSize;i++)
  {
     StHit *hit= (fSize==1) ? (StHit*)fObj: (StHit*)((StRefArray*)fObj)->at(i);
     StThreeVectorF v3 = hit->position();
     fXYZ[i*3+0] = v3.x(); 
     fXYZ[i*3+1] = v3.y(); 
     fXYZ[i*3+2] = v3.z(); 
  }
}
   
//______________________________________________________________________________
ClassImp(StFilterABC)

int StFilterABC::fgDial=0;
//______________________________________________________________________________
StFilterABC::StFilterABC(const char *name,bool active):TNamed(name,""),fActive(active)
{
#ifdef OLDDISPLAY
   char cbuf[200];
   sprintf(cbuf,"__StEventControlPanel__.AddFilter((TObject*)%p);",(void*)this);
   gROOT->ProcessLine(cbuf);
#endif
}
//______________________________________________________________________________
Int_t StFilterABC::Accept(StPoints3DABC *pnt, Color_t&, Size_t&, Style_t&)
{
  return Accept(pnt);
}
//______________________________________________________________________________
void StFilterABC::SetDefs()
{
  for (int i=0; GetNams()[i]; i++) {GetPars()[i]=GetDefs()[i];}
}
//______________________________________________________________________________
void   StFilterABC::Update()
{
#ifdef OLDDISPLAY
   char cbuf[200];
   float       *pars    = GetPars();
   const float *defs    = GetDefs();
   const char **namval  = GetNams();
   int flagg = 2001;
   if (!fgDial++) gROOT->LoadMacro("FilterDialog.C");
   sprintf(cbuf
  ,"new FilterDialog((char*)%p,(char**)%p,(float*)%p,(float*)%p,(int*)%p);"
                    ,(void*)GetName(),(void*)namval,(void*)defs,(void*)pars,(void*)&flagg);
   printf("%s\n",cbuf);
   void *dial = (void*)gROOT->ProcessLineFast(cbuf);
   printf("StFilterABC::Update() Waiting for update\n");
   while(flagg) {gSystem->DispatchOneEvent(1);}
   sprintf(cbuf,"delete ((FilterDialog*)%p);",(void*)dial);
   printf("StFilterABC::Update: %s\n",cbuf);
   gROOT->ProcessLine(cbuf);
   printf("StFilterABC::Update() update finished\n");
#endif
}
   
//______________________________________________________________________________
ClassImp(StFilterDef)
StFilterDef::StFilterDef(const char *name,bool active):StFilterABC(name,active)
{
  SetDefs();
  
}
//______________________________________________________________________________
const char  **StFilterDef::GetNams() const
{
  static const char *nams[] = {
   "  RandomSelect ",
   "  RxyMin       ",
   "  RxyMax       ",
   "  ZMin         ",
   "  ZMax         ",
   "  PhiMin       ",
   "  PhiMax       ",
   "  LenMin       ",
   "  LenMax       ",
   "  PtMin        ",
   "  PtMax        ",
   "  PseudoMin    ",
   "  PseudoMax    ",
   "  QMin         ",
   "  QMax         ", 
   "  EncodedMethod",
   0};
  return nams;
}
//______________________________________________________________________________
const float  *StFilterDef::GetDefs() const
{
  static const float defs[] = {
   /*  RandomSelect=*/    1.00,
   /*  RxyMin      =*/    0.00,
   /*  RxyMax      =*/  900.00,
   /*  ZMin        =*/ -900.00,
   /*  ZMax        =*/ +900.00,
   /*  PhiMin      =*/ -180.01,
   /*  PhiMax      =*/ +181.01,
   /*  LenMin      =*/   +0.00,
   /*  LenMax      =*/ +999.00,
   /*  PtMin       =*/    0.00,
   /*  PtMax       =*/  999.00,
   /*  PseudoMin   =*/ -999.00,
   /*  PseudoMax   =*/  999.00,
   /*  QMin        =*/   -1   ,
   /*  QMax        =*/   +1   ,
   /* Encoded method*/   -1   ,     // The default value -1 menas all

   0};
  return defs;   
}   

//______________________________________________________________________________
Int_t StFilterDef::Accept(StPoints3DABC *pnt,Color_t &color, Size_t&, Style_t&)
{
   static TRandom rrr;
   float x,y,z,r2xy,phid,len,pt,ps,q;
   const TObject *to;
   const StTrack *trk;
    // set default color for tracks
   color = (((color-kRed)+1)%6)+kRed;

   int cut = 1;
   if (fRandomSelect < 1. && fRandomSelect < rrr.Rndm())return 0;
 
   z = pnt->GetZ(0);				
   cut++;
   if (fZMin >z || z > fZMax)				goto SKIP;	

   x = pnt->GetX(0);
   y = pnt->GetY(0);
   r2xy = x*x+y*y;
   cut++;
   if (fRxyMin*fRxyMin > r2xy || r2xy > fRxyMax*fRxyMax)goto SKIP;
   phid = atan2(y,x)*(180./M_PI);
   cut++;
   if (fPhiMin > phid || phid > fPhiMax) 		goto SKIP;
   to = pnt->GetObject();
   if (!to) 						return 1;
   if (!to->InheritsFrom(StTrack::Class()))		return 1;

   // set default color for tracks
   // color = (((color-kRed)+1)%6)+kRed;

   trk = (StTrack*)to;
   len = trk->length();
   cut++;
   if (fLenMin >len || len > fLenMax)			goto SKIP;	
   pt = trk->geometry()->momentum().perp();
   cut++;
   if (fPtMin >pt || pt > fPtMax)			goto SKIP;	
   ps = trk->geometry()->momentum().pseudoRapidity();
   cut++;
   if (fPsMin >ps || ps > fPsMax)			goto SKIP;	
   q = trk->geometry()->charge();
   cut++;
   if (fQMin >q || q > fQMax)				goto SKIP;	
   cut++;
   if ( (int(fEncodedMethod) != -1) && (trk->encodedMethod() != int(fEncodedMethod)) )
      goto SKIP;
   return 1;   

SKIP: return 0;

}


//______________________________________________________________________________
ClassImp(StMuDstFilterHelper)
StMuDstFilterHelper::StMuDstFilterHelper(const char *name,bool active):StFilterABC(name,active)
{
  mBB = new BetheBloch();
  SetDefs();
  
}
//______________________________________________________________________________
StMuDstFilterHelper::~StMuDstFilterHelper()
{ delete mBB;}
//______________________________________________________________________________
const char  **StMuDstFilterHelper::GetNams() const
{
  static const char *nams[] = {
    " pCutHigh            ",  
    " nHitsCutHighP       ",
    " pCutLow             ",
    " nHitsCutLowP        ",    
    " chargeForLowP       ",
    " dEdxMassCutHigh     ",
    " dEdxFractionCutHigh ",
    " dEdxMassCutLow      ",
    " dEdxFractionCutLow  ",
    0
  };
  return nams;
}
//______________________________________________________________________________
const float  *StMuDstFilterHelper::GetDefs() const
{
  static const float defs[] = {
    /* pCutHigh            */ 2.0,    // high momentum cut for RICH/Upsilon candidates 
    /* nHitsCutHighP       */ 10,     // nHits cut for all tracks
    /* pCutLow             */ 0.2,    // low momentum cut
    /* nHitsCutLowP        */ 15,    
    /* chargeForLowP       */ -1,     // charge for tracks with pCutLow < p < pCutHigh, set to 0 for all tracks
    /* dEdxMassCutHigh     */ 0.939,  // cut below BetheBloch(p/dEdxMassCutHigh), e.g. proton-band
    /* dEdxFractionCutHigh */ 0.6,    // cut fraction of dEdx-band, i.e. dEdxFractionCut * BetheBloch(p/dEdxMassCut)
    /* dEdxMassCutLow      */ 0.494,  // cut above BetheBloch(p/dEdxMassCutLow), e.g. kaon-band
    /* dEdxFractionCutLow  */ 1.1,
    0
  };
  return defs;
}
//______________________________________________________________________________
Int_t StMuDstFilterHelper::Accept(const StTrack* track) {
  
  float pCutHigh        = fpCutHigh;    // high momentum cut for RICH/Upsilon candidates 
  int   nHitsCutHighP   = int(fnHitsCutHighP);     // nHits cut for all tracks

  // following cuts apply only for tracks with pCutLow < p <pHigh
  float pCutLow             = fpCutLow;            // low momentum cut
  int   nHitsCutLowP        = int(fnHitsCutLowP);    
  int   chargeForLowP       = int(fchargeForLowP); // charge for tracks with pCutLow < p < fpCutHigh, set to 0 for all tracks
  float dEdxMassCutHigh     = fdEdxMassCutHigh;    // cut below BetheBloch(p/dEdxMassCutHigh), e.g. proton-band
  float dEdxFractionCutHigh = fdEdxFractionCutHigh;// cut fraction of dEdx-band, i.e. dEdxFractionCut * BetheBloch(p/dEdxMassCut)
  float dEdxMassCutLow      = fdEdxMassCutLow;     // cut above BetheBloch(p/dEdxMassCutLow), e.g. kaon-band
  float dEdxFractionCutLow  = fdEdxFractionCutLow;

  int iret = 0;
  int chargeOK = 0;
  int dedxOK = 0;

  float magnitude = track->geometry()->momentum().magnitude();
  int   nPoints   = track->detectorInfo()->numberOfPoints();

  if  (   magnitude > pCutHigh && nPoints >= nHitsCutHighP)   iret = 1;
  else {
     if ( magnitude > pCutLow  && nPoints >= nHitsCutLowP ) 
     {
        // check charge
        if (chargeForLowP==0) 
           chargeOK = 1;
        else if (track->geometry()->charge() == chargeForLowP) 
           chargeOK = 1;

        // check dEdx
        //	      if (mBB==0) mBB = new BetheBloch();
        float dedxHigh = dEdxFractionCutHigh * mBB->Sirrf(magnitude/dEdxMassCutHigh);
        float dedxLow  = dEdxFractionCutLow  * mBB->Sirrf(magnitude/dEdxMassCutLow);
        float dedx     = 0;

        // get track dEdx
        const StSPtrVecTrackPidTraits& traits = track->pidTraits();
        StDedxPidTraits* dedxPidTr;
        for (unsigned int itrait = 0; itrait < traits.size(); itrait++){
           dedxPidTr = 0;
           if (traits[itrait]->detector() == kTpcId) {
              StTrackPidTraits* thisTrait = traits[itrait];
              dedxPidTr = dynamic_cast<StDedxPidTraits*>(thisTrait);
              if (dedxPidTr && dedxPidTr->method() == kTruncatedMeanId) {
                 // adjust L3 dE/dx by a factor of 2 to match offline
                 dedx = 2 * dedxPidTr->mean();
              }
           }
        }
        if (dedx > dedxHigh && dedx > dedxLow) 
           dedxOK = 1;
        // final answer
        iret = chargeOK * dedxOK;
     } // if (pCutLow && nHitsCutLowP)
  }
  return iret;
}

//______________________________________________________________________________
Int_t StMuDstFilterHelper::Accept(StPoints3DABC *pnt) 
{
   const TObject *to;
   const StTrack *trk;
   to = pnt->GetObject();
   if (!to) 						return 1;
   if (!to->InheritsFrom(StTrack::Class()))		return 1;
   trk = (StTrack*)to;
   return Accept(trk);
}

//______________________________________________________________________________
ClassImp(StColorFilterHelper)
StColorFilterHelper::StColorFilterHelper(const char *name,bool active):StFilterABC(name,active)
{
   fPidAlgorithm = new StTpcDedxPidAlgorithm();;
   fElectron     = StElectron::instance();
   fPion         = StPionPlus::instance();
   fKaon         = StKaonPlus::instance();
   fProton       = StProton::instance();

   SetDefs();
  
}
//______________________________________________________________________________
StColorFilterHelper::~StColorFilterHelper()
{ delete fPidAlgorithm;}
//______________________________________________________________________________
const char  **StColorFilterHelper::GetNams() const
{
  static const char *nams[] = {
    " Electron sigma ",  
    " Electron color ",
    " Pion sigma     ",  
    " Pion color     ",
    " Kaon sigma     ",  
    " Kaon color     ",
    " Proton sigma   ",  
    " Proton color   ",
    " others sigma   ",  
    " others color   ",
    0
  };
  return nams;
}
//______________________________________________________________________________
const float  *StColorFilterHelper::GetDefs() const
{
  static const float defs[] = {
    /* fNSigmaElectron*/ 1 ,   // nSigma cut for electron 
    /* fNColorElectron*/ 2 ,   // the color index for electron
    /* fNSigmaPion    */ 1 ,   // nSigma cut for electron
    /* fNColorPion    */ 3 ,   // the color index for pion
    /* fNSigmaKaon    */ 1 ,   // nSigma cut for pion
    /* fNColorKaon    */ 4 ,   // the color index for kaon 
    /* fNSigmaProton  */ 1 ,   // nSigma cut for kaon
    /* fNColorProton  */ 6 ,   // the color index kaon
    
    /* fNSigmaOther*/   -1,     // nSigma cut for other types
    /* fNColorOther*/    0,     // the color index for other types
    0
  };
  return defs;
}
//______________________________________________________________________________
Int_t StColorFilterHelper::Accept(const StTrack* track, Color_t &color, Size_t&size, Style_t&) {
  
float   sigmaElectron =  fNSigmaElectron ;         // nSigna cut for electron 
Color_t colorElectron = (Color_t)fNColorElectron ; // the color index for electron

float   sigmaPion     = fNSigmaPion ;              // nSigna cut for electron
Color_t colorPion     = (Color_t)fNColorPion ;     // the color index for pion

float   sigmaKaon     = fNSigmaKaon ;              // nSigna cut for pion
Color_t colorKaon     = (Color_t)fNColorKaon ;     // the color index for kaon 

float   sigmaProton   = fNSigmaProton ;            // nSigna cut for kaon
Color_t colorProton   = (Color_t)fNColorProton ;   // the color index kaon
    
// float   sigmaOther    = fNSigmaOther ;             // nSigna cut for other types
Color_t colorOther    = (Color_t)fNColorOther ;    // the color index for other types

// Fisyak's color schema

/* const StParticleDefinition* pd = */ track->pidTraits(*fPidAlgorithm);

  color = colorOther;
  size  = 1;

 if (TMath::Abs(fPidAlgorithm->numberOfSigma(fElectron)) < sigmaElectron) 
    { color = colorElectron; size = 2; }

 if (TMath::Abs(fPidAlgorithm->numberOfSigma(fKaon))     < sigmaKaon)
    { color = colorKaon; size = 4; }
 
 if (TMath::Abs(fPidAlgorithm->numberOfSigma(fPion))     < sigmaPion)
    { color = colorPion; size = 5; }
 
 if (TMath::Abs(fPidAlgorithm->numberOfSigma(fProton))   < sigmaProton)
    { color = colorProton; size = 3; }

  return 1;
}

//______________________________________________________________________________
Int_t StColorFilterHelper::Accept(StPoints3DABC *pnt, Color_t&color, Size_t&size, Style_t&style) 
{
   const TObject *to;
   const StTrack *trk;
   to = pnt->GetObject();
   if (!to) 						return 1;
   if (!to->InheritsFrom(StTrack::Class()))		return 1;
   trk = (StTrack*)to;
   return Accept(trk,color,size,style);
}
//______________________________________________________________________________
//______________________________________________________________________________
//______________________________________________________________________________
StVertexHelper::StVertexHelper(const StVertex *vtx)
{ SetVertex(vtx);} 
//______________________________________________________________________________
void StVertexHelper::SetVertex(const StVertex *vtx){fVtx = vtx;}    
int  StVertexHelper::GetType()               {return (int)fVtx->type();}
int  StVertexHelper::GetFlag()               {return fVtx->flag();};
int  StVertexHelper::GetNTracks()            {return fVtx->numberOfDaughters();}	
//______________________________________________________________________________
const StThreeVectorF &StVertexHelper::GetPoint()
{
  return fVtx->position();
}  
//______________________________________________________________________________   
const StTrack *StVertexHelper::GetTrack(int idx)  	// -1=parent track  
{
  if (idx==-1) return fVtx->parent();
  if (idx>= GetNTracks()) return 0;
  return fVtx->daughter((UInt_t)idx);
}
//______________________________________________________________________________
//______________________________________________________________________________
//______________________________________________________________________________
StTrackHelper::StTrackHelper(const StTrack *trk)
{ fHelx[0]=0; fHelx[1]=0; SetTrack(trk); }

StTrackHelper::~StTrackHelper(){  delete fHelx[0];delete fHelx[1]; }
void StTrackHelper::SetTrack(const StTrack *trk){fTrk=trk;fHits=0;GetNHits();}    
int  StTrackHelper::GetType()                 	{return fTrk->type();}
        int     StTrackHelper::GetFlag()      	{return fTrk->flag();}
        int     StTrackHelper::GetCharge()    	{return fTrk->geometry()->charge();}
const StVertex *StTrackHelper::GetParent()    	{return fTrk->vertex();}	 
      float     StTrackHelper::GetImpact()    	{return fTrk->impactParameter();}
      float     StTrackHelper::GetCurv()      	{return fTrk->geometry()->curvature();}
      float     StTrackHelper::GetLength()    	{return fTrk->length();}
const StThreeVectorF &StTrackHelper::GetFirstPoint(){return fTrk->geometry()->origin();}
const StThreeVectorF &StTrackHelper::GetLastPoint() {return fTrk->outerGeometry()->origin();}
const StThreeVectorF &StTrackHelper::GetMom()       {return fTrk->geometry()->momentum();}
//______________________________________________________________________________
StPhysicalHelixD *StTrackHelper::GetHelix(int idx)
{
  if (!fHelx[idx]) fHelx[idx]= new StPhysicalHelixD;
  *fHelx[idx] = (idx==0) ? fTrk->geometry()->helix():fTrk->outerGeometry()->helix();
  return fHelx[idx];
}
//______________________________________________________________________________
const StPtrVecHit *StTrackHelper::GetHits()
{
  if (fHits) 	return fHits;
  const StTrackDetectorInfo *tdi = fTrk->detectorInfo();
  if (!tdi)	return 0;
  fHits = &tdi->hits();
  		return fHits;
}
//______________________________________________________________________________
int StTrackHelper::GetNHits()
{ 
  if (fHits) return fHits->size(); 
  GetHits();
  return (fHits)? fHits->size():0; 
}
//______________________________________________________________________________
const StHit *StTrackHelper::GetHit(int idx)
{
  if (idx<0) 		return 0;
  if (idx>=GetNHits()) 	return 0;
  if (!fHits)          	return 0;
  return fHits->at(idx);
}
//______________________________________________________________________________
//______________________________________________________________________________
//______________________________________________________________________________
      StHitHelper::StHitHelper(const StHit *hit){fHit = hit;}
void  StHitHelper::SetHit(const StHit *hit)	{fHit = hit;}    
int   StHitHelper::GetDetId()			{return fHit->detector();}
int   StHitHelper::GetFlag() 			{return fHit->flag();}
float StHitHelper::GetCharge()			{return fHit->charge();}
int   StHitHelper::IsUsed()			{return fHit->trackReferenceCount();}
int   StHitHelper::IsFit()			{return fHit->usedInFit();}
const StThreeVectorF &StHitHelper::GetPoint()	{return fHit->position();}





