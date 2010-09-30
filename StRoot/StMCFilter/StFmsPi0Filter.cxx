// @(#)root/eg:$Id: StFmsPi0Filter.cxx,v 1.1 2010/09/30 20:05:10 jwebb Exp $
// Author: Victor Perev  17/03/2009

//______________________________________________________________________________
#include "stdlib.h"
#include "math.h"
#include "StFmsPi0Filter.h"
#include "StGenParticle.h"

/// 	IMPORTANT IMPORTANT IMPORTANT
/// Defining the static instance of user filter provides creating this
/// class during the loading of library. Afterward GEANT could select 
/// the needed filter by name. 
/// more info in http://www.star.bnl.gov/~perev/SIM/mcFilter.pdf
///
/// The libraries in loadlibs.kumac must be loaded prior to 
/// setting up the filter in the kumac.
///
/// See filt.kumac for details.

static StFmsPi0Filter fmsFilter;

/// StMCFilter base class is :
/// 1. A user interface. User must overload functions:
/// 	a)RejectEG (StGenParticles &) ? called inside Pythia. Interaction point
/// 	  in (0,0,0); EG == EventGenerator
/// 	b)RejectGT (StGenParticles &) ? called inside Geant before tracking.
/// 	  Interaction point generated by Geant; GT==GeantTracking
/// 	c)RejectGE (StGenParticles &) ? called inside Geant after tracking;
/// 	  GE==GeantEnd
/// 2. All three methods have exactly the same input arguments;
/// 3. User must provide the unique name of the his filter. Selection of filter is
///    based on this name.
/// 4. Apart of that in this base class all the machinery of connection to Pythia
///    and Geant is hidden
/// 5. At the end Finish() is called. Print statistics. Could be overloaded
/// 
/// An argument of RejectXX(StGenParticles &Ptl)
/// Class StGenParticles is a container class containing StGenParticle objects.
/// Each object represents one particle(track). User methods of StGenParticles
/// class:
/// 1. Ptl.Size() ? number of particles;
/// 2. Ptl(index) ? pointer to particle (StGenParticle*)
/// 3. Ptl.Print() ? print all particles;
/// 4. Ptl.Print(char* tit) ? print container
/// 
/// Class StGenParticle ideologically is based on HEPEVT standard
/// http://cepa.fnal.gov/psm/simulation/mcgen/lund/pythia_manual/pythia6.3/pythia6301/node39.html
/// 
/// Methods:
///   - int GetStatusCode; 			/// 1= final particle
///   - int GetPdgCode; 			//PDG particle code
///   - int GetGeaCode(); 			//Geant particle code
///   - StGenParticle *GetMother(int i); 	//mother particle(0=beam,1=target)
///   - StGenParticle *GetDaughter(int i); 	//daughter ith particle
///   - double GetCalcMass ();		//calculated mass
///   - double GetMass(); 			//mass
///   - int GetNDaughters
///   - void Momentum(double p4[4]); //four momentum
///   - void Vertex(double v[3]) //vertex in cm;
///   - double Time(); //time in cm
///   - int IsPrimary(); //Is this particle a primary one?
///   - int IsFinal () //Is this particle a final one?
/// 
/// Additional methods:
///   - double R (); //Rxy of vertex
///   - double Rho (); //Rxyz of vertex
///   - double P (); /// Full momentum
///   - double Pt (); //Transverse momentum
///   - double Energy();
///   - double Eta (); //Pseudo rapidity
///   - double Phi ();
///   - double Theta ();
/// 
///     		Filter kumac commands
/// 	gexec $STAR_LIB/geometry.so
/// 	gexec $STAR_LIB/libpythia_6410t.so
/// 	gexec $STAR_LIB/bpythia.so
/// 	gexec $STAR_LIB/StMCFilter.so
/// 	gfilter filterName
/// All three methods are called in a proper places. Method which is not
/// overloaded, always returns zero (no rejection)
/// 


StFmsPi0Filter::StFmsPi0Filter(): StMCFilter("fmsfilt")
{
  mEtaMin=2.8; mEtaMax=4.1; mPtMin=1.0;
  cout << "StFmsPi0Filter::StFmsPi0Filter   Setting Default parameters"<<endl;
  cout << "StFmsPi0Filter::StFmsPi0Filter   EtaMin="<<mEtaMin<<endl;
  cout << "StFmsPi0Filter::StFmsPi0Filter   EtaMax="<<mEtaMax<<endl;
  cout << "StFmsPi0Filter::StFmsPi0Filter   PtMin= "<<mPtMin<<endl;
};

//______________________________________________________________________________
int StFmsPi0Filter::RejectEG(const StGenParticleMaster &ptl) const
{
  //ptl.Print("************** In RejectEG ************** ");
  const StGenParticle *tk=0;
  int n = ptl.Size();
  int ntk=0;
  for (int i=0;i<n;i++) {
    tk = ptl(i); if (!tk) 	continue;
    if (tk->GetPdgCode()==111 &&
	tk->Eta() > mEtaMin   &&
        tk->Eta() < mEtaMax   &&
        tk->Pt()  > mPtMin    ){
      double p[4];
      tk->Momentum(p);
      printf("PI0!!! %3d St=%3d Pid=%5d Gid=%3d P=%7.2f %7.2f %7.2f %7.2f pt=%7.2f eta=%7.2f\n",
	     i,tk->GetStatusCode(),tk->GetPdgCode(),tk->GetGeaCode(),
	     p[0],p[1],p[2],p[3],tk->Pt(),tk->Eta()
	     );
      ntk++;
    }
  }  
  if (ntk==0) {return 1;}
  printf("Accepted/Total EG=%10d/%10d  GT=%10d/%10d  GE=%10d/%10d\n",
	   GetNTotEG()-1-GetNRejEG(),GetNTotEG(),
	   GetNTotGT()-GetNRejGT(),GetNTotGT(),
	   GetNTotGE()-GetNRejGE(),GetNTotGE());
  return 0;
}
//______________________________________________________________________________
int StFmsPi0Filter::RejectGT(const StGenParticleMaster &ptl) const
{
  //ptl.Print("************** In RejectGT ************** ");
  return 0;
}
//______________________________________________________________________________
int StFmsPi0Filter::RejectGE(const StGenParticleMaster &ptl) const
{
  //ptl.Print("************** In RejectGE ************** ");
  return 0;
}
//______________________________________________________________________________
void StFmsPi0Filter::ChangeConfig(string attr, float val)
{
  if (attr == "EtaMin"){
      cout << "StFmsPi0Filter::ChangeConfig()   Setting EtaMin to " << val << endl;
      mEtaMin = val;
  } else if (attr == "EtaMax"){
      cout << "StFmsPi0Filter::ChangeConfig()   Setting EtaMax to " << val << endl;
      mEtaMax = val;
  } else if (attr == "PtMin"){
      cout << "StFmsPi0Filter::ChangeConfig()   Setting PtMin to " << val << endl;
      mPtMin = val;
  } else {
      cout << "StFmsPi0Filter::ChangeConfig()   Unknown parameter " << attr << endl;
  }
}
