#include "StvDiver.h"
#include "TGeoManager.h"
#include "TGeoVolume.h"
#include "TVirtualMCStack.h"
#include "TGeant3TGeo.h"
#include "StarVMC/GeoTestMaker/StVMCApplication.h"
#include "StarVMC/GeoTestMaker/StMCStack.h"
#include "StarVMC/GeoTestMaker/StTGeoProxy.h"
#include "StvUtil/StvNodePars.h"
#include "StarMagField.h"
#include "StvUtil/StvELossTrak.h"
#include "THelixTrack.h"
#include "TRandom.h"

class MyRandom : public TRandom 
{
public:
virtual Double_t Rndm(Int_t i = 0) 				{return 0.5;}
virtual Double_t Gaus(Double_t mean = 0, Double_t sigma = 1)	{return 0.0;}
};
static MyRandom* gMyRandom=0;
static const double gMyPiMass=0.1396;
static const    int gMyPiPdg =9999;





static void mybreak(int key)
{ static int kto=-2010;
  if (kto != key) return;
  printf ("BOT OHO %d\n",key);
}

ClassImp(StvDiver)
//_____________________________________________________________________________
//_____________________________________________________________________________
const StvELossData StvDiver::GetELossData() const
{
 StvELossData eld;
 
  eld.mTheta2 = mELoss->GetTheta2();
  eld.mOrt2   = mELoss->GetOrt2();
  eld.mdPP    = mELoss->dPP();
  eld.mELoss  = mELoss->ELoss();
  eld.mdPPErr2= mELoss->dPPErr2();
  eld.mTotLen = mELoss->TotLen();
  eld.mP      = mELoss->P();
  eld.mM      = mELoss->M();
  eld.mMate   = (mELoss->GetNMats()==1)? mELoss->GetMate():0;
  
  return eld;
}
//_____________________________________________________________________________
StvDiver::StvDiver(const char *name):TNamed(name,"")
{
  memset(mBeg,0,mEnd-mBeg+1);
}
//_____________________________________________________________________________
int StvDiver::Init() 
{
  gMyRandom = new MyRandom;
  mHelix = new THelixTrack;
  mELoss = new StvELossTrak;
  StVMCApplication *app = (StVMCApplication*)TVirtualMCApplication::Instance();
  assert(app);
  mSteps =  ( StvMCStepping*)app->GetStepping();
  assert(mSteps);
  mSteps->Set(mHelix);
  mSteps->Set(mELoss);
  mGen = (StvMCPrimaryGenerator*)app->GetPrimaryGenerator();
  mFld = (StvMCField*           )app->GetField();
  mSteps->Set(mFld);
  
  TVirtualMC::GetMC()->DefineParticle( gMyPiPdg,"MyPi+",kPTHadron,gMyPiMass, 1,1e+10
	                             ,"pType", 0., 0, 1, 0, 1, 1, 1, 0, 1, 1);
  TVirtualMC::GetMC()->DefineParticle(-gMyPiPdg,"MyPi-",kPTHadron,gMyPiMass,-1,1e+10
	                             ,"pType", 0., 0, 1, 0, 1, 1, 1, 0, 1, 1);
  return 0;
}
//_____________________________________________________________________________
void StvDiver::SetRZmax(double rMax,double zMax) 
{   
  StVMCApplication *app = (StVMCApplication*)TVirtualMCApplication::Instance();
  app->SetRZmax(rMax,zMax);
}

//_____________________________________________________________________________
void StvDiver::Reset() 
{
 mSteps->Reset();
}
//_____________________________________________________________________________
void StvDiver::SetOpt(int opt)
{
 mSteps->SetOpt(opt);
}
//_____________________________________________________________________________
void StvDiver::SetTarget(const double target[3],int nTarget)
{
 mSteps->SetTarget(target,nTarget);
}
//_____________________________________________________________________________
int  StvDiver::Dive()
{
// ****************** Replacing ROOT random by empty one. Dangerous
// ****************** At the end of method it is returned back
  assert(gRandom != gMyRandom);
  TRandom *myRandom = gRandom;
  gRandom = gMyRandom;

  mFld->SetHz(mInpPars->_hz);	//Set initial value of mag field
  assert(fabs(mInpPars->_hz)<0.01);
  mELoss->Reset();
  int myExit = 0;
  mInpPars->get(mHelix);
  mInpErrs->Get(mHelix);
  mHlxDeri[0][0]=0;		//Mark this matrix is not filled
  if (!mDir) mHelix->Backward();

  while(1) {
    TVirtualMC::GetMC()->ProcessEvent();
    myExit = mSteps->GetExit();
    if (myExit==StvDiver::kDiveBreak) break;

    TVector3 pos = mSteps->CurrentPosition().Vect();
    TVector3 mom = mSteps->CurrentMomentum().Vect();
    mOutPars->_x = pos.X();
    mOutPars->_y = pos.Y();
    mOutPars->_z = pos.Z();
    mOutPars->_psi = mom.Phi();
    mOutPars->_ptin = -mSteps->Charge()/mom.Pt();
    mOutPars->_tanl = mom[2]*fabs(mOutPars->_ptin);
    mOutPars->_hz   = mFld->GetHz();
    mOutPars->ready(); 
    mOutErrs->Set(mHelix,mOutPars->_hz);
    assert(mOutErrs->mPP>0);
    mOutPars->convert(*mOutDeri,mHlxDeri);
    if (!mDir) {
      mOutPars->reverse();
      mOutDeri->Reverse();
      mOutErrs->Backward();
      assert(mOutErrs->mPP>0);
    }
    if (myExit !=StvDiver::kDiveMany) break;
    mHelix->Move(1.0);
  }
  assert (myExit >1 || mInpPars->_ptin * mOutPars->_ptin >=0);
  gRandom = myRandom;

  return mSteps->GetExit();
}
//_____________________________________________________________________________
void StvDiver::Set(const StvNodePars *inpar,const StvFitErrs *inerr,int idir)
{
  mInpPars= inpar;
  mInpErrs= inerr;
  mDir    = idir;
  mSteps->SetDir(mDir);
  mGen->Set(inpar,idir);
}
//_____________________________________________________________________________
void StvDiver::Set(StvNodePars *otpar,StvFitErrs *oterr,StvFitDers *deriv)
{
  mOutPars = otpar;
  mOutErrs = oterr;
  mOutDeri = deriv;
  mSteps->Set(&mHlxDeri);

}
//_____________________________________________________________________________
double StvDiver::GetLength() const
{
  return TVirtualMC::GetMC()->TrackLength();
}

//_____________________________________________________________________________
//_____________________________________________________________________________
ClassImp(StvMCInitApp)

//_____________________________________________________________________________
StvMCInitApp::StvMCInitApp()  
{}   
//_____________________________________________________________________________
int  StvMCInitApp::Fun()
{
  StVMCApplication  *app = (StVMCApplication*)TVirtualMCApplication::Instance();
  TVirtualMC *myMC  = new TGeant3TGeo("C++ Interface to Geant3"); 
  Info("Init","TGeant3TGeo has been created.");
  StvMCConstructGeometry *geo = new StvMCConstructGeometry(app->GetName());
  app->SetConstructGeometry(geo);
  app->SetPrimaryGenerator(new StvMCPrimaryGenerator());
  app->SetField(new StvMCField);
  StvMCStepping *steps =   new StvMCStepping("");
  app->SetStepping(steps);

  app->SetDebug(0);
  myMC->SetStack(new StMCStack(1));
  myMC->Init();
  myMC->BuildPhysics(); 
  ((TGeant3*)myMC)->SetDEBU(0,0,0); 
  ((TGeant3*)myMC)->SetMaxNStep(-1000);

  Gcphys_t* gcphys = ((TGeant3*)myMC)->Gcphys(); if (gcphys){}

  Info("Init","switch off physics");
  myMC->SetProcess("DCAY", 0);
  myMC->SetProcess("ANNI", 0);
  myMC->SetProcess("BREM", 0);
  myMC->SetProcess("COMP", 0);
  myMC->SetProcess("HADR", 0);
  myMC->SetProcess("MUNU", 0);
  myMC->SetProcess("PAIR", 0);
  myMC->SetProcess("PFIS", 0);
  myMC->SetProcess("PHOT", 0);
  myMC->SetProcess("RAYL", 0);
  myMC->SetProcess("LOSS", 4); // no fluctuations 
  //  myMC->SetProcess("LOSS 1"); // with delta electron above dcute
  myMC->SetProcess("DRAY", 0);
  myMC->SetProcess("MULS", 0);
  myMC->SetProcess("STRA", 0);
  myMC->SetCut("CUTGAM",	1e-3  );
  myMC->SetCut("CUTELE", 	1e-3  );
  myMC->SetCut("CUTHAD", 	.001  );
  myMC->SetCut("CUTNEU", 	.001  );
  myMC->SetCut("CUTMUO", 	.001  );
  myMC->SetCut("BCUTE", 	.001  );
  myMC->SetCut("BCUTM", 	.001  );
  myMC->SetCut("DCUTE", 	1e-3  );
  myMC->SetCut("DCUTM", 	.001  );
  myMC->SetCut("PPCUTM", 	.001  );
  myMC->SetCut("TOFMAX", 	50.e-6);

  return 0;
}
//_____________________________________________________________________________
//_____________________________________________________________________________
ClassImp(StvMCStepping)

//_____________________________________________________________________________
StvMCStepping::StvMCStepping(const char *name,const char *tit)
  : StMCStepping(name,tit)
{
  memset(fFist,0,fLast-fFist);
  fNTarget = 2;
}   
//_____________________________________________________________________________
StvMCStepping::~StvMCStepping()
{
}
//_____________________________________________________________________________
void StvMCStepping::Reset() 
{
  memset(fFist,0,fMidl-fFist);
  fNTarget = 2;
}		
//_____________________________________________________________________________
void StvMCStepping::SetTarget(const double *target,int nTarget) 
{
  memcpy(fTarget,target,sizeof(double)*nTarget);
  fNTarget = nTarget;
}		
//_____________________________________________________________________________
void StvMCStepping::SetOpt(int opt) 
{
  fOpt = opt;
  fNTarget = (fOpt&StvDiver::kTarg3D)? 3:2;
}		
//_____________________________________________________________________________
void StvMCStepping::Print(const Option_t*) const
{
}		
//_____________________________________________________________________________
int StvMCStepping::Fun()
{
static int nCall = 0;
nCall++;
static StTGeoProxy *tgh = StTGeoProxy::Instance();
int meAgain = 0;

mybreak(nCall);
  TString ts,modName;
  fKount++;
  Case();


  assert(fCurrentLength< 10000);
  assert(fEnterLength  < 10000);
  
//   StTGeoProxy::Instance()->Print(KazeAsString(fKaze));
//   printf("fEnterLength=%g fCurrentLength=%g Rxy=%g Z=%g\n\n"
//         , fEnterLength, fCurrentLength,fCurrentPosition.Perp(),fCurrentPosition.Z());
SWITCH: int myKaze = fKaze;
// printf("KASE=%d Pos(%g %g %g) In %s\n",fKaze
//       ,fCurrentPosition.X(),fCurrentPosition.Y(),fCurrentPosition.Z()
//       ,gGeoManager->GetPath());



if (GetDebug()) {printf("%d - ",nCall); Print();}
  switch (fKaze) {
    case kNEWtrack:;
         meAgain = (fPrevPath == tgh->GetPath());


    case kENTERtrack:;{
         double *X = &fCurrentPosition[0];
         fHitted = (tgh->IsHitted(X) && (!meAgain));
         if (strcmp(fVolume->GetName(),"HALL")==0) fKaze=kENDEDtrack;
         if (!StTGeoProxy::Inst()->GetHitShape()->Inside(fCurrentPosition.Z(),fCurrentPosition.Perp()))
	    fKaze=kENDEDtrack;
         if (fKaze==kENDEDtrack) break;
         if ((fExit = BegVolume())) fKaze=kENDEDtrack;}
    break;
    
    case kCONTINUEtrack:
    case kIgnore:
      if (IsDca00(2)) fKaze = kEXITtrack;
    break;
    
    case kOUTtrack:
    case kENDEDtrack:
      fExit=StvDiver::kDiveBreak;
      TVirtualMC::GetMC()->StopTrack();
      break;

    case kEXITtrack:
    {
      fExit = EndVolume();
      if (!fExit) break;
      fPrevPath ="";
      if (fExit == StvDiver::kDiveHits) fPrevPath = tgh->GetPath();
      TVirtualMC::GetMC()->StopTrack();
    }
    break;

    default:
     Error("Case","Unexpected case %x == %s",fCase,fCasName.Data());
     assert(0);
  }
  if (fKaze!=myKaze) 			goto SWITCH;
  if (fExit) 				return 0;
  if (fKaze!=fLastKaze) {fLastNumb=0; fLastKaze=fKaze; return 0;}
  fLastNumb++; if (fLastNumb<100)	return 0;
  fExit=StvDiver::kDiveMany; fLastNumb=0;
  TooMany();
//VP  TVirtualMC::GetMC()->StopTrack();
  return 0;
}		
//_____________________________________________________________________________
int StvMCStepping::BegVolume()
{
static int nCall=0; nCall++;

  fPrevMat = fMaterial;
  fELossTrak->Set(fMaterial,fEnterMomentum.Vect().Mag());
  fTooManyLength = fCurrentLength;
  return (IsDca00(0));
}
//_____________________________________________________________________________
int StvMCStepping::EndVolume()
{
static int nCall=0; nCall++;
  double pos[4]={0},mom[4]={0};

  int isDca = (IsDca00(1));
  if (isDca>=StvDiver::kDiveBreak) 	return isDca;
  fTooManyLength = fCurrentLength;
  double dL = fCurrentLength-fEnterLength;
  if (dL<1e-6) 				return isDca;
  fCurrentPosition.GetXYZT(pos);
  fCurrentMomentum.GetXYZT(mom);
  double pt = fCurrentMomentum.Pt();
  double nowRho = -fField->GetHz()/pt*fCharge;
  double wasRho =  fHelix->GetRho();
  assert(nowRho*wasRho> -1./(200*200));
  fELossTrak->Add(dL);

  if ((fOpt&StvDiver::kDoErrs)) { 	//Errors and derivatives requested
    fHelix->Set((2*wasRho+nowRho)/3);
    if (!(*fDeriv)[0][0]) {		//first time
      fHelix->Move(dL,*fDeriv);
    } else {
      StvHlxDers T,R;
      fHelix->Move(dL,T);
      Multiply(R,T,*fDeriv);
     *fDeriv=R;
    }
  }

  fHelix->Set(pos,mom,nowRho);
  return isDca;
}
//_____________________________________________________________________________
int StvMCStepping::IsDca00(int begEnd)
{
static int nCall=0; nCall++;
  fCurrentSign = 0;
  for (int itg = 0; itg<fNTarget; itg++) {
    fCurrentSign+=(fCurrentPosition[itg]-fTarget[itg])*fCurrentMomentum[itg];}

  switch (begEnd) {

    case 0: { // begin volume
      fStartSign = fCurrentSign; 
      if ((fCurrentSign<0)==(fDir==0)) return 0;
      return StvDiver::kDiveBreak;
    }

    case 1: { // end volume
      double dL = fCurrentLength-fEnterLength;
      if (dL<1e-6) 	return 0;		//Too small step, ignore it

      int ans = 0;
      if      ((fCurrentSign<0) != (fDir==0)          ) {//Over step DCA00 point?
        ans = StvDiver::kDiveDca;
	if ((fOpt&StvDiver::kTarg2D)==0) return ans;	
      }
      else if ((fOpt & StvDiver::kTargHit) && fHitted ) {//We are in hitted volume 
        ans = StvDiver::kDiveHits;
      }	
      else {return 0;}	//Nothing interesting(ni figa), get out
//
//		Now there are Hit or Dca cases
      THelixTrack th(*fHelix);
      double dcaL = (ans==StvDiver::kDiveDca)? th.Path(0.,0.) : dL/2;
      if (dcaL< 0) 	return StvDiver::kDiveBreak;		//Crazy case		
      double nowRho = -fField->GetHz()/fCurrentMomentum.Pt()*fCharge;
      double wasRho =  fHelix->GetRho();
      double delta = nowRho-wasRho;
      if (fabs(delta) > 1e-6*fabs(nowRho)) { // significant change of curvature
         th.Set((2*wasRho+nowRho)/3);
         if (ans==StvDiver::kDiveDca) dcaL = th.Path(0.,0.);
      }
  //		Update end position
      th.Move(dcaL);
      nowRho = (wasRho*(dL-dcaL)+nowRho*dcaL)/dL;

      fCurrentLength=fEnterLength+dcaL;
      fCurrentPosition.SetVect(TVector3(th.Pos()));
      double pt = fabs(fField->GetHz()*fCharge/nowRho);
      double p  = pt/th.GetCos();
      fCurrentMomentum.SetVectM(TVector3(th.Dir())*p,fMass);
      return ans;
    }
    case 2: { // continue volume
      if ((fCurrentSign<0) != (fDir==0)) return StvDiver::kDiveDca;
      return 0;
    }
  }
  return StvDiver::kDiveBreak;
}
//_____________________________________________________________________________
int StvMCStepping::TooMany()
{
  double dL = fCurrentLength-fTooManyLength;
  if (dL<1e-6) return 0;
  fEnterLength = fTooManyLength;
  EndVolume();
  return 0;
}

//_____________________________________________________________________________
//_____________________________________________________________________________
void StvMCStepping::Finish(const char *opt)
{
}
ClassImp(StvMCConstructGeometry)

//_____________________________________________________________________________
StvMCConstructGeometry::StvMCConstructGeometry(const char *gy)
  : GCall(gy,"StvMCConstructGeometry")
{
}   
//_____________________________________________________________________________
int  StvMCConstructGeometry::Fun()
{
  TVirtualMC *myMC = TVirtualMC::GetMC();
  myMC->SetRootGeometry();
  Info("Init","switch off physics");
  myMC->SetProcess("DCAY", 0);
  myMC->SetProcess("ANNI", 0);
  myMC->SetProcess("BREM", 0);
  myMC->SetProcess("COMP", 0);
  myMC->SetProcess("HADR", 0);
  myMC->SetProcess("MUNU", 0);
  myMC->SetProcess("PAIR", 0);
  myMC->SetProcess("PFIS", 0);
  myMC->SetProcess("PHOT", 0);
  myMC->SetProcess("RAYL", 0);
  myMC->SetProcess("LOSS", 4); // no fluctuations 
  //  myMC->SetProcess("LOSS 1"); // with delta electron above dcute
  myMC->SetProcess("DRAY", 0);
  myMC->SetProcess("MULS", 0);
  myMC->SetProcess("STRA", 0);
  myMC->SetCut("CUTGAM",	1e-3  );
  myMC->SetCut("CUTELE", 	1e-3  );
  myMC->SetCut("CUTHAD", 	.001  );
  myMC->SetCut("CUTNEU", 	.001  );
  myMC->SetCut("CUTMUO", 	.001  );
  myMC->SetCut("BCUTE", 	.001  );
  myMC->SetCut("BCUTM", 	.001  );
  myMC->SetCut("DCUTE", 	1e-3  );
  myMC->SetCut("DCUTM", 	.001  );
  myMC->SetCut("PPCUTM", 	.001  );
  myMC->SetCut("TOFMAX", 	50.e-6);
  


  return 0;
}
//_____________________________________________________________________________
//_____________________________________________________________________________
ClassImp(StvMCPrimaryGenerator);
//_____________________________________________________________________________
StvMCPrimaryGenerator::StvMCPrimaryGenerator()
{
 mPars=0;
 mDir=0; // direction of moving 1=along track; 0=opposite
}  

//_____________________________________________________________________________
int StvMCPrimaryGenerator::Fun() 
{     

 // Add one primary particle to the user stack (derived from TVirtualMCStack).
 // Track ID (filled by stack)
 // Option: to be tracked

 int toBeDone = 1; 
 
 // Particle type
 int pdg  = (mPars->getCharge()>0)? gMyPiPdg:-gMyPiPdg;
 // Particle momentum
 double p[3]={0};
 mPars->getMom(p);

 if (!mDir) { pdg = -pdg; p[0]=-p[0]; p[1]=-p[1];p[2]=-p[2];}
 
 // Polarization
static const double polx = 0.,poly = 0.,polz = 0.; 

 // Position
static  const double tof = 0.;
 
 double e  = sqrt(gMyPiMass*gMyPiMass + mPars->getP2());
 // Add particle to stack 
 assert(e>1e-6);
 int ntr=1;
 TVirtualMC::GetMC()->GetStack()->Clear();
 TVirtualMC::GetMC()->GetStack()->PushTrack(
  	 toBeDone,-1,pdg,p[0],  p[1],  p[2],e 
	,mPars->_x,  mPars->_y, mPars->_z,tof
        ,polx,poly,polz, kPPrimary, ntr, 1.,0);
 return 0;
}
//_____________________________________________________________________________
//_____________________________________________________________________________
ClassImp(StvMCField)
//_____________________________________________________________________________
StvMCField::StvMCField() 
{
  mHz = 3e33;
  mFild =  StarMagField::Instance();
}
//_____________________________________________________________________________
int StvMCField::FunDD(const double *x,double *b) 
{     
  if (!mFild) { mFild =  StarMagField::Instance();assert(mFild);}
static const Double_t EC = 2.99792458e-4;
  mFild->BField(x,b); 
  mHz = b[2]*EC;
  if (fabs(mHz) < 1e-5) mHz=1e-5;
  return 0;
}
  
  
