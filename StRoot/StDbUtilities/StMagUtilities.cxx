/***********************************************************************
 *
 * $Id: StMagUtilities.cxx,v 1.28 2002/02/03 21:17:11 dunlop Exp $
 *
 * Author: Jim Thomas   11/1/2000
 *
 ***********************************************************************
 *
 * Description: Utilities for the Magnetic Field
 *
 ***********************************************************************
 *
 * $Log: StMagUtilities.cxx,v $
 * Revision 1.28  2002/02/03 21:17:11  dunlop
 * Fix the spacecharge instance, so that it gets called to
 * reset ONLY if the instance is non-zero, e.g. wanted.
 * (Previous log: call SpaceCharge::instance() every hit
 * to reset the DetectorDbMaker array.  Only works on 2nd+ event if you do this.)
 *
 * Revision 1.27  2002/02/03 20:59:47  dunlop
 * *** empty log message ***
 *
 * Revision 1.26  2002/02/02 02:05:30  jhthomas
 * Included gFactor explicitly in SpaceCharge call
 *
 * Revision 1.25  2002/02/02 01:01:09  jeromel
 * Jim's modif for FC & SpaceCharge corrections.
 *
 * Revision 1.23  2001/10/25 23:00:24  hardtke
 * Use database to get a few parameters in StMagUtilities (including twist)
 *
 * Revision 1.22  2001/10/06 06:14:06  jeromel
 * Sorry for multiple commits but ... added one more comment line.
 *
 * Revision 1.21  2001/10/05 20:19:38  dunlop
 * Made default BMap + Padrow13 + Twist + Clock.
 * Made selection logic symmetric
 *
 * Revision 1.20  2001/10/05 03:44:25  jeromel
 * Modifications by Jamie so we can turn on/off every corrections.
 *
 * Revision 1.18  2001/09/06 18:27:39  jeromel
 * Modifications for larger number of ExB options, forcing different configuration 9EB1 EB2 ...). Added loading of StTableUtilities when 'display' option is required.
 *
 * Revision 1.17  2001/08/08 20:11:42  jeromel
 * Added debugging lines for ExB correction option. WAS NEVER ON ==> Corrected & -> | (i.e. mea culpa)
 *
 * Revision 1.16  2001/08/01 18:34:39  jhthomas
 * Add temporary mode flag for year 2 running (different cathode potentials)
 *
 * Revision 1.15  2001/07/24 00:20:20  jhthomas
 * Protect Divide by Zero in UndoBDistortion
 *
 * Revision 1.14  2001/06/15 00:52:15  jhthomas
 * Protect discontinuity in distortions at CM
 *
 * Revision 1.13  2001/06/14 22:12:11  jhthomas
 * Speedup UndoBDistorion by adding table lookups
 *
 * Revision 1.12  2001/06/13 16:36:43  jhthomas
 * Improve the speed and timing of the PadRow13 correction.
 * Add 3D magnetic field functions so now both 2D and 3D are availble.
 *
 * Revision 1.3  2000/12/15 16:10:45  jhthomas
 * Add PadRow13, Clock, and Twist corrections to UndoDistortion
 *
 * Revision 1.2  2000/11/03 02:41:58  jhthomas
 * Added CVS comment structure to .h and .cxx files
 *
 ***********************************************************************/

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// StMagUtilities Class                                                 //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

/*!

\class StMagUtilities 

\author Jim Thomas 10 October 2000

A package of Bfield routines and distortion corrections for STAR.  
Methods included to read the correct Bfield map and scale it 
according to a scale factor provided during instantiation.
All corrections automatically adjust themselves for different
B field settings and E field settings.  Even reversed fields. 

<p>

An enumerated argument provided at the time of instantiation selects
a constant field (map=1) or the interpolation grid (map=2).
This code works in kGauss, cm - but note that the Bfield maps on disk 
are in gauss, cm.

<p>

To do:  <br>
- Finish pulling parameters out of DB rather than from #define. 
- Use Magnet current rather than MagFactor
- Add a routine to distort the track if we are given a Geant Vector full of points == a track
- Add simulated B field map in the regions where the field is not mapped.

*/

#include "StMagUtilities.h"
#include "TFile.h"
#include "StTpcDb/StTpcDb.h"
#include "tables/St_MagFactor_Table.h"
#include "StDetectorDbMaker/StDetectorDbSpaceCharge.h"
#include "StDetectorDbMaker/StDetectorDbMagnet.h"

static EBField  gMap  =  kUndefined ;   // Global flag to indicate static arrays are full
static Float_t  gFactor  = 1.0 ;        // Multiplicative factor (allows scaling and sign reversal)
static Float_t  gRescale = 1.0 ;        // Multiplicative factor (allows re-scaling wrt which map read)

//________________________________________


ClassImp(StMagUtilities)

/// StMagUtilities default constructor

StMagUtilities::StMagUtilities ()
  
{
  cout << "StMagUtilities:: Unfortunately, instantiation with StMagUtilities(<empty>) is obsolete" << endl ;
  cout << "StMagUtilities:: You must specify DataBase pointers or specify the requested Field settings manually" << endl ;
}


/// StMagUtilities constructor using the DataBase

StMagUtilities::StMagUtilities ( Int_t mode , StTpcDb* dbin , TDataSet* dbin2 )

{ 
  gMap = kMapped ;                    // Do once & Select the B field map (mapped field or constant)
  fSpaceCharge = StDetectorDbSpaceCharge::instance() ;  // Initialize the DB for SpaceCharge (EbyE)
  CommonStart( mode, dbin , dbin2 ) ; // Read the Magnetic and Electric Field Data Files, set constants
}


/// StMagUtilities constructor not using the DataBase

StMagUtilities::StMagUtilities ( const EBField map, const Float_t factor, Int_t mode = 0 )       

{ 
  gFactor = factor ;
  gMap = map ;                        // Do once & select the requested map (mapped or constant)
  fSpaceCharge = 0 ;                  // Do not get SpaceCharge out of the DB - use default in CommonStart
  CommonStart( mode, 0 , 0 ) ;        // Read the Magnetic and Electric Field Data Files, set constants
}

//________________________________________


void StMagUtilities::SetDb ( StTpcDb* dbin , TDataSet* dbin2 )
 
{
  thedb = dbin ;
  thedb2 = dbin2 ;
}


//________________________________________

/// Initialization method.  This will also sort the options received by the tpt Maker

void StMagUtilities::CommonStart ( Int_t mode, StTpcDb* dbin, TDataSet* dbin2 )

{

  Float_t  B[3], X[3] = { 0, 0, 0 } ;
  Float_t  OmegaTau ;           // For an electron, OmegaTau carries the sign opposite of B 

  // These items are available in the DB
  StarDriftV  =     5.45 ;      // Drift Velocity (cm/microSec) Magnitude
  TPC_Z0      =    209.3 ;      // Z location of STAR TPC Ground wire Plane (cm)
  XTWIST      =   -0.165 ;      // X Displacement of West end of TPC wrt magnet (mRad)
  YTWIST      =    0.219 ;      // Y Displacement of West end of TPC wrt magnet (mRad)
  SpaceCharge =      0.0 ;      // Space Charge parameter (uniform in the TPC - Coulombs/Epsilon-nought)
  // These items are not available in the DB but should be ... some day.
  IFCShift    =   0.0080 ;      // Shift of the IFC towards the West Endcap (cm) (2/1/2002)
  CathodeV    =  31000.0 ;      // Cathode Voltage (volts)
  GG          =   -127.5 ;      // Gating Grid voltage (volts)
  EASTCLOCKERROR =   0.0 ;      // Phi rotation of East end of TPC in milli-radians
  WESTCLOCKERROR = -0.43 ;      // Phi rotation of West end of TPC in milli-radians
  IFCRadius   =    47.45 ;      // Radius of the Inner Field Cage
  OFCRadius   =    200.0 ;      // Radius of the Outer Field Cage
  // End of list of items that might come from the DB

  SetDb( dbin, dbin2 ) ;

  if ( dbin != 0 )  // Initialize parameters to database values, if requested and where available
    { 
      // STAR Drift Velocity (cm/microSec) Magnitude
      StarDriftV  = 1e-6*thedb->DriftVelocity() ;        
      // Z location of STAR TPC Ground Plane (cm)
      TPC_Z0      = thedb->PadPlaneGeometry()->outerSectorPadPlaneZ()-thedb->WirePlaneGeometry()
	            ->outerSectorFrischGridPadPlaneSeparation() ;    
      // X Displacement of West end of TPC wrt magnet (mRad)
      XTWIST      = 1e3*thedb->GlobalPosition()->TpcRotationAroundGlobalAxisY() ; 
      // Y Displacement of West end of TPC wrt magnet (mRad)
      YTWIST      = -1e3*thedb->GlobalPosition()->TpcRotationAroundGlobalAxisX() ;            
      cout << "StMagUtilities::CommonSta  Using TPC parameters from DataBase. " << endl ; 
    }
  else
    {
      cout << "StMagUtilities::CommonSta  WARNING -- Using hard-wired TPC parameters. " << endl ; 
    }

  if ( dbin2 != 0 )  // Initialize the DB for the Magnetic Field and set the scale factor
    {
      St_MagFactor *fMagFactor = (St_MagFactor *) thedb2->Find("MagFactor"); assert(fMagFactor);
      gFactor = (*fMagFactor)[0].ScaleFactor;  // Set the magnetic field scale factor
    }
  else
    {
      cout << "StMagUtilities::CommonSta  WARNING -- Using manually selected BFIELD setting. " << endl ; 
    }

  if ( fSpaceCharge != 0 )  // Get SpaceCharge so it can be printed, below.
    {
      SpaceCharge = fSpaceCharge->getSpaceChargeCoulombs((double)gFactor) ; 
    }
  else
    {
      cout << "StMagUtilities::CommonSta  WARNING -- Using manually selected SpaceCharge setting. " << endl ; 
    }

  // Default behavior: no bits set gives you this default
  // To turn on and off individual distortions, set these higher bits

  mDistortionMode = mode;
  
  if ( !( mode & ( kBMap | kPadrow13 | kTwist | kClock | kMembrane | kEndcap | kIFCShift | kSpaceCharge ))) 
    {
      mDistortionMode |= kBMap;
      mDistortionMode |= kTwist;
      mDistortionMode |= kPadrow13;
      mDistortionMode |= kClock;
      printf("StMagUtilities::CommonSta  Default mode selection\n");
    } 
  else 
    {
      printf("StMagUtilities::CommonSta  Using mode option 0x%X\n",mode);
    }
 
  ReadField() ;                             // Read the Magnetic and Electric Field Data Files
  BField(X,B) ;                             // Work in kGauss, cm and assume Bz dominates

  // Mode = 0 is for Year 1 running, Mode = 1 is for year 2 running (different cathode potentials)
  // We reserved 3 bits for the option so we can extend up to 111=7 => 8 options (0 to 7)

  // Theoretically, OmegaTau is defined as shown in the next line.  
  // OmegaTau   =  -10. * B[2] * StarDriftV / StarMagE ;  // cm/microsec, Volts/cm
  // Instead, we will use scaled values from the Aleph collaboration

  StarMagE     =  TMath::Abs(CathodeV/TPC_Z0) ;           // STAR Electric Field (V/cm) Magnitude

  if ( !(mode & kElectricField2001) ){
    OmegaTau   =  -11.0 * B[2] * StarDriftV / StarMagE ;  // B in kGauss, note the sign of B is important 
  } else {
    OmegaTau   =  -12.4 * B[2] * StarDriftV / StarMagE ;  // B in kGauss, note the sign of B is important 
  }

  Const_0    =  1. / ( 1. + pow( OmegaTau, 2 ) ) ;
  Const_1    =  OmegaTau / ( 1. + pow( OmegaTau, 2 ) ) ;
  Const_2    =  pow( OmegaTau, 2 ) / ( 1. + pow( OmegaTau, 2 ) ) ;

  cout << "StMagUtilities::OmegaTau   =  " << OmegaTau << endl ; 
  cout << "StMagUtilities::XTWIST     =  " << XTWIST << " mrad" << endl ;
  cout << "StMagUtilities::YTWIST     =  " << YTWIST << " mrad" << endl ;
  cout << "StMagUtilities::SpaceCharg =  " << SpaceCharge << " Coulombs/epsilon-nought" << endl ;
  cout << "StMagUtilities::IFCShift =  " << IFCShift << " cm" << endl ;


}



//________________________________________


/// B field in Cartesian coordinates - 2D field (ie. Phi symmetric)

void StMagUtilities::BField( const Float_t x[], Float_t B[] )

{                          

  Float_t r, z, Br_value, Bz_value ;

  z  = x[2] ;
  r  = TMath::Sqrt( x[0]*x[0] + x[1]*x[1] ) ;
  
  if ( r != 0.0 )
    {
      Interpolate2DBfield( r, z, Br_value, Bz_value ) ;
      B[0] = Br_value * (x[0]/r) ;
      B[1] = Br_value * (x[1]/r) ;
      B[2] = Bz_value ; 
    }
  else
    {
      Interpolate2DBfield( r, z, Br_value, Bz_value ) ;
      B[0] = Br_value ;
      B[1] = 0.0 ;
      B[2] = Bz_value ;
    }

}


/// Bfield in Cartesian coordinates - 3D field
 
void StMagUtilities::B3DField( const Float_t x[], Float_t B[] )

{                          

  Float_t r, z, phi, Br_value, Bz_value, Bphi_value ;

  z  = x[2] ;
  r  = TMath::Sqrt( x[0]*x[0] + x[1]*x[1] ) ;
  
  if ( r != 0.0 )
    {
      phi = TMath::ATan2( x[1], x[0] ) ;
      if ( phi < 0 ) phi += 2*TMath::Pi() ;             // Table uses phi from 0 to 2*Pi
      Interpolate3DBfield( r, z, phi, Br_value, Bz_value, Bphi_value ) ;
      B[0] = Br_value * (x[0]/r) - Bphi_value * (x[1]/r) ;
      B[1] = Br_value * (x[1]/r) + Bphi_value * (x[0]/r) ;
      B[2] = Bz_value ; 
    }
  else
    {
      phi = 0 ;
      Interpolate3DBfield( r, z, phi, Br_value, Bz_value, Bphi_value ) ;
      B[0] = Br_value ;
      B[1] = Bphi_value ;
      B[2] = Bz_value ;
    }

  return ;

}


/// B field in Radial coordinates - 2D field (ie Phi symmetric)

void StMagUtilities::BrBzField( const Float_t r, const Float_t z, Float_t &Br_value, Float_t &Bz_value )

{
  
  Interpolate2DBfield( r, z, Br_value, Bz_value ) ;

}


/// B field in Radial coordinates - 3D field

void StMagUtilities::BrBz3DField( const Float_t r, const Float_t z, const Float_t phi, 
				  Float_t &Br_value, Float_t &Bz_value, Float_t &Bphi_value )

{

  Float_t phiprime ;
  phiprime = phi ;
  if ( phiprime < 0 ) phiprime += 2*TMath::Pi() ;             // Table uses phi from 0 to 2*Pi
  Interpolate3DBfield( r, z, phiprime, Br_value, Bz_value, Bphi_value ) ;

}


//________________________________________


/// Main Entry Point for requests to UNDO the E and B field distortions

void StMagUtilities::UndoDistortion( const Float_t x[], Float_t Xprime[] )

{
  // Control by flags JCD Oct 4, 2001
  Float_t Xprime1[3], Xprime2[3] ;

  // Set it up
  for (unsigned int i=0; i<3; ++i) {
      Xprime1[i] = x[i];
  }

  Float_t r2 = x[0]*x[0] + x[1]*x[1] ;   // Point must be inside TPC to be suffer distortions, check this.
  if ( r2 >= OFCRadius*OFCRadius || r2 <= IFCRadius*IFCRadius || x[2] >= TPC_Z0 || x[2] <= -1*TPC_Z0 )
    {
      for (unsigned int i=0; i<3; ++i) { Xprime[i] = x[i] ; }
      return ;
    }
      
  if (mDistortionMode & kBMap) {
      FastUndoBDistortion    ( Xprime1, Xprime2 ) ;
      for (unsigned int i=0; i<3; ++i) {
	  Xprime1[i] = Xprime2[i];
      }
  }

  if (mDistortionMode & kPadrow13) {
      UndoPad13Distortion    ( Xprime1, Xprime2 ) ;
      for (unsigned int i=0; i<3; ++i) {
	  Xprime1[i] = Xprime2[i];
      }
  }
  
  if (mDistortionMode & kTwist) {

      UndoTwistDistortion    ( Xprime1, Xprime2 ) ;
      for (unsigned int i=0; i<3; ++i) {
	  Xprime1[i] = Xprime2[i];
      }
  }

  if (mDistortionMode & kClock) {
      
      UndoClockDistortion    ( Xprime1, Xprime2 ) ; 
      for (unsigned int i=0; i<3; ++i) {
	  Xprime1[i] = Xprime2[i];
      }
  }

  if (mDistortionMode & kMembrane) {
      
      UndoMembraneDistortion ( Xprime1, Xprime2 ) ;
      for (unsigned int i=0; i<3; ++i) {
	  Xprime1[i] = Xprime2[i];
      }

  }

  if (mDistortionMode & kEndcap) { 
      UndoEndcapDistortion ( Xprime1, Xprime2 ) ;
      for (unsigned int i=0; i<3; ++i) {
	  Xprime1[i] = Xprime2[i];
      }
  }

  if (mDistortionMode & kIFCShift) { 
      UndoIFCShiftDistortion ( Xprime1, Xprime2 ) ;
      for (unsigned int i=0; i<3; ++i) {
	  Xprime1[i] = Xprime2[i];
      }
  }

  if (mDistortionMode & kSpaceCharge) { 
      UndoSpaceChargeDistortion ( Xprime1, Xprime2 ) ;
      for (unsigned int i=0; i<3; ++i) {
	  Xprime1[i] = Xprime2[i];
      }
  }

  // Return it

  for (unsigned int i=0; i<3; ++i) {
      Xprime[i] = Xprime1[i];
  }
  
}


//________________________________________


/// Main Entry Point for requests to DO the E and B field distortions (for simulations)

void StMagUtilities::DoDistortion( const Float_t x[], Float_t Xprime[] )

{

  UndoDistortion ( x, Xprime ) ;

  Xprime[0] = 2*x[0] - Xprime[0] ;
  Xprime[1] = 2*x[1] - Xprime[1] ;
  Xprime[2] = 2*x[2] - Xprime[2] ;

}


//________________________________________

/// B field distortions ( no Table ) - calculate the distortions due to the shape of the B field

/*! 
    Distortions are calculated point by point and integrated in real time.
    This avoids the time required to set up a table of distorted values but
    is slow for a very large number of points ( > 10,000 ).
*/

void StMagUtilities::UndoBDistortion( const Float_t x[], Float_t Xprime[] )

{

  Double_t ah ;                             // ah carries the sign opposite of E (for forward integration)
  Float_t  B[3] ; 
  Int_t    sign, index = 1 , NSTEPS ;              
  
  if ( x[2] >= 0.0 ) sign =  1 ;                       // (TPC West)
  else               sign = -1 ;                       // (TPC East)  

  Xprime[0]  =  x[0] ;                                 // Integrate backwards from TPC plane to 
  Xprime[1]  =  x[1] ;                                 // the point the electron cluster was born. 
  Xprime[2]  =  sign * TPC_Z0 ;                        // Prepare for different readout planes

  for ( NSTEPS = 5 ; NSTEPS < 1000 ; NSTEPS += 2 )     // Choose ah to be about 1.0 cm, NSTEPS must be odd
    {
      ah = ( x[2] - sign * TPC_Z0 ) / ( NSTEPS - 1 ) ; // Going Backwards! See note above.
      if ( TMath::Abs(ah) < 1.0 ) break ;
    }

  for ( Int_t i = 1; i <= NSTEPS; ++i )                // Simpson's Integration Loop
    {
      if ( i == NSTEPS ) index = 1 ;
      Xprime[2] +=  index*(ah/3) ;
      B3DField( Xprime, B ) ;                          // Work in kGauss, cm
      if ( TMath::Abs(B[2]) > 0.001 )                  // Protect From Divide by Zero Faults
	{
	  Xprime[0] +=  index*(ah/3)*( Const_2*B[0] - Const_1*B[1] ) / B[2] ;
	  Xprime[1] +=  index*(ah/3)*( Const_2*B[1] + Const_1*B[0] ) / B[2] ;
	}
      if ( index != 4 ) index = 4; else index = 2 ;
    }    

}


/// B field distortions (Table) - calculate the distortions due to the shape of the B field

/*! 
    Distortions are calculated and then stored in a table.  This method requires
    about 1 minute of CPU time to generate the table but it is very fast after the
    table has been created.  Use it when you have a large number of points ( > 10,000 ).
*/

void StMagUtilities::FastUndoBDistortion( const Float_t x[], Float_t Xprime[] )

{

#define NPOINTS 22                                  // Number of points on the Z interpolation grid

  static  Int_t   DoOnce = 0 ;
  static  Float_t xarray[2*NPOINTS-1], yarray[2*NPOINTS-1], zarray[NPOINTS] ;
  static  Float_t dXplus[2*NPOINTS-1][2*NPOINTS-1][NPOINTS], dYplus[2*NPOINTS-1][2*NPOINTS-1][NPOINTS] ;
  static  Float_t dXminus[2*NPOINTS-1][2*NPOINTS-1][NPOINTS], dYminus[2*NPOINTS-1][2*NPOINTS-1][NPOINTS] ;

  const   Int_t ORDER = 2 ;                         // Linear interpolation = 1, Quadratic = 2         
  Int_t   i, j, k ;
  Int_t   ilow, jlow, klow ;
  Float_t xx[3] ;
  Float_t save_dX[ORDER+1], saved_dX[ORDER+1] ;
  Float_t save_dY[ORDER+1], saved_dY[ORDER+1] ;

  if ( DoOnce == 0 )
    {
      cout << "StMagUtilities::FastUndoD  Please wait for the tables to fill ... ~60 seconds" << endl ;
      for ( i = 0 ; i < 2*NPOINTS-1 ; i++ )
	{
	  xarray[i] = -1*TPC_Z0 + i*TPC_Z0/(NPOINTS-1) ;
	  xx[0] = xarray[i] ;
	  for ( j = 0 ; j < 2*NPOINTS-1 ; j++ )
	    {
	      yarray[j] = -1*TPC_Z0 + j*TPC_Z0/(NPOINTS-1) ;
	      xx[1] = yarray[j] ;
	      for ( k = 0 ; k < NPOINTS ; k++ )
		{
		  zarray[k] = k * TPC_Z0/(NPOINTS-1) ;
		  xx[2] = zarray[k] ;
		  if ( k == 0 ) xx[2] = 0.1 ;       // Stay off central membrane by a tiny bit
		  UndoBDistortion(xx,Xprime) ;
		  dXplus[i][j][k] = Xprime[0] ;
		  dYplus[i][j][k] = Xprime[1] ;
		  xx[2] = -1*zarray[k] ;            // Note sign flip for Z < 0
		  if ( k == 0 ) xx[2] = -0.1 ;      // Stay off central membrane by a tiny bit
		  UndoBDistortion(xx,Xprime) ;
		  dXminus[i][j][k] = Xprime[0] ;
		  dYminus[i][j][k] = Xprime[1] ;
		}
	    }
	}
      DoOnce = 1 ;
    }

  Search( 2*NPOINTS-1, xarray, x[0], ilow ) ;
  Search( 2*NPOINTS-1, yarray, x[1], jlow ) ;
  Search( NPOINTS,     zarray, TMath::Abs(x[2]), klow ) ;
  if ( ilow < 0 ) ilow = 0 ;   // artifact of Root's binsearch, returns -1 if out of range
  if ( jlow < 0 ) jlow = 0 ;
  if ( klow < 0 ) klow = 0 ;
  if ( ilow + ORDER  >=  2*NPOINTS - 2 ) ilow =  2*NPOINTS - 2 - ORDER ;
  if ( jlow + ORDER  >=  2*NPOINTS - 2 ) jlow =  2*NPOINTS - 2 - ORDER ;
  if ( klow + ORDER  >=  NPOINTS - 1 )   klow =  NPOINTS - 1 - ORDER ;
  
  for ( i = ilow ; i < ilow + ORDER + 1 ; i++ )
    {
      for ( j = jlow ; j < jlow + ORDER + 1 ; j++ )
	{
	  if ( x[2] >= 0 )
	    {
	      save_dX[j-jlow] = Interpolate( &zarray[klow], &dXplus[i][j][klow], ORDER, x[2] )   ;
	      save_dY[j-jlow] = Interpolate( &zarray[klow], &dYplus[i][j][klow], ORDER, x[2] )   ;
	    }
	  else
	    {
	      save_dX[j-jlow] = Interpolate( &zarray[klow], &dXminus[i][j][klow], ORDER, -1*x[2] )   ;
	      save_dY[j-jlow] = Interpolate( &zarray[klow], &dYminus[i][j][klow], ORDER, -1*x[2] )   ;
	    }
	}
      saved_dX[i-ilow] = Interpolate( &yarray[jlow], save_dX, ORDER, x[1] )   ; 
      saved_dY[i-ilow] = Interpolate( &yarray[jlow], save_dY, ORDER, x[1] )   ; 
    }
  Xprime[0] = Interpolate( &xarray[ilow], saved_dX, ORDER, x[0] )   ;
  Xprime[1] = Interpolate( &xarray[ilow], saved_dY, ORDER, x[0] )   ;
  Xprime[2] = x[2] ;
  
}


//________________________________________

/// Twist distortion

void StMagUtilities::UndoTwistDistortion( const Float_t x[], Float_t Xprime[] )

{

  Double_t        Zdrift ;
  Int_t           sign ;

  // Work in TPC coordinates but note that XTWIST and YTWIST reported in Magnet coord system 
  // so they have been negated (below)  
  
  if ( x[2] >= 0.0 ) sign =  1 ;                       // (TPC West)
  else               sign = -1 ;                       // (TPC East)  

  Zdrift = sign * ( TPC_Z0 - TMath::Abs(x[2]) ) ;
  Xprime[0] = x[0] - (     Const_1 * YTWIST - Const_2 * XTWIST ) * Zdrift/1000 ;
  Xprime[1] = x[1] - ( -1* Const_1 * XTWIST - Const_2 * YTWIST ) * Zdrift/1000 ;
  Xprime[2] = x[2] ;                                   // Subtract to undo the distortion 

}


//________________________________________

#define  GAP13_14      1.595            // Width of the gap between the grids at row 13 and row 14 (cm)
#define  GAPRADIUS     121.8            // Radius of gap between rows 13 & 14 at phi = zero degrees (cm)
#define  NYARRAY       33               // Dimension of the vector to contain the YArray
#define  NZDRIFT       15               // Dimension of the vector to contain ZDriftArray

/// Pad row 13 distortion

void StMagUtilities::UndoPad13Distortion( const Float_t x[], Float_t Xprime[] )

{

  const Int_t   TERMS    = 400 ;                 // Number of terms in the sum
  const Float_t SCALE    = 0.192 ;               // Set the scale for the correction
  const Float_t BOX      = 200.0 - GAPRADIUS ;   // Size of the box in which to work
  const Float_t PI       = TMath::Pi() ;

  static Float_t ZDriftArray[NZDRIFT] = {0,1,2,3,4,5,7.5,10,15,20,30,50,75,100,220} ;
  static Float_t YArray[NYARRAY] = { 50.0, 75.0,  100.0,
				     103.5, 104.0, 104.5, 
				     108.7, 109.2, 109.7,
				     113.9, 114.4, 114.9,
				     118.9, 119.6, 119.8, 
				     120.1, 120.5, 121.0, 121.5, 122.1, 122.6, 125.2, 
				     126.2, 127.195, 
				     128.2, 129.195,
				     130.2, 131.195,
				     132.2, 133.195, 137.195, 150., 200. } ;

  static Double_t C[TERMS] ;                     // Coefficients for series
  static Int_t    DoOnce = 0 ;                   // Calculate only once
  static Float_t  SumArray[NZDRIFT][NYARRAY] ;
  static Int_t    ilow, jlow, ORDER ;

  Float_t  y, Zdrift, save_sum[3] ;
  Double_t r, phi, phi0, sum = 0.0 ;

  if ( DoOnce == 0 ) 
    {                          // Put these coefficients in a table to save time
      C[0] = GAP13_14 * GG * SCALE / ( 2 * BOX ) ;   
      for ( Int_t i = 1 ; i < TERMS ; i++ )
	  C[i] = 2 * GG * SCALE * TMath::Sin( GAP13_14*i*PI/( 2*BOX ) ) / ( i * PI ) ;
      for ( Int_t i = 0; i < NZDRIFT ; i++ )
	{
	  Zdrift = ZDriftArray[i] ;
	  for ( Int_t j = 0; j < NYARRAY ; j++ )
	    {
	      sum = 0.0 ;
	      y = YArray[j] ;
	      for ( Int_t k = 1 ; k < TERMS ; k++ )
		{
		  sum += ( C[k] / StarMagE ) * ( 1. - TMath::Exp(-1*k*PI*Zdrift/BOX) )
		         * TMath::Sin(k*PI*(y-GAPRADIUS)/BOX) ;
		}
	      SumArray[i][j] = sum ;
	    }
	}
      DoOnce = 1 ;
    }
  
  r      =  TMath::Sqrt( x[0]*x[0] + x[1]*x[1] ) ;
  phi    =  TMath::ATan2(x[1],x[0]) ;               // Phi ranges from pi to -pi
  phi0   =  ( (Int_t)((TMath::Abs(phi)+PI/12.)/(PI/6.) + 6.0 ) - 6.0 ) * PI/6. ;
  if ( phi < 0 ) phi0 *= -1. ;
  y      =  r * TMath::Cos( phi0 - phi ) ;
  Zdrift =  TPC_Z0 - TMath::Abs(x[2]) ;

  ORDER = 2 ;                                       // Quadratic Interpolation of the table
  Search ( NZDRIFT, ZDriftArray,  Zdrift, ilow ) ;
  Search ( NYARRAY, YArray, y, jlow ) ;

  if ( ilow < 0 ) ilow = 0 ;   // artifact of Root's binsearch, returns -1 if out of range
  if ( jlow < 0 ) jlow = 0 ;
  if ( ilow + ORDER  >=    NZDRIFT - 1 ) ilow =   NZDRIFT - 1 - ORDER ;
  if ( jlow + ORDER  >=    NYARRAY - 1 ) jlow =   NYARRAY - 1 - ORDER ;

  for ( Int_t i = ilow ; i < ilow + ORDER + 1 ; i++ )
    {
      save_sum[i-ilow]   = Interpolate( &YArray[jlow], &SumArray[i][jlow], ORDER, y )   ;
    }

  sum  = Interpolate( &ZDriftArray[ilow], save_sum, ORDER, Zdrift )   ; 

  if ( r > 0.0 )
    {
      phi =  phi - ( Const_1*(-1*sum)*TMath::Cos(phi0-phi) + Const_0*sum*TMath::Sin(phi0-phi) ) / r ;      
      r   =  r   - ( Const_0*sum*TMath::Cos(phi0-phi) - Const_1*(-1*sum)*TMath::Sin(phi0-phi) ) ;  
    }                                               // Subtract to Undo the distortions

  Xprime[0] = r * TMath::Cos(phi) ;
  Xprime[1] = r * TMath::Sin(phi) ;
  Xprime[2] = x[2] ;
  
}


//________________________________________

/// Clock distortion

void StMagUtilities::UndoClockDistortion( const Float_t x[], Float_t Xprime[] )

{

  Double_t r, phi ;

  r      =  TMath::Sqrt( x[0]*x[0] + x[1]*x[1] ) ;
  phi    =  TMath::ATan2(x[1],x[0]) ;

  if ( x[2] < 0 )  phi += EASTCLOCKERROR/1000. ;    // Phi rotation error in milli-radians
  if ( x[2] >= 0 ) phi += WESTCLOCKERROR/1000. ;    // Phi rotation error in milli-radians

  Xprime[0] = r * TMath::Cos(phi) ;
  Xprime[1] = r * TMath::Sin(phi) ;
  Xprime[2] = x[2] ;

}


//________________________________________

/// Membrane distortion
 
void StMagUtilities::UndoMembraneDistortion( const Float_t x[], Float_t Xprime[] )

{

  Float_t  Er_integral, Ephi_integral ;
  Double_t r, phi, z ;

  r      =  TMath::Sqrt( x[0]*x[0] + x[1]*x[1] ) ;
  phi    =  TMath::ATan2(x[1],x[0]) ;
  if ( phi < 0 ) phi += 2*TMath::Pi() ;             // Table uses phi from 0 to 2*Pi
  z      =  x[2] ;
  if ( z > 0 && z <  0.2 ) z =  0.2 ;               // Protect against discontinuity at CM
  if ( z < 0 && z > -0.2 ) z = -0.2 ;               // Protect against discontinuity at CM
 
  InterpolateEdistortion( r, phi, z, cmEr, cmEphi, Er_integral, Ephi_integral ) ;

  // Subtract to Undo the distortions
  if ( r > 0.0 ) 
    {
      phi =  phi - ( Const_0*Ephi_integral - Const_1*Er_integral ) / r ;      
      r   =  r   - ( Const_0*Er_integral   + Const_1*Ephi_integral ) ;  
    }

  Xprime[0] = r * TMath::Cos(phi) ;
  Xprime[1] = r * TMath::Sin(phi) ;
  Xprime[2] = x[2] ;

}


//________________________________________

/// Endcap distortion

void StMagUtilities::UndoEndcapDistortion( const Float_t x[], Float_t Xprime[] )

{

  Float_t  Er_integral, Ephi_integral ;
  Double_t r, phi, z ;

  r      =  TMath::Sqrt( x[0]*x[0] + x[1]*x[1] ) ;
  phi    =  TMath::ATan2(x[1],x[0]) ;
  if ( phi < 0 ) phi += 2*TMath::Pi() ;             // Table uses phi from 0 to 2*Pi
  z      =  x[2] ;
  if ( z > 0 && z <  0.2 ) z =  0.2 ;               // Protect against discontinuity at CM
  if ( z < 0 && z > -0.2 ) z = -0.2 ;               // Protect against discontinuity at CM

  InterpolateEdistortion( r, phi, z, endEr, endEphi, Er_integral, Ephi_integral ) ;

  // Subtract to Undo the distortions
  if ( r > 0.0 ) 
    {
      phi =  phi - ( Const_0*Ephi_integral - Const_1*Er_integral ) / r ;      
      r   =  r   - ( Const_0*Er_integral   + Const_1*Ephi_integral ) ;  
    }

  Xprime[0] = r * TMath::Cos(phi) ;
  Xprime[1] = r * TMath::Sin(phi) ;
  Xprime[2] = x[2] ;

}


//________________________________________

/// IFC distortion

void StMagUtilities::UndoIFCShiftDistortion( const Float_t x[], Float_t Xprime[] )
// Electrostatic equations solved in Rectangular Coodinates by Jim Thomas
// Updated to work in cylindrical coordinates by Jamie Dunlop  11/01/2001
{ 

  Float_t  Er_integral, Ephi_integral ;
  Double_t r, phi, z ;

  static Int_t DoOnce = 0 ;

  if ( DoOnce == 0 )
    {
      Int_t Nterms = 100 ;
      for ( Int_t i = 0 ; i < neZ ; ++i ) 
	{
	  z = TMath::Abs( eZList[i] ) ;
	  for ( Int_t j = 0 ; j < neR ; ++j ) 
	    {
	      r = eRadius[j] ;
	      Double_t IntegralOverZ = 0 ;
	      for ( Int_t n = 1 ; n < Nterms ; ++n ) 
		{
		  Double_t k  = (2*n-1) * TMath::Pi() / TPC_Z0 ;
		  Double_t Cn = 4.0 * IFCShift / ( k * TPC_Z0 ) ;
		  Double_t Numerator =
		    TMath::BesselK0( k*OFCRadius ) * TMath::BesselI1( k*r ) -
		    TMath::BesselK1( k*r )         * TMath::BesselI0( k*OFCRadius ) ;
		  Double_t Denominator =
		    TMath::BesselK0( k*OFCRadius ) * TMath::BesselI0( k*IFCRadius ) -
		    TMath::BesselK0( k*IFCRadius ) * TMath::BesselI0( k*OFCRadius ) ;
		  Double_t zterm = 1 + cos( k*z ) ;
		  IntegralOverZ += Cn * zterm * Numerator / Denominator ;
		}
	      if  ( eZList[i] < 0 )  IntegralOverZ = -1 * IntegralOverZ ;  // Force AntiSymmetry of solutions in Z
	      for ( Int_t iphi = 0 ; iphi < nePhi ; ++ iphi ) 
		{ 
		  shiftEr[i][iphi][j]   = IntegralOverZ ; 
		  shiftEphi[i][iphi][j] = 0.0 ; 
		}
	    }
	}
      DoOnce = 1 ;
    }
  
  r      =  TMath::Sqrt( x[0]*x[0] + x[1]*x[1] ) ;
  phi    =  TMath::ATan2(x[1],x[0]) ;
  if ( phi < 0 ) phi += 2*TMath::Pi() ;             // Table uses phi from 0 to 2*Pi
  z      =  x[2] ;
  if ( z > 0 && z <  0.2 ) z =  0.2 ;               // Protect against discontinuity at CM
  if ( z < 0 && z > -0.2 ) z = -0.2 ;               // Protect against discontinuity at CM

  InterpolateEdistortion( r, phi, z, shiftEr, shiftEphi, Er_integral, Ephi_integral ) ;

  // Subtract to Undo the distortions
  if ( r > 0.0 ) 
    {
      phi =  phi - ( Const_0*Ephi_integral - Const_1*Er_integral ) / r ;      
      r   =  r   - ( Const_0*Er_integral   + Const_1*Ephi_integral ) ;  
    }

  Xprime[0] = r * TMath::Cos(phi) ;
  Xprime[1] = r * TMath::Sin(phi) ;
  Xprime[2] = x[2] ;

}


//________________________________________

/// Space Charge distortion

void StMagUtilities::UndoSpaceChargeDistortion( const Float_t x[], Float_t Xprime[] )
// Electrostatic equations solved by Jamie Dunlop  11/01/2001
// Updated to include linear increase of charge from endcap to CM by Jim Thomas 12/18/2001

{ 
  

  Float_t  Er_integral, Ephi_integral ;
  Double_t r, phi, z ;

  static Int_t DoOnce = 0 ;

  if ( DoOnce == 0 )
    {
      Int_t Nterms = 100 ;
      for ( Int_t i = 0 ; i < neZ ; ++i ) 
	{
	  z = TMath::Abs( eZList[i] ) ;
	  for ( Int_t j = 0 ; j < neR ; ++j ) 
	    {
	      r = eRadius[j] ;
	      Double_t IntegralOverZ = 0 ;
	      for ( Int_t n = 1 ; n < Nterms ; ++n ) 
		{
		  Double_t k  = n * TMath::Pi() / TPC_Z0 ;  // Integrated Charge Density
		  Double_t Zterm = pow(-1,(n+1)) * ( 1.0 - TMath::Cos( k * ( TPC_Z0 - z ) ) ) ;
		  //Double_t k  = (2*n-1) * TMath::Pi() / TPC_Z0 ;  // Uniform Charge Density
		  //Double_t Zterm = 1.0 + TMath::Cos( k *  z ) ;   // Uniform Charge Density
		  Double_t Cn = -4.0 / ( k*k*k * TPC_Z0 * StarMagE ) ;
		  Double_t Numerator =
		    TMath::BesselI1( k*r )         * TMath::BesselK0( k*OFCRadius ) -
		    TMath::BesselI1( k*r )         * TMath::BesselK0( k*IFCRadius ) +
		    TMath::BesselK1( k*r )         * TMath::BesselI0( k*OFCRadius ) -
		    TMath::BesselK1( k*r )         * TMath::BesselI0( k*IFCRadius ) ;
		  Double_t Denominator =
		    TMath::BesselK0( k*OFCRadius ) * TMath::BesselI0( k*IFCRadius ) -
		    TMath::BesselK0( k*IFCRadius ) * TMath::BesselI0( k*OFCRadius ) ;
		  IntegralOverZ += Cn * Zterm * Numerator / Denominator ;
		}
	      for ( Int_t iphi = 0 ; iphi < nePhi ; ++ iphi ) 
		{ 
		  spaceEr[i][iphi][j]   = IntegralOverZ ; 
		  spaceEphi[i][iphi][j] = 0.0 ; 
		}
	    }
	}
      DoOnce = 1 ;
    }
  
  r      =  TMath::Sqrt( x[0]*x[0] + x[1]*x[1] ) ;
  phi    =  TMath::ATan2(x[1],x[0]) ;
  if ( phi < 0 ) phi += 2*TMath::Pi() ;             // Table uses phi from 0 to 2*Pi
  z      =  x[2] ;
  if ( z > 0 && z <  0.2 ) z =  0.2 ;               // Protect against discontinuity at CM
  if ( z < 0 && z > -0.2 ) z = -0.2 ;               // Protect against discontinuity at CM

  InterpolateEdistortion( r, phi, z, spaceEr, spaceEphi, Er_integral, Ephi_integral ) ;
  // Get Space Charge **** Every Event (JCD This is actually per hit)***
  // Need to reset the instance every hit.  May be slow, but there's no per-event hook.
  
  if ( fSpaceCharge !=0 ) {
      // need to reset it. 
      fSpaceCharge = StDetectorDbSpaceCharge::instance();

      SpaceCharge = fSpaceCharge->getSpaceChargeCoulombs((double)gFactor) ;
  }
  
  // Subtract to Undo the distortions
  if ( r > 0.0 ) 
    {
      phi =  phi - SpaceCharge * ( Const_0*Ephi_integral - Const_1*Er_integral ) / r ;      
      r   =  r   - SpaceCharge * ( Const_0*Er_integral   + Const_1*Ephi_integral ) ;  
    }

  Xprime[0] = r * TMath::Cos(phi) ;
  Xprime[1] = r * TMath::Sin(phi) ;
  Xprime[2] = x[2] ;

}

  
//________________________________________

/// Read the electric and magnetic field maps stored on disk

void StMagUtilities::ReadField( )

{

  FILE    *magfile, *efile, *eefile, *b3Dfile ;
  TString comment, filename, filename3D ;
  TString MapLocation ;
  TString BaseLocation = "$STAR/StarDb/StMagF/" ;     // Base Directory for Maps

  if ( gMap == kMapped )                    // Mapped field values
    {
      if ( TMath::Abs(gFactor) > 0.8 )      // Scale from full field data 
	{
	  if ( gFactor > 0 )
	    {
	      filename   = "bfield_full_positive_2D.dat" ;
	      filename3D = "bfield_full_positive_3D.dat" ;
	      comment    = "Measured Full Field" ;
	      gRescale   = 1 ;                // Normal field 
	    }
	  else
	    {
	      filename   = "bfield_full_negative_2D.dat" ;
	      filename3D = "bfield_full_negative_3D.dat" ;
	      comment    = "Measured Full Field Reversed" ;
	      gRescale   = -1 ;               // Reversed field
	    }
	}
      else                                  // Scale from half field data             
	{
	  filename   = "bfield_half_positive_2D.dat" ;
	  filename3D = "bfield_half_positive_3D.dat" ;
          comment    = "Measured Half Field" ;
	  gRescale   = 2 ;                    // Adjust scale factor to use half field data
	}
    }
  else if ( gMap == kConstant )             // Constant field values
    {
      filename = "const_full_positive_2D.dat" ;
      comment  = "Constant Full Field" ;
      gRescale = 1 ;                        // Normal field
    }
  else
    {
      fprintf(stderr,"StMagUtilities::ReadField  No map available - you must choose a mapped field or a constant field\n");
      exit(1) ;
    }
      
  printf("StMagUtilities::ReadField  Reading Magnetic Field:  %s,  Scale factor = %f \n",comment.Data(),gFactor);
  printf("StMagUtilities::ReadField  Filename is %s, Adjusted Scale factor = %f \n",filename.Data(),gFactor*gRescale);

  
  printf("StMagUtilities::ReadField  Version: ") ;
  
  if ( mDistortionMode & kBMap )         printf ("3D Mag Field Distortions") ;
  if ( mDistortionMode & kPadrow13 )     printf (" + Padrow 13") ;
  if ( mDistortionMode & kTwist )        printf (" + Twist") ;
  if ( mDistortionMode & kClock )        printf (" + Clock") ;
  if ( mDistortionMode & kMembrane )     printf (" + Central Membrane") ;
  if ( mDistortionMode & kEndcap )       printf (" + Endcap") ;
  if ( mDistortionMode & kIFCShift )     printf (" + IFCShift") ;
  if ( mDistortionMode & kSpaceCharge )  printf (" + SpaceCharge") ;

  printf("\n");
  if (mDistortionMode & kElectricField2001){
      printf("StMagUtilities::ReadField  2001 Electric Field\n");
  }
  
  else {
      printf("StMagUtilities::ReadField  2000 Electric Field\n");
  }
  
  
  MapLocation = BaseLocation + filename ;
  gSystem->ExpandPathName(MapLocation) ;
  magfile = fopen(MapLocation.Data(),"r") ;

  if (magfile) 

    {
      Char_t cname[128] ;
      fgets  ( cname, sizeof(cname) , magfile ) ;    // Read comment lines at begining of file
      fgets  ( cname, sizeof(cname) , magfile ) ;
      fgets  ( cname, sizeof(cname) , magfile ) ;
      fgets  ( cname, sizeof(cname) , magfile ) ;
      fgets  ( cname, sizeof(cname) , magfile ) ;

      for ( Int_t j=0 ; j < nZ ; j++ ) 
	{
	  for ( Int_t k=0 ; k < nR ; k++ )
	    {
	      fgets  ( cname, sizeof(cname) , magfile ) ; 
	      sscanf ( cname, " %f %f %f %f ", &Radius[k], &ZList[j], &Br[j][k], &Bz[j][k] ) ;  
	    }
	}
    }

  else 

    { 
      fprintf(stderr,"StMagUtilities::ReadField  File %s not found !\n",MapLocation.Data());
      exit(1);
    }

  fclose(magfile) ;
      
  MapLocation = BaseLocation + filename3D ;
  gSystem->ExpandPathName(MapLocation) ;
  b3Dfile = fopen(MapLocation.Data(),"r") ;
  printf("StMagUtilities::ReadField  Reading 3D Magnetic Field file: %s \n",filename3D.Data());

  if (b3Dfile) 

    {
      Char_t cname[128] ;
      fgets  ( cname, sizeof(cname) , b3Dfile ) ;    // Read comment lines at begining of file
      fgets  ( cname, sizeof(cname) , b3Dfile ) ;    // Read comment lines at begining of file
      fgets  ( cname, sizeof(cname) , b3Dfile ) ;    // Read comment lines at begining of file
      fgets  ( cname, sizeof(cname) , b3Dfile ) ;    // Read comment lines at begining of file
      fgets  ( cname, sizeof(cname) , b3Dfile ) ;    // Read comment lines at begining of file
      fgets  ( cname, sizeof(cname) , b3Dfile ) ;    // Read comment lines at begining of file
      
      for ( Int_t i=0 ; i < nPhi ; i++ ) 
	{
	  for ( Int_t j=0 ; j < nZ ; j++ ) 
	    {
	      for ( Int_t k=0 ; k < nR ; k++ )
		{
		  fgets  ( cname, sizeof(cname) , b3Dfile ) ; 
		  sscanf ( cname, " %f %f %f %f %f %f ",
			   &R3D[k], &Z3D[j], &Phi3D[i], &Br3D[i][j][k], &Bz3D[i][j][k], &Bphi3D[i][j][k] ) ;
		  Phi3D[i] *= TMath::Pi() / 180. ;   // Convert to Radians  phi = 0 to 2*Pi
		}
	    }
	}
    }

  else if ( gMap == kConstant )             // Constant field values

    {
      for ( Int_t i=0 ; i < nPhi ; i++ ) 
	{
	  for ( Int_t j=0 ; j < nZ ; j++ ) 
	    {
	      for ( Int_t k=0 ; k < nR ; k++ )
		{
		  Br3D[i][j][k] = Br[j][k] ;
		  Bz3D[i][j][k] = Bz[j][k] ;
		  Bphi3D[i][j][k] = 0 ;
		}
	    }
	}
    }

  else

    { 
      fprintf(stderr,"StMagUtilities::ReadField  File %s not found !\n",MapLocation.Data());
      exit(1);
    }

  fclose(b3Dfile) ;

  filename = "membrane_efield.dat" ;
  MapLocation = BaseLocation + filename ;
  gSystem->ExpandPathName(MapLocation) ;
  efile = fopen(MapLocation.Data(),"r") ;
  printf("StMagUtilities::ReadField  Reading CM Electric Field Distortion File: %s \n",filename.Data());

  if (efile) 
    {

      Char_t cname[128] ;
      fgets  ( cname, sizeof(cname) , efile ) ;    // Read comment lines at begining of file
      fgets  ( cname, sizeof(cname) , efile ) ;
      fgets  ( cname, sizeof(cname) , efile ) ;
      fgets  ( cname, sizeof(cname) , efile ) ;
      fgets  ( cname, sizeof(cname) , efile ) ;
      fgets  ( cname, sizeof(cname) , efile ) ;
      
      for ( Int_t i=0 ; i < neZ ; i++ ) 
	{
	  for ( Int_t j=0 ; j < nePhi ; j++ )
	    {
	      for ( Int_t k=0 ; k < neR ; k++ )
		{
		  if ( j == nePhi-1 )
		    {
		      ePhiList[j] = 6.2832 ;    // Repeat phi = 0 column in phi == 2 PI column
		      cmEr[i][j][k] = cmEr[i][0][k] ;
		      cmEphi[i][j][k] = cmEphi[i][0][k] ;
		    }
		  else
		    {
		      fgets  ( cname, sizeof(cname) , efile ) ; 
		      sscanf ( cname, " %f %f %f %f %f", &eRadius[k], &ePhiList[j], 
			       &eZList[i], &cmEr[i][j][k], &cmEphi[i][j][k] ) ;  
		      //ePhiList[j] *= TMath::Pi() / 180. ;  // Assume table uses  phi = 0 to 2*Pi
		    }
		}
	    }
	}
    }      

  else 
    { 
      fprintf(stderr,"StMagUtilities::ReadField  File %s not found !\n",MapLocation.Data());
      exit(1);
    }

  fclose(efile) ;

  filename = "endcap_efield.dat" ;
  MapLocation = BaseLocation + filename ;
  gSystem->ExpandPathName(MapLocation) ;
  eefile = fopen(MapLocation.Data(),"r") ;
  printf("StMagUtilities::ReadField  Reading Endcap Electric Field Distortion File: %s \n",filename.Data());

  if (eefile) 
    {

      Char_t cname[128] ;
      fgets  ( cname, sizeof(cname) , eefile ) ;    // Read comment lines at begining of file
      fgets  ( cname, sizeof(cname) , eefile ) ;
      fgets  ( cname, sizeof(cname) , eefile ) ;
      fgets  ( cname, sizeof(cname) , eefile ) ;
      fgets  ( cname, sizeof(cname) , eefile ) ;
      fgets  ( cname, sizeof(cname) , eefile ) ;
      
      for ( Int_t i=0 ; i < neZ ; i++ ) 
	{
	  for ( Int_t j=0 ; j < nePhi ; j++ )
	    {
	      for ( Int_t k=0 ; k < neR ; k++ )
		{
		  if ( j == nePhi-1 )
		    {
		      ePhiList[j] = 6.2832 ;    // Repeat phi = 0 column in phi == 2 PI column
		      endEr[i][j][k] = endEr[i][0][k] ;
		      endEphi[i][j][k] = endEphi[i][0][k] ;
		    }
		  else
		    {
		      fgets  ( cname, sizeof(cname) , eefile ) ; 
		      sscanf ( cname, " %f %f %f %f %f", &eRadius[k], &ePhiList[j], 
			       &eZList[i], &endEr[i][j][k], &endEphi[i][j][k] ) ;  
		      //eePhiList[j] *= TMath::Pi() / 180. ;  // Assume table uses  phi = 0 to 2*Pi
		    }
		}
	    }
	}
    }      

  else 
    { 
      fprintf(stderr,"StMagUtilities::ReadField  File %s not found !\n",MapLocation.Data());
      exit(1);
    }

  fclose(eefile) ;

  return ;

}


//________________________________________

/// Interpolate the B field map - 2D interpolation

void StMagUtilities::Interpolate2DBfield( const Float_t r, const Float_t z, Float_t &Br_value, Float_t &Bz_value )

{

  Float_t fscale ;

  fscale = 0.001*gFactor*gRescale ;               // Scale STAR maps to work in kGauss, cm

  const   Int_t ORDER = 1  ;                      // Linear interpolation = 1, Quadratic = 2        
  static  Int_t jlow, klow ;                            
  Float_t save_Br[ORDER+1] ;
  Float_t save_Bz[ORDER+1] ;

  Search ( nZ, ZList,  z, jlow ) ;
  Search ( nR, Radius, r, klow ) ;
  if ( jlow < 0 ) jlow = 0 ;   // artifact of Root's binsearch, returns -1 if out of range
  if ( klow < 0 ) klow = 0 ;
  if ( jlow + ORDER  >=    nZ - 1 ) jlow =   nZ - 1 - ORDER ;
  if ( klow + ORDER  >=    nR - 1 ) klow =   nR - 1 - ORDER ;

  for ( Int_t j = jlow ; j < jlow + ORDER + 1 ; j++ )
    {
      save_Br[j-jlow]   = Interpolate( &Radius[klow], &Br[j][klow], ORDER, r )   ;
      save_Bz[j-jlow]   = Interpolate( &Radius[klow], &Bz[j][klow], ORDER, r )   ;
    }
  Br_value  = fscale * Interpolate( &ZList[jlow], save_Br, ORDER, z )   ; 
  Bz_value  = fscale * Interpolate( &ZList[jlow], save_Bz, ORDER, z )   ; 

}

/// Interpolate the B field map - 3D interpolation

void StMagUtilities::Interpolate3DBfield( const Float_t r, const Float_t z, const Float_t phi, 
			 Float_t &Br_value, Float_t &Bz_value, Float_t &Bphi_value )
{

  Float_t fscale ;

  fscale = 0.001*gFactor*gRescale ;               // Scale STAR maps to work in kGauss, cm

  const   Int_t ORDER = 1 ;                      // Linear interpolation = 1, Quadratic = 2   
  static  Int_t ilow, jlow, klow ;
  Float_t save_Br[ORDER+1],   saved_Br[ORDER+1] ;
  Float_t save_Bz[ORDER+1],   saved_Bz[ORDER+1] ;
  Float_t save_Bphi[ORDER+1], saved_Bphi[ORDER+1] ;

  Search( nPhi, Phi3D, phi, ilow ) ;
  Search( nZ,   Z3D,   z,   jlow ) ;
  Search( nR,   R3D,   r,   klow ) ;
  if ( ilow < 0 ) ilow = 0 ;   // artifact of Root's binsearch, returns -1 if out of range
  if ( jlow < 0 ) jlow = 0 ;
  if ( klow < 0 ) klow = 0 ;

  if ( ilow + ORDER  >=  nPhi - 1 ) ilow = nPhi - 1 - ORDER ;
  if ( jlow + ORDER  >=    nZ - 1 ) jlow =   nZ - 1 - ORDER ;
  if ( klow + ORDER  >=    nR - 1 ) klow =   nR - 1 - ORDER ;

  for ( Int_t i = ilow ; i < ilow + ORDER + 1 ; i++ )
    {
      for ( Int_t j = jlow ; j < jlow + ORDER + 1 ; j++ )
	{
	  save_Br[j-jlow]   = Interpolate( &R3D[klow], &Br3D[i][j][klow], ORDER, r )   ;
	  save_Bz[j-jlow]   = Interpolate( &R3D[klow], &Bz3D[i][j][klow], ORDER, r )   ;
	  save_Bphi[j-jlow] = Interpolate( &R3D[klow], &Bphi3D[i][j][klow], ORDER, r ) ; 
	}
      saved_Br[i-ilow]   = Interpolate( &Z3D[jlow], save_Br, ORDER, z )   ; 
      saved_Bz[i-ilow]   = Interpolate( &Z3D[jlow], save_Bz, ORDER, z )   ; 
      saved_Bphi[i-ilow] = Interpolate( &Z3D[jlow], save_Bphi, ORDER, z ) ; 
    }
  Br_value   = fscale * Interpolate( &Phi3D[ilow], saved_Br, ORDER, phi )   ;
  Bz_value   = fscale * Interpolate( &Phi3D[ilow], saved_Bz, ORDER, phi )   ;
  Bphi_value = fscale * Interpolate( &Phi3D[ilow], saved_Bphi, ORDER, phi ) ; 

  return ;
 
}


//________________________________________

/// Interpolate the electric field maps

void StMagUtilities::InterpolateEdistortion( const Float_t r, const Float_t phi, const Float_t z, 
					     const Float_t Er[neZ][nePhi][neR], const Float_t Ephi[neZ][nePhi][neR], 
                                             Float_t &Er_integral, Float_t &Ephi_integral )

{

  const   Int_t ORDER = 1 ;                      // Linear interpolation = 1, Quadratic = 2         
  static  Int_t ilow, jlow, klow ;
  Float_t save_Er[ORDER+1],   saved_Er[ORDER+1] ;
  Float_t save_Ephi[ORDER+1], saved_Ephi[ORDER+1] ;

  Search( neZ,   eZList,   z,   ilow   ) ;
  Search( nePhi, ePhiList, phi, jlow   ) ;
  Search( neR,   eRadius,  r,   klow   ) ;
  if ( ilow < 0 ) ilow = 0 ;   // artifact of Root's binsearch, returns -1 if out of range
  if ( jlow < 0 ) jlow = 0 ;
  if ( klow < 0 ) klow = 0 ;

  if ( ilow + ORDER  >=    neZ - 1 ) ilow =   neZ - 1 - ORDER ;
  if ( jlow + ORDER  >=  nePhi - 1 ) jlow = nePhi - 1 - ORDER ;
  if ( klow + ORDER  >=    neR - 1 ) klow =   neR - 1 - ORDER ;

  for ( Int_t i = ilow ; i < ilow + ORDER + 1 ; i++ )
    {
      for ( Int_t j = jlow ; j < jlow + ORDER + 1 ; j++ )
	{
	  save_Er[j-jlow]     = Interpolate( &eRadius[klow], &Er[i][j][klow], ORDER, r )   ;
	  save_Ephi[j-jlow]   = Interpolate( &eRadius[klow], &Ephi[i][j][klow], ORDER, r )   ;
	}
      saved_Er[i-ilow]     = Interpolate( &ePhiList[jlow], save_Er, ORDER, phi )   ; 
      saved_Ephi[i-ilow]   = Interpolate( &ePhiList[jlow], save_Ephi, ORDER, phi )   ; 
    }
  Er_integral     = Interpolate( &eZList[ilow], saved_Er, ORDER, z )   ;
  Ephi_integral   = Interpolate( &eZList[ilow], saved_Ephi, ORDER, z )   ;

  return ;
 
}


//________________________________________

/// Interpolate a 3x2 table (quadratic) or a 2x2 table (linear)

Float_t StMagUtilities::Interpolate( const Float_t Xarray[], const Float_t Yarray[], 
				     const Int_t ORDER, const Float_t x )

{

  Float_t y ;


  if ( ORDER == 2 )                // Quadratic Interpolation = 2 

    {
      y  = (x-Xarray[1]) * (x-Xarray[2]) * Yarray[0] / ( (Xarray[0]-Xarray[1]) * (Xarray[0]-Xarray[2]) ) ; 
      y += (x-Xarray[2]) * (x-Xarray[0]) * Yarray[1] / ( (Xarray[1]-Xarray[2]) * (Xarray[1]-Xarray[0]) ) ; 
      y += (x-Xarray[0]) * (x-Xarray[1]) * Yarray[2] / ( (Xarray[2]-Xarray[0]) * (Xarray[2]-Xarray[1]) ) ; 
      
    }

  else                             // Linear Interpolation = 1

    {
      y  = Yarray[0] + ( Yarray[1]-Yarray[0] ) * ( x-Xarray[0] ) / ( Xarray[1] - Xarray[0] ) ;
    }

  return (y) ;

}


//________________________________________

/// Search an ordered table by starting at the most recently used point

void StMagUtilities::Search( Int_t N, Float_t Xarray[], Float_t x, Int_t &low )

{

  Long_t middle, high ;
  Int_t  ascend = 0, increment = 1 ;

  if ( Xarray[N-1] >= Xarray[0] ) ascend = 1 ;  // Ascending ordered table if true
  
  if ( low < 0 || low > N-1 ) { low = -1 ; high = N ; }

  else                                            // Ordered Search phase
    {
      if ( (Int_t)( x >= Xarray[low] ) == ascend ) 
	{
	  if ( low == N-1 ) return ;          
	  high = low + 1 ;
	  while ( (Int_t)( x >= Xarray[high] ) == ascend )  
	    {
	      low = high ;
	      increment *= 2 ;
	      high = low + increment ;
	      if ( high > N-1 )  {  high = N ; break ;  }
	    }
	}
      else
	{
	  if ( low == 0 )  {  low = -1 ;  return ;  }
	  high = low - 1 ;
	  while ( (Int_t)( x < Xarray[low] ) == ascend )
	    {
	      high = low ;
	      increment *= 2 ;
	      if ( increment >= high )  {  low = -1 ;  break ;  }
	      else  low = high - increment ;
	    }
	}
    }

  while ( (high-low) != 1 )                      // Binary Search Phase
    {
      middle = ( high + low ) / 2 ;
      if ( (Int_t)( x >= Xarray[middle] ) == ascend )
	low = middle ;
      else
	high = middle ;
    }

  if ( x == Xarray[N-1] ) low = N-2 ;
  if ( x == Xarray[0]   ) low = 0 ;

  return ;
       
}
















