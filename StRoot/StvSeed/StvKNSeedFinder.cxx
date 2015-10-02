#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "TCernLib.h"
#include "TSystem.h"
#include "TVector3.h"
#include "StMultiKeyMap.h"
#include "THelixTrack.h"
#include "StarVMC/GeoTestMaker/StTGeoProxy.h"
#include "StvSeed/StvSeedConst.h"

#ifndef __NOSTV__
#include "StarVMC/GeoTestMaker/StTGeoProxy.h"
#include "StvKNSeedFinder.h"
#include "Stv/StvHit.h"
#include "Stv/StvNode.h"
#include "Stv/StvTrack.h"
#include "StvUtil/StvDebug.h"
#include "Stv/StvDraw.h"
#endif

#ifdef APPROX_DEBUG
#include "TCanvas.h"
#include "TH1F.h"
#include "TProfile.h"
#endif //APPROX_DEBUG
void myBreak(int);

#ifndef __NOSTV__
ClassImp(StvKNSeedFinder)
#endif

enum {kMinRxy = 50};


//_____________________________________________________________________________
StvKNSeedFinder::StvKNSeedFinder(const char *name):StvSeedFinder(name)
{
  memset(mBeg,0,mEnd-mBeg+1);
#ifndef KNNGONE
  fMultiHits	= new StMultiKeyMap(3);
#else
  fMultiHits	= new StMultiKeyMap(6);
#endif
  fMultiIter	= new StMultiKeyMapIter(0);
  f1stHitMap 	= new Stv1stHitMap;
  f1stHitMapIter= new Stv1stHitMapIter;
}  
//_____________________________________________________________________________
void StvKNSeedFinder::Clear(const char*)
{
  memset(mBeg,0,mMed-mBeg+1);
  f1stHitMap->clear();
  fMultiHits->Clear();
  *f1stHitMapIter = f1stHitMap->end();
  StvSeedFinder::Clear();
}
//_____________________________________________________________________________
void StvKNSeedFinder::Reset()
{
  memset(mBeg,0,mMed-mBeg+1);
#ifndef __NOSTV__
  assert(!f1stHitMap->size());
  const StVoidArr *hitArr =  StTGeoProxy::Inst()->GetSeedHits();
  int nHits =  hitArr->size();
  for (int iHit=0;iHit<nHits;iHit++) {
    StvHit *hit = (StvHit*)(*hitArr)[iHit];
    if (hit->isUsed()) continue;
    const float *x = hit->x();
    float r2 = x[0]*x[0] + x[1]*x[1] + x[2]*x[2];
    f1stHitMap->insert(std::pair<float,StvHit*>(-r2, hit));
//    fMultiHits->Add(hit,x);
    float xx[6]={x[0],x[1],x[2],x[0]-x[1],x[1]-x[2],x[2]-x[0]};
    fMultiHits->Add(hit,xx);
  }  

  fMultiHits->MakeTree();
  *f1stHitMapIter = f1stHitMap->begin();
#endif
}    
//_____________________________________________________________________________
int StvKNSeedFinder::Again(int)
{
  *f1stHitMapIter = f1stHitMap->begin();
   return 1;
}
//_____________________________________________________________________________
const THelixTrack* StvKNSeedFinder::NextSeed()
{
static int nCall=0; nCall++;
  int nTotHits=0,nAccHits=0;

  if (fstHit)  ++(*f1stHitMapIter); 	//Next seed if success
  for (;(*f1stHitMapIter)!=f1stHitMap->end();++(*f1stHitMapIter)) {//1st hit loop

    fstHit = (*(*f1stHitMapIter)).second;
    assert(fstHit);
    if (fstHit->isUsed()) 		continue;
    fSeedHits.clear();
    const float *fstPos = fstHit->x();
    float fstRxy2 = fstPos[0]*fstPos[0]+fstPos[1]*fstPos[1];
    float fstRxy = sqrt(fstRxy2);
    if (fstRxy < kMinRxy) 		continue;	//Non Tpc hit
//VP    const StHitPlane *hp = fstHit->detector();
    float        fstDir[2]={fstPos[0]/fstRxy,fstPos[1]/fstRxy};
    mRej.Reset(fstPos);
    mRej.Prepare();
    fMultiIter->Set(fMultiHits->GetTop(),mRej.mLim[0],mRej.mLim[1]);
    mSel.Reset(fstHit->x(),fstHit);
    nTotHits=0;nAccHits=0;

//		Add all near hits 
    for (StMultiKeyNode *node=0;(node = *(*fMultiIter)) ;++(*fMultiIter)) 
    { 
//		Search next hit 
      StvHit *nexHit = (StvHit*)node->GetObj();

      if (nexHit->isUsed()) 		continue;
      if (nexHit==fstHit)		continue;
      const float *f = nexHit->x();
      float myRxy2 = f[0]*f[0]+f[1]*f[1];
      if (myRxy2 >=fstRxy2)  		continue;
      float proj = fstDir[0]*f[0]+fstDir[1]*f[1];
      if (proj < kMinRxy) 		continue;

      nTotHits++;
      int ans = mRej.Reject(nexHit->x());
      if (ans) continue;
      nAccHits++;

      mSel.Add(nexHit->x(),nexHit);

    } //endMultiIter loop
    if (nAccHits<kMinHits) 	continue;

    int nHits = mSel.Select();
    if (nHits < kMinHits) 	continue;
    fSeedHits.clear();
    fSeedHits+=mSel.Get();
    const THelixTrack *hel =  Approx();
    if (hel)  return hel;	//Good boy
  }// end 1st hit loop
  return 0;
}
//_____________________________________________________________________________
const StvHits *StvKNSeedFinder::GetHits() const 	
{
     return (const StvHits*)(void*)(&(mSel.Get()));
}     
//_____________________________________________________________________________
void StvKNSeedFinder::Show()  	
{
     mSel.Show();
}     
//_____________________________________________________________________________
void StvKNSeedFinder::FeedBack(const StvTrack *tk)  	
{
#ifndef __NOSTV__
  StvSeedFinder::FeedBack(tk);
  if (!tk) return;
  const StvNode *node = tk->GetNode(StvTrack::kFirstPoint);
  double P[3];
  node->GetFP().getMom(P);
  
  double eta = TVector3(P).Eta();
  int nHits = tk->GetNHits(kPxlId);
  nHits    += tk->GetNHits(kIstId);
  nHits    += tk->GetNHits(kSstId);
  StvDebug::Count("GoodEta",eta);
  if (nHits>=2) StvDebug::Count("HftEta",eta);
#endif
}     
  
