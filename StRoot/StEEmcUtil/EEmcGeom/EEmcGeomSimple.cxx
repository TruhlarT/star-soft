// $Id: EEmcGeomSimple.cxx,v 1.1 2003/01/16 19:33:50 zolnie Exp $
// $Log: EEmcGeomSimple.cxx,v $
// Revision 1.1  2003/01/16 19:33:50  zolnie
// added a simple Geom class to conver a track hit -> tower hit
//
#include <math.h>

#include "SystemOfUnits.h"
#include "StThreeVectorD.hh"
#include "StEmcRawHit.h"
#include "EEmcGeomSimple.h"


// ######################################################################
//         *** WARNING NOT TESTED FOR mClock==1 (clock-wise) ***
// ######################################################################




ClassImp(EEmcGeomSimple)


EEmcGeomSimple::EEmcGeomSimple() 
{
  InitDefaults();
}

EEmcGeomSimple::~EEmcGeomSimple() 
{
  if(mEtaBin) delete [] mEtaBin;
}


// counter-clockwise (mClock==-1)
//    12:  105deg ->   75deg
//     3:  195deg ->  165deg
//     6:  285deg ->  255deg
//     9:   15deg ->  345deg
void
EEmcGeomSimple::InitDefaults() 
{
  // default EtaBins
  const Float_t defaultEtaBin[] = {
    2.0    , 
    1.9008 , 1.8065 , 1.7168 , 1.6317 , 1.5507 , 1.4738 ,
    1.4007 , 1.3312 , 1.2651 , 1.2023 , 1.1427 , 1.086  ,
    0.0 
  };

  mNumSec  = kEEmcNumSectors;
  mNumSSec = kEEmcNumSubSectors;
  mNumEta  = kEEmcNumEtas;

  mEtaBin = new Float_t[mNumEta+1];
  for(int i=0;i<=mNumEta;i++) mEtaBin[i] = defaultEtaBin[i];

  mZ1     =  270.190*centimeter;
  mZ2     =  306.158*centimeter;
  mPhi0   =  75.0*degree;  //  
  mClock  = -1;

}

// =========================================================================
// gets a hit vector r checks if inside the EEMC
// and returns sector (1..12), subsector (1..5) and eta(1..mNumEta)
// =========================================================================
int 
EEmcGeomSimple::getHit(const StThreeVectorD& r,  StEmcRawHit &t)
{
  const double dPhiSec  = 2.0*M_PI/mNumSec;
  
  double  z   = r.z();
  double  eta = r.pseudoRapidity();
  double  phi = r.phi() - mPhi0;

  // check if inside the endcap
  if(z  <mZ1              || mZ2<z          ) return 0;
  if(eta<mEtaBin[mNumEta] || mEtaBin[0]<eta ) return 0;

  int teta = 0;
  for(teta=1;teta<=mNumEta;teta++) if(mEtaBin[teta]<eta) break;
  --teta; // step back

  // get the sector number
  int  k  = (mClock>0) ? (int) floor(phi/dPhiSec) : (int) ceil(phi/dPhiSec); 
  // adjust to 0..(mNumSec-1)
  int tsec    = (mNumSec + mClock*k)%mNumSec;

  // get the subsector
  int tsubsec = (int) ( ((k*dPhiSec - phi)/dPhiSec*mNumSSec) ) % mNumSSec ;
  
  t.setId(kEndcapEmcTowerId,tsec,teta,tsubsec);

  return 1;

}


