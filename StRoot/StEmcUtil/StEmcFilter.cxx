//******************************************************************************
//                                                                            
// StEmcFilter.h
//
// Authors: Alexandre Suaide & Marcia Maria de Moura
//
// Initial version: 2001/12/10
//
//******************************************************************************

#include "StEmcFilter.h"
#include "StMcEventTypes.hh"
#include "StEventTypes.h"
#include "StMcEvent.hh"
#include "StEvent.h"
#include <math.h>
#include "TFile.h"
#include "StTpcDedxPidAlgorithm.h"
#include "StEventUtilities/StuRefMult.hh"
#include "StEmcUtil/StEmcGeom.h"
#include "StEmcPosition.h"
#include "StarClassLibrary/SystemOfUnits.h"
#include "TString.h"
#ifndef ST_NO_NAMESPACES
using units::tesla;
#endif

ClassImp(StEmcFilter)

//------------------------------------------------------------------------------
StEmcFilter::StEmcFilter():TObject()
{
  
  mGeo[0] = StEmcGeom::getEmcGeom("bemc");
  mGeo[1] = StEmcGeom::getEmcGeom("bprs");
  mGeo[2] = StEmcGeom::getEmcGeom("bsmde");
  mGeo[3] = StEmcGeom::getEmcGeom("bsmdp");
  
  mPion=StPionPlus::instance();
  mProton=StProton::instance();
  mKaon=StKaonPlus::instance();
  mElectron=StElectron::instance();
    
  // event cuts
  mPrintLog=kFALSE;
  mEmcPresent=kTRUE;
  mHaveVertex=kTRUE;
  mHavePrimaries=kTRUE;
  mZVertexCut=20;
  mEmcETotalMin=0;
  mEmcETotalMax=100000;
  mMinMult=0;
  mMaxMult=100000;
  mBField=0.5;
  mNTriggerMask=0;
    
  // tracks cuts
  mDCACut=300000.0;
  mPtCut=0.0;
  mEtaMin=-10000.;
  mEtaMax=10000.;
  mFitPointsCut=0;
  mMustProjectEmc=kTRUE;
    
  // dE/dX cuts
  mdEdXScale=1.0;
  mPointsdEdX=0;
  mdEdXPMax=1.0;
  mdEdXCut=0.0;
  mdEdXNSigma=2.0;
  
  // V0 Vertex cuts
  mV0Pt = 0;
  mV0TrackProjectOnEmc = kTRUE;
  
  // EMC tower cuts
  mMaxTracksPerTower = 0;
  mEMin = 0;
  mEMax = 1000;
  mPtMin = 0;
  mPtMax = 1000;
  mPNeighbor = kTRUE;
  mSNeighbor = kFALSE;
  mTNeighbor = kFALSE;  
  
  // MC Tracks cuts
  mOnlyHadrons = kTRUE;
  mMcChargeType = kALL;
  mMcMustProjectEmc = kTRUE;
  mMcPtCut = 0.0;
  mMcEtaMin=-10000.;
  mMcEtaMax=10000.;
  
  mBemcRunning = NULL;
  mBprsRunning = NULL;
  mBsmdeRunning = NULL;
  mBsmdpRunning = NULL;
  
  mEmcPosition = new StEmcPosition();
  
}
//------------------------------------------------------------------------------
StEmcFilter::~StEmcFilter()
{
  delete mEmcPosition;
}
//------------------------------------------------------------------------------
Bool_t StEmcFilter::accept(StEvent* event)
{
  if(!event) 
  {
    msg("Event","Null pointer");
    return kFALSE;
  }
  
  if(mNTriggerMask!=0)
  {
    UInt_t trigger = event->triggerMask();
    Bool_t accept = kFALSE;
    for(UInt_t n = 0;n<mNTriggerMask;n++) if(mTriggerMask[n] == trigger) accept = kTRUE;
    if(!accept) 
    {
      msg("Event","Trigger Mask");
      return kFALSE;
    }
  }
  
  if(mHaveVertex)
  {
    StPrimaryVertex *vertex = event->primaryVertex();
    if(!vertex) 
    {
      msg("Event","Null vertex");
      return kFALSE;
    }
  
    StThreeVectorF v = vertex->position();
    Float_t vz=v.z();
    if(fabs(vz)>fabs(mZVertexCut)) 
    {
      msg("Event","ZVertexCut");
      cout <<"Vertex = "<<vz<<endl;
      return kFALSE;
    }
    
    if(mHavePrimaries)
    {
      StSPtrVecPrimaryTrack& tracks = vertex->daughters();
      if(tracks.size()==0) 
      {
        msg("Event","HavePrimaries");
        return kFALSE;
      }
    }
  }
  
  Float_t EventMultiplicity = uncorrectedNumberOfNegativePrimaries(*event);
  if(EventMultiplicity<mMinMult || EventMultiplicity>mMaxMult) 
  {
    msg("Event","Min/MaxMult");
    return kFALSE;
  }
  
  if(mEmcPresent)
  {
    StEmcCollection *emc=event->emcCollection();
    if(!emc) 
    {
      msg("Event","EmcPresent");
      return kFALSE;
    }
    Float_t emcETotal = getEmcETotal(event);
    if(emcETotal<mEmcETotalMin || emcETotal>mEmcETotalMax) 
    {
      msg("Event","EmcETotalMin/Max");
      return kFALSE;
    }
  }
  
  return kTRUE; 
}
//------------------------------------------------------------------------------
Float_t StEmcFilter::getEmcETotal(StEvent * event)
{
  StEmcCollection *emc=event->emcCollection();
  if(!emc) return 0;
  
  Float_t ETotal = 0;
  StDetectorId id = static_cast<StDetectorId>(0+kBarrelEmcTowerId); 
  StEmcDetector* emcDet = emc->detector(id) ;
  if(!emcDet) return 0;
  for(Int_t m=1;m<121;m++)
  {
    StEmcModule* module = emcDet->module(m);
    if(module)
    {
      StSPtrVecEmcRawHit& Hits = module->hits();
      if(Hits.size()>0)
        for(Int_t k=0;k<(Int_t)Hits.size();k++)
          ETotal+=Hits[k]->energy();
    }
  }
  return ETotal;
}
//------------------------------------------------------------------------------/
void StEmcFilter::initEmcTowers(StEvent *event)
{
  for(Int_t i=0;i<NTOWER;i++)
  {
    mPtTower[i]=0;
    mETower[i]=0;
    mNTracksTower[i]=0;
  }
  if(!event) return;
  
  StEmcCollection *emc=event->emcCollection();
  if(!emc) return;
  
  // filing emc hits
  StDetectorId id = static_cast<StDetectorId>(0+kBarrelEmcTowerId); 
  StEmcDetector* emcDet = emc->detector(id) ;
  if(!emcDet) return;
  for(Int_t m=1;m<121;m++)
  {
    StEmcModule* module = emcDet->module(m);
    if(module)
    {
      StSPtrVecEmcRawHit& Hits = module->hits();
      if(Hits.size()>0)
        for(Int_t k=0;k<(Int_t)Hits.size();k++)
        {
          Int_t m = Hits[k]->module();
          Int_t e = Hits[k]->eta();
          Int_t s = abs(Hits[k]->sub());
          Int_t rid;
          mGeo[0]->getId(m,e,s,rid);
          mETower[rid-1]=Hits[k]->energy();
        }
    }
  }
  
  //checking tracks
  StSPtrVecTrackNode& trackNodes = event->trackNodes();
  
  for (UInt_t i = 0; i < trackNodes.size(); i++)
  {    
    StTrack* track = trackNodes[i]->track(0);
    StThreeVectorD position, momentum;
    if (mEmcPosition->trackOnEmc(&position, &momentum, track, mBField,mGeo[0]->Radius()))
    {
      Float_t eta=position.pseudoRapidity();
      Float_t phi=position.phi();
      Int_t m,e,s;
      mGeo[0]->getBin(phi,eta,m,e,s);
      if(s==-1) s=1;
      if(m<1 || m>120) goto NEXT;
      if(s<1 || s>2  ) goto NEXT;
      if(e<1 || e>20 ) goto NEXT;
      Int_t rid;
      mGeo[0]->getId(m,e,s,rid);
      if(getEmcStatus(1,rid)==kBAD) goto NEXT;
      mNTracksTower[rid-1]++;
      mPtTower[rid-1]+=track->geometry()->momentum().perp();     
    }
    NEXT: continue;
  }
  return;
}
//------------------------------------------------------------------------------/
Bool_t StEmcFilter::accept(StTrack *track)
{
  if(!track) return kFALSE;
  
  StThreeVectorD p = track->geometry()->momentum();
  if(p.mag()==0) return kFALSE;

  if(p.perp()<mPtCut) return kFALSE;
  
  if(p.pseudoRapidity()<mEtaMin || p.pseudoRapidity()>mEtaMax) return kFALSE;
  if(track->fitTraits().numberOfFitPoints()<mFitPointsCut) return kFALSE;
  if(track->impactParameter()>mDCACut) return kFALSE;

  if(mMustProjectEmc) 
  {
    StThreeVectorD position, momentum;
    if (!mEmcPosition->trackOnEmc(&position, &momentum, track, mBField,mGeo[0]->Radius())) return kFALSE;
    
    //check if it hit a valid EMC tower
    Float_t eta=position.pseudoRapidity();
    Float_t phi=position.phi();
    Int_t m,e,s;
    mGeo[0]->getBin(phi,eta,m,e,s);
    if(s==-1) s=1;
    if(m<1 || m>120) return kFALSE;
    if(s<1 || s>2  ) return kFALSE;
    if(e<1 || e>20 ) return kFALSE;
    Int_t id;
    mGeo[0]->getId(m,e,s,id);
    if(getEmcStatus(1,id)==kBAD) return kFALSE;
  }
  
  return kTRUE; 

}
//------------------------------------------------------------------------------/
Bool_t StEmcFilter::accept(StMcEvent *event)
{
  if(!event) 
  {
    msg("McEvent","Null pointer");
    return kFALSE;
  }
  StMcVertex* vertex = event->primaryVertex();
  if(!vertex) 
  {
    msg("McEvent","Null vertex");
    return kFALSE;
  }
  
  StThreeVectorF position = vertex->position();
  
  if(fabs(position.z())>mZVertexCut) 
  {
    msg("McEvent","ZVertexCut");
    return kFALSE;
  }
  
  return kTRUE;
}
//------------------------------------------------------------------------------/
Bool_t StEmcFilter::accept(StV0Vertex *vertex)
{
  if(!vertex) return kFALSE;
  StThreeVectorF p = vertex->momentum();
  if(p.perp()<mV0Pt) return kFALSE;
  if(!mV0TrackProjectOnEmc) return kTRUE;
  
  UInt_t nd = vertex->numberOfDaughters();
  if(nd==0) return kFALSE;

  for(UInt_t i=0;i<nd;i++)
  {
    StTrack* track = vertex->daughter(i);
    if(track)
    {
      StThreeVectorD position, momentum;
      if (mEmcPosition->trackOnEmc(&position, &momentum, track, mBField,mGeo[0]->Radius()))
      {
        //check if it hit a valid EMC tower
        Float_t eta=position.pseudoRapidity();
        Float_t phi=position.phi();
        Int_t m,e,s;
        mGeo[0]->getBin(phi,eta,m,e,s);
        if(s==-1) s=1;
        if(m>=1 && m<=120) if(s>=1 && s<=2  ) if(e>=1 && e<=20 )
        {
          Int_t id;
          mGeo[0]->getId(m,e,s,id);
          if(getEmcStatus(1,id)==kGOOD) return kTRUE;
        }
      }
    }
  }
  return kFALSE;
}
//------------------------------------------------------------------------------/
Bool_t StEmcFilter::accept(StMcTrack *track)
{
  if(!track) return kFALSE;
  
  if(mOnlyHadrons)
  {
    Int_t geantId = (Int_t)track->geantId();
    if(geantId<8 || geantId>32) return kFALSE;
  }
  
  if(mMcChargeType != kALL)
  {
    Int_t charge = (Int_t)track->particleDefinition()->charge();
    Int_t signal = 0;
  
    if(charge!=0) signal = charge/abs(charge);
    
    if(signal == 0   && mMcChargeType != kNEUTRAL) return kFALSE;
    if(signal == -1  && (mMcChargeType != kCHARGED && mMcChargeType != kNEGATIVE)) return kFALSE;
    if(signal == +1  && (mMcChargeType != kCHARGED && mMcChargeType != kPOSITIVE)) return kFALSE;
  }
  
  StThreeVectorD p = track->momentum();
  if(p.mag()==0) return kFALSE;
  if(p.perp()<mMcPtCut) return kFALSE;
  if(p.pseudoRapidity()<mMcEtaMin || p.pseudoRapidity()>mMcEtaMax) return kFALSE;
    
  if(mMcMustProjectEmc)
  {
    // first check if there is a stop vertex
    StMcVertex *stop=track->stopVertex();
    if(stop) // check if the stop vertex is before EMC
    {
     StThreeVectorF po = stop->position(); 
     Float_t stopRadius = sqrt(po.x()*po.x()+po.y()*po.y());
     if(stopRadius<mGeo[0]->Radius()) return kFALSE; // track stopped before EMC. Not accepted
    }
    
    StThreeVectorD position, momentum;
    if (!mEmcPosition->trackOnEmc(&position, &momentum, track, mBField,mGeo[0]->Radius())) return kFALSE;
    
    //check if it hit a valid EMC tower
    Float_t eta=position.pseudoRapidity();
    Float_t phi=position.phi();
    Int_t m,e,s;
    mGeo[0]->getBin(phi,eta,m,e,s);
    if(s==-1) s=1;
    if(m<1 || m>120) return kFALSE;
    if(s<1 || s>2  ) return kFALSE;
    if(e<1 || e>20 ) return kFALSE;
    Int_t id;
    mGeo[0]->getId(m,e,s,id);
    if(getEmcStatus(1,id)==kBAD) return kFALSE;
  }
  return kTRUE; 
}
//------------------------------------------------------------------------------/
Bool_t StEmcFilter::accept(Int_t rid)
{
  if(rid<1 && rid>4800) return kFALSE;
  if(mNTracksTower[rid-1]>mMaxTracksPerTower) return kFALSE;
  if(mETower[rid-1]<mEMin || mETower[rid-1]>mEMax) return kFALSE;
  if(mPtTower[rid-1]<mPtMin || mPtTower[rid-1]>mPtMax) return kFALSE;
  Int_t size = 0;
  if(mTNeighbor) { size = 7; goto DOIT;}
  if(mSNeighbor) { size = 5; goto DOIT;}
  if(mPNeighbor) size = 3;
  DOIT:
  if(size==0) return kTRUE;
  Int_t half=size/2;
  Float_t eta,phi;
  mGeo[0]->getEtaPhi(rid,eta,phi);
  for(Int_t i = -half; i<= half; i++)
    for(Int_t j = -half; j<= half; j++)
    {
      Int_t rid1 = mEmcPosition->getNextTowerId(eta,phi,i,j);
      if(rid1>0) if(mNTracksTower[rid1-1]>0) return kFALSE;
    }
  return kTRUE;
}
//------------------------------------------------------------------------------/
Bool_t StEmcFilter::accept(Int_t m, Int_t e, Int_t s)
{
  Int_t rid;
  mGeo[0]->getId(m,e,s,rid);
  return accept(rid);
}
//------------------------------------------------------------------------------/
Int_t StEmcFilter::getNTracksTower(Int_t rid)
{
  if(rid<1 && rid>4800) return 0;
  return mNTracksTower[rid-1];
}
//------------------------------------------------------------------------------/
Int_t StEmcFilter::getNTracksTower(Int_t m, Int_t e, Int_t s)
{
  Int_t rid;
  mGeo[0]->getId(m,e,s,rid);
  return getNTracksTower(rid);
}
//------------------------------------------------------------------------------
/*!
\param track is the pointer to StTrack
\param mass is the mass of idetified track
\param id is the geant id of the identified track

To the present, only pions, kaons, protons and electrons are tested.
*/
Bool_t StEmcFilter::getTrackId(StTrack *track,Float_t& mass,Int_t& id)
{
 // dE/dx
  id=8;
  mass=mPion->mass();  
  
  if(!track) return kFALSE;
  
  double momentum  = fabs(track->geometry()->momentum().mag());
  if(momentum>mdEdXPMax) return kFALSE;

  StPtrVecTrackPidTraits traits = track->pidTraits(kTpcId);
  unsigned int size = traits.size();

  // default result (track id = pion)
  if(size==0) return kFALSE;  

  Float_t m[4];
  m[0] = mPion->mass();
  m[1] = mProton->mass();
  m[2] = mKaon->mass();
  m[3] = mElectron->mass();
  
  if (size>0)
  {
    StDedxPidTraits* pid;
    for (unsigned int i = 0; i < traits.size(); i++)
    {
      pid = dynamic_cast<StDedxPidTraits*>(traits[i]);
      if (pid) if(pid->method() == kTruncatedMeanId) break;
    }
    if(!pid) return kFALSE;

    double dEdX = (double)pid->mean();
    if(dEdX==0) return kFALSE;
    
    double npt = (double)pid->numberOfPoints();
       
    double dedx_expected;
    double dedx_resolution = (double)pid->errorOnMean();
    if(dedx_resolution<=0) dedx_resolution=npt > 0 ? 0.45/sqrt(npt) : 1000.;
    double z;
    Float_t nSigma[4];
            
    Int_t charge=track->geometry()->charge();
    
    for(Int_t i=0;i<4;i++)
    {
      dedx_expected=mBB(momentum/m[i])*mdEdXScale;
      z = log(dEdX/dedx_expected);
      nSigma[i]=fabs((Float_t) z/dedx_resolution) ;
    }
  
    Float_t SigmaOrder[4];
    Int_t type[4];
    for(Int_t i=0;i<4;i++)
    {
      SigmaOrder[i]=999999;
      type[i]=0;
      for(Int_t k=0;k<4;k++) 
      {
        if(nSigma[k]<SigmaOrder[i]) {SigmaOrder[i]=nSigma[k]; type[i]=k;}
      }
      nSigma[type[i]]=9999; 
    }
      
    if(SigmaOrder[0]<=mdEdXNSigma)
    {  
      if(type[0]==0 && charge>0 && dEdX>mdEdXCut) {mass=mPion->mass();   id = 8; return kTRUE;}
      if(type[0]==0 && charge<0 && dEdX>mdEdXCut) {mass=mPion->mass();   id = 9; return kTRUE;}
  
      if(type[0]==1 && charge>0 && dEdX>mdEdXCut) {mass=mProton->mass(); id = 14; return kTRUE;}
      if(type[0]==1 && charge<0 && dEdX>mdEdXCut) {mass=mProton->mass(); id = 15; return kTRUE;}
  
      if(type[0]==2 && charge>0 && dEdX>mdEdXCut) {mass=mKaon->mass();   id = 11; return kTRUE;}
      if(type[0]==2 && charge<0 && dEdX>mdEdXCut) {mass=mKaon->mass();   id = 12; return kTRUE;}

      if(type[0]==3 && charge>0 && dEdX>mdEdXCut) {mass=mElectron->mass();id = 2; return kTRUE;}
      if(type[0]==3 && charge<0 && dEdX>mdEdXCut) {mass=mElectron->mass();id = 3; return kTRUE;}
    }
   //cout <<"final id = "<<id<<endl;
   return kFALSE; 
  }
  return kFALSE;
}
//------------------------------------------------------------------------------
/*!
\param det is the detector number (1 = bemc, 2 = bprs, 3 = bsmde, 4 = bsmdp)
\param id is the software id of the tower/strip you would like to get the status

If no emcRunning or smdRunning table is set the default values are the 24 modules of 2001 run for towers only
*/
EmcStatus StEmcFilter::getEmcStatus(Int_t det, Int_t id)
{
  switch (det)
  {
    case 1: // bemc
      if(mBemcRunning)
      {
        emcRunning_st *st=mBemcRunning->GetTable();
        if(id<1 || id >4800) return kBAD;
        else 
        {
          Int_t status = (Int_t) st[0].IsRunning[id-1];
          if(status == 1) return kGOOD;
          if(status == 0) return kBAD;
          return kOTHER;
        }
      }
      else
      {
        if ((id >= 1 && id <= 340) || (id >= 1861 && id <= 2400) ) return kGOOD;
        else return kBAD;
      }
      break;
    case 2: // bprs
      if(mBprsRunning)
      {
        emcRunning_st *st=mBprsRunning->GetTable();
        if(id<1 || id >4800) return kBAD;
        else 
        {
          Int_t status = (Int_t) st[0].IsRunning[id-1];
          if(status == 1) return kGOOD;
          if(status == 0) return kBAD;
          return kOTHER;
        }
      }
      else return kBAD;
      break;
    case 3: // bsmde
      if(mBsmdeRunning)
      {
        smdRunning_st *st=mBsmdeRunning->GetTable();
        if(id<1 || id >18000) return kBAD;
        else 
        {
          Int_t status = (Int_t) st[0].IsRunning[id-1];
          if(status == 1) return kGOOD;
          if(status == 0) return kBAD;
          return kOTHER;
        }
      }
      else return kBAD;
      break;
    case 4: // bsmdp
      if(mBsmdpRunning)
      {
        smdRunning_st *st=mBsmdpRunning->GetTable();
        if(id<1 || id >18000) return kBAD;
        else 
        {
          Int_t status = (Int_t) st[0].IsRunning[id-1];
          if(status == 1) return kGOOD;
          if(status == 0) return kBAD;
          return kOTHER;
        }
      }
      else return kBAD;
      break;      
  }
  return kBAD;
}
//------------------------------------------------------------------------------
/*!
\param det is the detector number (1 = bemc, 2 = bprs, 3 = bsmde, 4 = bsmdp)
\param etabin is the etabin number
\param side is the EMC side (0 = west side, 1 = east side)
*/
Float_t StEmcFilter::getFraction(Int_t det,Int_t etabin,Int_t side)
{
  if(det<1 || det>4) return 0.;
  
  Float_t ntowers=0;
  Float_t TotalTowers=60*mGeo[det-1]->NSub(); //60 modules x  sub/module
  
  if(etabin<1 || etabin>mGeo[det-1]->NEta()) return 0.;
  
  Int_t mi=1,mf=60;
  if(side==1) {mi=61; mf=120;}
  
  for(Int_t m=mi;m<=mf;m++)
    for(Int_t s=1;s<=mGeo[det-1]->NSub();s++)
    {
      Int_t id;
      mGeo[det-1]->getId(m,etabin,s,id);
      if(getEmcStatus(det,id)==kGOOD) ntowers++;
    }
  
  return ntowers/TotalTowers;
}
//------------------------------------------------------------------------------
/*!
\param det is the detector number (1 = bemc, 2 = bprs, 3 = bsmde, 4 = bsmdp)
*/
Float_t StEmcFilter::getWestFraction(Int_t det)
{
  if(det<1 || det>4) return 0.;
  Int_t nEta = mGeo[det-1]->NEta();
  
  Float_t phiFr=0;
  for(Int_t i=1;i<=nEta;i++)
  {
    phiFr+=getFraction(det,i,0);
  }
  return phiFr/(Float_t)nEta;
}
//------------------------------------------------------------------------------
/*!
\param det is the detector number (1 = bemc, 2 = bprs, 3 = bsmde, 4 = bsmdp)
*/
Float_t StEmcFilter::getEastFraction(Int_t det)
{
  if(det<1 || det>4) return 0.;
  Int_t nEta = mGeo[det-1]->NEta();
  
  Float_t phiFr=0;
  for(Int_t i=1;i<=nEta;i++)
  {
    phiFr+=getFraction(det,i,1);
  }
  return phiFr/(Float_t)nEta;
}
//------------------------------------------------------------------------------
/*!
\param det is the detector number (1 = bemc, 2 = bprs, 3 = bsmde, 4 = bsmdp)
*/
Float_t StEmcFilter::getTotalFraction(Int_t det)
{
  if(det<1 || det>4) return 0.;
  Float_t WPhiFr=getWestFraction(det);
  Float_t EPhiFr=getEastFraction(det);
  
  return (WPhiFr+EPhiFr)/2.;
}
//------------------------------------------------------------------------------
void StEmcFilter::printCuts()
{
  TString TF[]={"kFALSE","kTRUE"};
  TString CH[]={"kNEGATIVE", "kNEUTRAL", "kPOSITIVE", "kCHARGED", "kALL"};
  cout <<"EMC Filter ---------------------------------------------------\n\n";
  cout <<"   1. Event Cuts \n";
  cout <<"      EmcPresent = "<<TF[(Int_t)mEmcPresent].Data()<<endl;
  cout <<"      HaveVertex = "<<TF[(Int_t)mHaveVertex].Data()<<endl;
  cout <<"      HavePrimaries = "<<TF[(Int_t)mHavePrimaries].Data()<<endl;
  cout <<"      ZVertexCut = "<<mZVertexCut<<" cm\n";
  cout <<"      EmcETotalMin = "<<mEmcETotalMin<<" GeV\n";
  cout <<"      EmcETotalMax = "<<mEmcETotalMax<<" GeV\n";
  cout <<"      MinMult = "<<mMinMult<<endl;
  cout <<"      MaxMult = "<<mMaxMult<<endl;
  cout <<"      BField = "<<mBField<<" Tesla \n";
  cout <<endl;
  cout <<"   2. Tracks cuts\n";
  cout <<"      DCACut = "<<mDCACut<<" cm\n";
  cout <<"      PtCut = "<<mPtCut<<" GeV/c\n";
  cout <<"      EtaMin = "<<mEtaMin<<endl;
  cout <<"      EtaMax = "<<mEtaMax<<endl;
  cout <<"      FitPointsCut = "<<mFitPointsCut<<endl;
  cout <<"      MusProjectEmc = "<<TF[(Int_t)mMustProjectEmc].Data()<<endl;
  cout <<endl;
  cout <<"   3. dE/dX cuts for StTrack Id\n";
  cout <<"      dEdXScale = "<<mdEdXScale<<endl;
  cout <<"      PointsdEdX = "<<mPointsdEdX<<endl;
  cout <<"      dEdXPMax = "<<mdEdXPMax<<" GeV/c\n";
  cout <<"      dEdXCut = "<<mdEdXCut<<" GeV/cm\n";
  cout <<"      dEdXNSigma = "<<mdEdXNSigma<<endl;
  cout <<endl;
  cout <<"   4. MC Tracks cuts\n";
  cout <<"      OnlyHadrons = "<<TF[(Int_t)mOnlyHadrons].Data()<<endl;
  cout <<"      McChargeType = "<<CH[(Int_t)mMcChargeType+1].Data()<<endl;
  cout <<"      McMustProjectEmc = "<<TF[(Int_t)mMcMustProjectEmc].Data()<<endl;
  cout <<"      McEtaMin = "<<mMcEtaMin<<endl;
  cout <<"      McEtaMac = "<<mMcEtaMax<<endl;
  cout <<"--------------------------------------------------------------\n";
  return;
}




