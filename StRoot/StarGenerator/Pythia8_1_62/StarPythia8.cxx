#include "StarPythia8.h"
ClassImp(StarPythia8);

#include "TDatabasePDG.h"
#include "TParticlePDG.h"

#include "StarGenerator/UTIL/StarRandom.h" 
#include "StarGenerator/EVENT/StarGenPPEvent.h"
#include "StarGenerator/EVENT/StarGenEPEvent.h"
#include "TString.h"
#include "TSystem.h"

// ----------------------------------------------------------------------------
// Remap pythia's random number generator to StarRandom
class PyRand : public Pythia8::RndmEngine {
public:
  Double_t flat() { return StarRandom::Instance().flat(); }
};
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
StarPythia8::StarPythia8(const Char_t *name) : StarGenerator(name)
{

  // Create the new instance of pythia, specifying the path to the
  // auxilliary files required by pythia. 
  // NOTE:  When adding new versions of Pythia8, we need to specify
  // the version of the code in the source code
  TString path = "StRoot/StarGenerator/"; path+=Pythia8::_version; path+="/xml/"; 
  { 
    ifstream in(path); 
    if (!in.good()) { path = "$(STAR)/"+path; }
    path = gSystem->ExpandPathName(path.Data());
  }
  

  Info(GetName(),Form("MC version is %s data at %s",Pythia8::_version,path.Data()));
  Info(GetName(),Form("Configuration files at %s",path.Data()));

  mPythia = new Pythia8::Pythia( path.Data() );
  mPythia -> setRndmEnginePtr( new PyRand() );

}
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
Int_t StarPythia8::Init()
{

  //
  // Remap pythia8 to pdg particles
  //
  map<TString,TString> particles;
  particles["electron"]="e-";
  particles["proton"]="proton";

  TString myBlue = particles[mBlue];     if ( myBlue == "" ) myBlue=mBlue;
  TString myYell = particles[mYell];     if ( myYell == "" ) myYell=mYell;

  //
  // Initialize pythia based on the frame and registered beam momenta
  // TODO: Switch to StarParticleDB
  //
  TDatabasePDG &pdg  = (*TDatabasePDG::Instance());
  TParticlePDG *blue = pdg.GetParticle(myBlue); assert(blue);
  TParticlePDG *yell = pdg.GetParticle(myYell); assert(yell);
  //
  if ( mFrame == "CMS"  ) InitCMS ( blue->PdgCode(), yell->PdgCode() );
  if ( mFrame == "FIXT" ) InitFIXT( blue->PdgCode(), yell->PdgCode() );
  if ( mFrame == "3MOM" ) Init3MOM( blue->PdgCode(), yell->PdgCode() );
  if ( mFrame == "4MOM" ) Init4MOM( blue->PdgCode(), yell->PdgCode() );
  if ( mFrame == "5MOM" ) Init5MOM( blue->PdgCode(), yell->PdgCode() );
  //
  // Setup event record based upon the beam species
  //
  if ( mBlue == "proton" )         mEvent = new StarGenPPEvent();
  else                             assert(0); // Pythia 8 does not (yet) support e+p collisions
  //
  // Make several particles stable which may cross the beam pipe,
  // and so the simulation package must be allowed to decide to
  // decay them or not.
  //
  Set("111:onMode=0"); // pi0 stable to permit mother/daughter in star record
  Set("211:onMode=0"); // pi+/- stable
  Set("221:onMode=0"); // eta stable
  Set("321:onMode=0"); // K+/- stable
  Set("310:onMode=0"); // K short
  Set("130:onMode=0"); // K long
  Set("3122:onMode=0"); // Lambda 0 
  Set("3112:onMode=0"); // Sigma -
  Set("3222:onMode=0"); // Sigma +
  Set("3212:onMode=0"); // Sigma 0
  Set("3312:onMode=0"); // Xi -
  Set("3322:onMode=0"); // Xi 0
  Set("3334:onMode=0"); // Omega -
  //
  return StMaker::Init();
  //
}
// ----------------------------------------------------------------------------
Int_t StarPythia8::Generate()
{
  
  //
  // Generate the event.  This is where the action happens.  The rest of this
  // method is just copying data from pythia into the event record.
  //
  mPythia -> next();

  //
  // Get the pythis event record
  //
  Pythia8::Event &event = mPythia->event;

  //
  // Get the number of particles in the event.  Pythia 8 include a "0th" entry,
  // which represents the system in the event record.  We will skip over this.
  //
  mNumberOfParticles = event.size() - 1;


  if ( mBlue == "proton" )          FillPP( mEvent );
  else                              FillEP( mEvent );

  // Loop over all particles in the event
  for ( Int_t idx=1; idx <= mNumberOfParticles; idx++ )
    {
      
      Int_t id        = event[idx].id();
      Int_t stat      = event.statusHepMC(idx);
      Int_t mother1   = event[idx].mother1();
      Int_t mother2   = event[idx].mother2();
      Int_t daughter1 = event[idx].daughter1();
      Int_t daughter2 = event[idx].daughter2();
      Double_t px     = event[idx].px();
      Double_t py     = event[idx].py();
      Double_t pz     = event[idx].pz();
      Double_t energy = event[idx].e();
      Double_t mass   = event[idx].m();
      Double_t vx     = event[idx].xProd(); // mm
      Double_t vy     = event[idx].yProd(); // mm
      Double_t vz     = event[idx].zProd(); // mm
      Double_t vt     = event[idx].tProd(); // mm/c

      mEvent -> AddParticle( stat, id, mother1, mother2, daughter1, daughter2, px, py, pz, energy, mass, vx, vy, vz, vt );

    }

  return kStOK;
}
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void StarPythia8::FillEP( StarGenEvent *myevent )
{
  //
  // Fill event-wise information
  //
  StarGenEPEvent *event = (StarGenEPEvent *)myevent;
  Pythia8::Info  &info  = mPythia->info;
  
  event -> idBlue     = info.idA();     // Beam particle
  event -> idYell     = info.idB();     // Beam particle
  event -> process    = info.code();
  event -> subprocess = (info.hasSub())? 0 : info.codeSub();

  Int_t id = info.id1();
  Double_t x = info.x1();
  Double_t xPdf = info.pdf1();
  Int_t valence = info.isValence1();
  if ( TMath::Abs(id)>6 )
    {
      id = info.id2();
      x  = info.x2();
      xPdf = info.pdf2();
      valence = info.isValence2();
    }
  
  event -> idParton   = id;
  event -> xParton    = x;
  event -> xPdf       = xPdf;

  event -> Q2         = info.Q2Fac();        // factorization scale
  event -> valence    = valence;
  
//   event -> sHat       = info.sHat();
//   event -> tHat       = info.tHat();
//   event -> uHat       = info.uHat();
//   event -> ptHat      = info.pTHat();
//   event -> thetaHat   = info.thetaHat();
//   event -> phiHat     = info.phiHat();

  event -> weight     = info.weight();

}
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void StarPythia8::FillPP( StarGenEvent *myevent )
{
  //
  // Fill event-wise information
  //
  StarGenPPEvent *event = (StarGenPPEvent *)myevent;
  Pythia8::Info  &info  = mPythia->info;

  event -> idBlue     = info.idA();     // Beam particle
  event -> idYell     = info.idB();     // Beam particle
  event -> process    = info.code();
  event -> subprocess = (info.hasSub())? 0 : info.codeSub();

  event -> idParton1  = info.id1();
  event -> idParton2  = info.id2();
  event -> xParton1   = info.x1();
  event -> xParton2   = info.x2();
  event -> xPdf1      = info.pdf1();
  event -> xPdf2      = info.pdf2();
  event -> Q2fac      = info.Q2Fac();        // factorization scale
  event -> Q2ren      = info.Q2Ren();        // renormalization scale
  event -> valence1   = info.isValence1();
  event -> valence2   = info.isValence2();
  
  event -> sHat       = info.sHat();
  event -> tHat       = info.tHat();
  event -> uHat       = info.uHat();
  event -> ptHat      = info.pTHat();
  event -> thetaHat   = info.thetaHat();
  event -> phiHat     = info.phiHat();

  event -> weight     = info.weight();

}
// ----------------------------------------------------------------------------
Int_t StarPythia8::InitCMS( Int_t blue, Int_t yell )
{
  mPythia->init( blue, yell, mRootS );
  return 0;
}
// ----------------------------------------------------------------------------
Int_t StarPythia8::InitFIXT( Int_t blue, Int_t yell )
{
  if ( mRootS > 0 ) 
    mPythia->init( blue, yell, mRootS, 0.0 );
  else
    mPythia->init( blue, yell, 0, mRootS );
      
  return 0;
}
// ----------------------------------------------------------------------------
Int_t StarPythia8::Init3MOM( Int_t blue, Int_t yell )
{

  cout << "Initializing 3MOM: " << endl;
  mBlueMomentum.Print();
  mYellMomentum.Print();


  mPythia -> init( blue, yell, 
		   mBlueMomentum.X(), mBlueMomentum.Y(), mBlueMomentum.Z(),
		   mYellMomentum.X(), mYellMomentum.Y(), mYellMomentum.Z() );
		   
  return 0;
}
// ----------------------------------------------------------------------------
Int_t StarPythia8::Init4MOM( Int_t blue, Int_t yell )
{
  return Init3MOM( blue, yell );
}
// ----------------------------------------------------------------------------
Int_t StarPythia8::Init5MOM( Int_t blue, Int_t yell )
{
  return Init3MOM( blue, yell );
}
// ----------------------------------------------------------------------------
