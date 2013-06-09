#include <string.h>
#include "TSystem.h"
#include "TBrowser.h"
#include "TCernLib.h"
#include "TVector3.h"
#include "StvDraw.h"
#include "Stv/StvTrack.h"
#include "Stv/StvNode.h"
#include "Stv/StvHit.h"
#include "StvUtil/StvNodePars.h"
#include "Stv/StvStl.h"
#include "THelixTrack.h"
#include "StarVMC/GeoTestMaker/StTGeoProxy.h"

#include "Stv/StvToolkit.h"
static Color_t gMyColors[] = {kRed,kBlue,kMagenta,kCyan};

StvDraw *StvDraw::fgStvDraw=0;
//_____________________________________________________________________________
//_____________________________________________________________________________
StvDraw::StvDraw(const char *name):StDraw3D(name)
{
 fgStvDraw = this; mNDoIt=0;mNPow2=1;mIColor=0;
 SetBkColor(kWhite);
}
//_____________________________________________________________________________
TObject *StvDraw::Hits(const std::vector<StvHit*> &hits, EDraw3DStyle sty)
{
const std::vector<const StvHit*>&vc = (std::vector<const StvHit*>&)hits;
return Hits(vc,sty);
}


//_____________________________________________________________________________
TObject *StvDraw::Hits(const std::vector<const StvHit*> &hits, EDraw3DStyle sty)
{
  int n = hits.size();
  std::vector<float> vec(n*3);
  const float *f;float *v=&vec[0];
  for (int i=0;i<n; i++) {
    const StvHit *h=hits[i];
    if (!h) continue;
    f = h->x();v[0]=f[0];v[1]=f[1];v[2]=f[2];v+=3;
  }
  vec.resize(v-&vec[0]);
  TObject *to = Points(vec,sty);
  DoIt();
//  ProcessEvents();
  return to;
}
//_____________________________________________________________________________
TObject *StvDraw::Hits(const std::vector<const float*> &hits, EDraw3DStyle sty)
{
  int n = hits.size();
  std::vector<float> vec(n*3);
  const float *f;float *v=&vec[0];
  for (int i=0;i<n; i++) {
    f = hits[i]; if(!f) continue; 
    v[0]=f[0];v[1]=f[1];v[2]=f[2];v+=3;
  }
  vec.resize(v-&vec[0]);
  return Points(vec,sty);
}
//_____________________________________________________________________________
TObject *StvDraw::Trak(const THelixTrack &helx,const std::vector<StvHit*>  &hits, EDraw3DStyle sty)
{
const std::vector<const StvHit*>&vc = (std::vector<const StvHit*>&)hits;
return Trak(helx,vc,sty);
}
//_____________________________________________________________________________
void StvDraw::Road(const THelixTrack &helx,const std::vector<const StvHit*> &hits
                  , EDraw3DStyle sty, double wide)
{
  int n = hits.size();
  if (!n) return;

  TVector3 A(hits.front()->x());
  TVector3 B(hits.back ()->x());
  StvConstHits unHits;
  Near(A,B,unHits,wide);
  Hits(unHits,kUnusedHit);
  Trak(helx,hits,sty);
}
//_____________________________________________________________________________
TObject *StvDraw::Trak(const THelixTrack &helx
                      ,const std::vector<const StvHit*>  &hits
		      ,EDraw3DStyle sty)
{
  int n = hits.size(); if (n<=1) return 0;
  Hits(hits  ,kUsedHit);
  if (helx.GetCos()<=0) {DoIt(); return 0;}

  const float *f = 0;
  f = hits.front()->x();
  double fst[3]={f[0],f[1],f[2]};
  f = hits.back()->x();
  double lst[3]={f[0],f[1],f[2]};

  std::vector<float> myTrak;  
  THelixTrack th(helx);

  double l = th.Path(fst); th.Move(l);
  l = th.Path(lst);
  double dl = l/100;
  for (int i=0;i<=100;i++) {
    const double *x = th.Pos(); 
    for (int j=0;j<3;j++) {myTrak.push_back(x[j]);} th.Move(dl);
  }
                Hits(hits  ,kUsedHit);
  TObject *to = Line(myTrak,sty);
  DoIt();
  return to;
}
//_____________________________________________________________________________
TObject *StvDraw::Trak(const std::vector<float> &pnts, EDraw3DStyle sty,Color_t color)
{
  int n = pnts.size(); if (!n) return 0;
  StDraw3DStyle myStyle = Style(sty);
  if (!color) {
    myStyle.Col() = gMyColors[mIColor];
    mIColor = (mIColor+1)%(sizeof(gMyColors)/sizeof(gMyColors[0]));
  }
  return Line(pnts, myStyle.Col(),myStyle.Sty(),myStyle.Siz() );
}
//_____________________________________________________________________________
void  StvDraw::Trak(const StvTrack *tk, int dir, EDraw3DStyle sty)
{
  StvConstHits myHits,ihHits;
  StvPoints  myPoits;
  const StvNode *lNode=0,*rNode;
  StvNodeConstIter itBeg,itEnd,it;

  if (dir) { //fit in ==> out
    itBeg = tk->begin();        itEnd = tk->end();
  } else   {//fit out ==> in
    itBeg = tk->end(); --itBeg; itEnd = tk->begin();--itEnd;
  }

//   StvNodeConstIter itBeg =(dir==0)? tk->rbegin():tk->begin();
//   StvNodeConstIter itEnd =(dir==0)? tk->rend()  :tk->end();
  
  for (it=itBeg; it!=itEnd; (dir)? ++it:--it) {//Main loop
    rNode = *it;
    if (rNode->mFE[dir].mHH<0) 			continue; 		//this node is not filled
    if (fabs(rNode->mFP[dir]._cosCA)<=0)  	continue;		//this node is not filled

    const StvHit  *hit  = rNode->GetHit();
    if (hit) {
      if (rNode->GetXi2(dir)<1000) {myHits+=hit;} else {ihHits+=hit;}}
      
    if (!lNode) { myPoits+=rNode->GetFP(dir).P;}
    else        { Join(lNode,rNode,myPoits,dir);}

    const double *P = rNode->GetFP(dir).P;
    if (hit)    {// make connection to hit
      const float  *H = hit->x();
      float con[6] = {H[0],H[1],H[2],P[0],P[1],P[2]};
      Line (2,con);            
    }  	
    {// only short line to mark node
       const double *D = &rNode->GetFP(dir)._cosCA;
       float con[6] = {P[0]         ,P[1]         ,P[2]
                     ,P[0]-D[1]*0.1,P[1]+D[0]*0.1,P[2]};
       Line (2,con);            
    }
    lNode = rNode;
  }
  Hits(myHits,kUsedHit);
  Hits(ihHits,kUnusedHit);
  Trak(myPoits,sty,0);

}
//_____________________________________________________________________________
void StvDraw::Zhow(const StvTrack *tk){Inst()->Road(tk,10);}
//_____________________________________________________________________________
void  StvDraw::Road(const StvTrack *tk, double wide, EDraw3DStyle sty)
{
  Trak(tk, sty);
  const StvNode *fist = tk->front();
  const StvNode *last = tk->back();
  const StvNodePars &parF = fist->GetFP();
  const StvNodePars &parL = last->GetFP();
  TVector3 myFst(parF.P);
  TVector3 myLst(parL.P);
  StvConstHits unHits;
  Near(myFst,myLst,unHits,wide);
  if (!unHits.size()) 			return;
  Hits(unHits,kUnusedHit);
}
//_____________________________________________________________________________
void StvDraw::Near(const TVector3 &A,const TVector3 &B,StvConstHits &hits,double wide)
{
 TVector3 D = B-A; 
 double len = D.Mag();D*=1./len;
 StVoidArr *vHits = StTGeoProxy::Inst()->GetAllHits();
  int nHits = vHits->size();
  hits.resize(0);
  for (int ih=0;ih<nHits;ih++) {//loop hit
    const StvHit *hit = (const StvHit*)(*vHits)[ih];
    TVector3 hi(hit->x()); 
    TVector3 hl = hi-A;
    double dot = hl.Dot(D);
    if (dot<-3*wide || dot >len+3*wide) continue;
    if ((hl.Cross(D)).Mag()>wide)	continue;
    hits.push_back(hit);
  } //End hit loop
}

//_____________________________________________________________________________
void StvDraw::Join(const StvNode *left,const StvNode *rite,StvPoints &poits,int dir)
{
static const double maxStep=0.1;
  const StvNodePars &lFP = left->GetFP(dir);
  const StvNodePars &rFP = rite->GetFP(dir);
  THelixTrack hLeft;
  lFP.get(&hLeft);
  double lenL =  hLeft.Path(rFP.P);

  int nStep = fabs(lenL)/maxStep; if (nStep <3) nStep = 3;
  double step = lenL/nStep;
  for (int is=0;is<=nStep;is++) {
    poits +=hLeft.Pos();
    hLeft.Move(step);
  }
}
//_____________________________________________________________________________
//_____________________________________________________________________________
void StvDraw::Show(const StvTrack *tk,int dir){Inst()->Trak(tk,dir);}
//_____________________________________________________________________________
void StvDraw::Klear(){Inst()->Clear();}
//_____________________________________________________________________________
void StvDraw::DoIt()
{
  mNDoIt++; if (mNDoIt<=mNPow2) return;
  mNPow2<<=1;
  UpdateModified(); ProcessEvents();
}
//_____________________________________________________________________________
void StvDraw::Clear(const char *)
{
  mNDoIt=0;  mNPow2=1;
  StDraw3D::Clear();
}
//_____________________________________________________________________________
int StvDraw::ProcessEvents()
{
  int ans = gSystem->ProcessEvents();
  return ans;
}
//_____________________________________________________________________________
void StvDraw::Wait()
{
    if (Jnst()) Jnst()->UpdateModified();
    fprintf(stderr,"StvDraw::Waiting...\n");
    while(!ProcessEvents()){gSystem->Sleep(200);}; 
}
//_____________________________________________________________________________
void StvDraw::KBrowse(const TObject *to)
{
  new TBrowser("StvDraw",(TObject*)to);
}
//_____________________________________________________________________________
void  StvDraw::All(const char *opt)
{
  if (!opt || !*opt) opt = "THh";

  if (strstr(opt,"T")) {
    StvTracks &tks = StvToolkit::Inst()->GetTracks();
    for (StvTrackConstIter it=tks.begin(); it!=tks.end(); ++it) {
      const StvTrack *tk = *it;
      Trak(tk);
  }  }

  if (strstr(opt,"h")) {
    StVoidArr *vHits = StTGeoProxy::Inst()->GetAllHits();  
    std::vector<const StvHit*> sHits;
    for (int ihit=0;ihit<(int)vHits->size();ihit++) {
      const StvHit *stvHit = (StvHit*)(*vHits)[ihit];
      if (stvHit->timesUsed()) continue;
      sHits.push_back(stvHit);
    }
    Hits(sHits,kUnusedHit);
  }  
}

