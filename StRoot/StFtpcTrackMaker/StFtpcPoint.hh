// $Id: StFtpcPoint.hh,v 1.11 2003/01/16 18:04:33 oldi Exp $
// $Log: StFtpcPoint.hh,v $
// Revision 1.11  2003/01/16 18:04:33  oldi
// Bugs eliminated. Now it compiles on Solaris again.
// Split residuals for global and primary fit.
//
// Revision 1.10  2002/11/06 13:45:42  oldi
// Flag for clusters not to be used for tracking introduced.
// Code clean ups.
//
// Revision 1.9  2002/06/04 13:34:59  oldi
// Transformation of local FTPC coordinates in global coordinates introduced.
// An additional flag keeps track in which coordinate system the point position
// is measured.
// 'Tracked' flag is set correctly, now.
//
// Revision 1.8  2002/04/05 16:50:40  oldi
// Cleanup of MomentumFit (StFtpcMomentumFit is now part of StFtpcTrack).
// Each Track inherits from StHelix, now.
// Therefore it is possible to calculate, now:
//  - residuals
//  - vertex estimations obtained by back extrapolations of FTPC tracks
// Chi2 was fixed.
// Many additional minor (and major) changes.
//
// Revision 1.7  2002/01/29 11:08:03  oldi
// Write() renamed to WriteCluster() resp. WriteTrack() to avoid compiler warnings.
// As a result the functions TObject::Write() are available again (directly).
//
// Revision 1.6  2001/01/25 15:21:51  oldi
// Review of the complete code.
// Fix of several bugs which caused memory leaks:
//  - Tracks were not allocated properly.
//  - Tracks (especially split tracks) were not deleted properly.
//  - TClonesArray seems to have a problem (it could be that I used it in a
//    wrong way). I changed all occurences to TObjArray which makes the
//    program slightly slower but much more save (in terms of memory usage).
// Speed up of HandleSplitTracks() which is now 12.5 times faster than before.
// Cleanup.
//
// Revision 1.5  2000/11/10 18:37:46  oldi
// New constructor added.
// StThreeVector replaced by TVector3 to be able to use ROOT output (e.g. Write()).
// Cleanup.
//
// Revision 1.4  2000/08/01 12:24:04  hummler
// add writing to table functionality (ToTable() function)
//
// Revision 1.3  2000/07/18 21:22:16  oldi
// Changes due to be able to find laser tracks.
// Cleanup: - new functions in StFtpcConfMapper, StFtpcTrack, and StFtpcPoint
//            to bundle often called functions
//          - short functions inlined
//          - formulas of StFormulary made static
//          - avoid streaming of objects of unknown size
//            (removes the bunch of CINT warnings during compile time)
//          - two or three minor bugs cured
//
// Revision 1.2  2000/06/13 14:49:25  oldi
// Added SetTrackedFlag(Bool_t tracked) and GetTrackedFlag() to take care of the
// bit 5 of mFlags.
// Changed SetUsage(Bool_t f) to change the bit 5 of mFlags, too.
//
// Revision 1.1  2000/05/11 15:14:49  oldi
// Changed class names *Hit.* due to already existing class StFtpcHit.cxx in StEvent
//

///////////////////////////////////////////////////////////////////////////////////
//                                                                               //
// StFtpcPoint class - representation of one FTPC cluster for the FTPC trackers. //
//                                                                               //
///////////////////////////////////////////////////////////////////////////////////

#ifndef STAR_StFtpcPoint
#define STAR_StFtpcPoint

#include "TObject.h"
#include "TObjArray.h"
#include "TVector3.h"
#include "TMath.h"

#include "tables/St_fcl_fppoint_Table.h"
#include "tables/St_ffs_gepoint_Table.h"

#include "StFtpcTrack.hh"

class StFtpcTrack;

class StFtpcPoint : public TObject {
  
private:
  
  TVector3  mCoord;         // vector of cluster coordinates
  TVector3  mError;         // vector of errors on cluster coordinates
  
  Bool_t    mGlobalCoord;   // flag that indicates if the hit is stored in global or local (FTPC) coordinates
  Bool_t    mUsed;          // flag that indicates if the hit is assigned to a track 
  Int_t     mHitNumber;     // number of this cluster in this event
  Int_t     mNextHitNumber; // number of next hit on same track
  Int_t     mTrackNumber;   // track number to which this cluster belongs to

  // additional input variables from cluster finder
  
  Long_t    mPadRow;        // FTPC row number
  Long_t    mSector;        // FTPC readout sector number
  Long_t    mNumberPads;    // number of pads in cluster
  Long_t    mNumberBins;    // number of consecutive timebins in cluster
  Long_t    mMaxADC;        // cluster peak height (adc channels)
  Long_t    mCharge;        // cluster charge (adc channels)
  Long_t    mFlags;         // bit0:unfolded, bit1:unfold failed,
                            // bit2:saturated, bit3:bad shape, 
                            // bit4:cut off, bit5:tracked, 
                            // bit6:global coords, bit7:don't use for tracking
  Double_t  mSigmaPhi;      // cluster sigma in pad direction
  Double_t  mSigmaR;        // cluster sigma in drift direction

    // Residuals
  Double_t  mXPrimResidual;     // x distance of measured point to primary momentum fit
  Double_t  mYPrimResidual;     // y distance of measured point to primary momentum fit
  Double_t  mRPrimResidual;     // r of measured point to r of primary momentum fit
  Double_t  mPhiPrimResidual;   // angle of measured point to angle of primary momentum fit
  Double_t  mXGlobResidual;     // x distance of measured point to global momentum fit
  Double_t  mYGlobResidual;     // y distance of measured point to global momentum fit
  Double_t  mRGlobResidual;     // r of measured point to r of global momentum fit
  Double_t  mPhiGlobResidual;   // angle of measured point to angle of global momentum fit

public:
  
                 StFtpcPoint();                                 // default constructor
                 StFtpcPoint(Long_t   row, 
			     Long_t   sector, 
			     Long_t   n_pads, 
			     Long_t   n_bins, 
			     Long_t   max_adc, 
			     Long_t   charge, 
			     Double_t x, 
			     Double_t y, 
			     Double_t z, 
			     Double_t x_err, 
			     Double_t y_err, 
			     Double_t z_err, 
			     Double_t s_phi, 
			     Double_t s_r, 
			     Long_t   flags);                   // constructor to be filled directly from the cluster finder
                 StFtpcPoint(fcl_fppoint_st *point_st);         // constructor for data after cluster finding
                 StFtpcPoint(Double_t *x, Int_t row);           // constructor which take an arbitrary point as input
  virtual       ~StFtpcPoint();                                 // destructor

  // coordinate transformations
  void TransformFtpc2Global();
  void TransformGlobal2Ftpc();

  virtual Int_t  WriteCluster();                                // writes cluster to disc
  virtual Int_t  ToTable(fcl_fppoint_st *point_st);             // writes cluster to STAF table
  
  // getter
  TVector3 GetCoord()  { return mCoord;    }
  TVector3 GetError()  { return mError;    }
  
  Double_t GetX()          const { return mCoord.X();   }
  Double_t GetY()          const { return mCoord.Y();   }
  Double_t GetZ()          const { return mCoord.Z();   }
  Double_t GetRadius()     const { return TMath::Sqrt(mCoord.X()*mCoord.X() + mCoord.Y()*mCoord.Y()); }
  Double_t GetXerr()       const { return mError.X();   }
  Double_t GetYerr()       const { return mError.Y();   }
  Double_t GetZerr()       const { return mError.Z();   }
  Double_t GetSigmaPhi()   const { return mSigmaPhi;    }
  Double_t GetSigmaR()     const { return mSigmaR;      }
  
  StFtpcTrack *GetTrack(TObjArray *tracks) const;
         void  SetTrackedFlag(Bool_t tracked);
       Bool_t  GetTrackedFlag();
         void  SetGlobalFlag(Bool_t global);
       Bool_t  GetGlobalFlag();
         void  SetUnusableForTrackingFlag(Bool_t global);
       Bool_t  GetUnusableForTrackingFlag();

  Bool_t   IsUsable();
  Bool_t   IsUnusable();
  Bool_t   IsInGlobalCoord()  { return GetGlobalFlag();  }
  Bool_t   GetUsage()         { return GetTrackedFlag(); }
  Int_t    GetHitNumber()     const { return mHitNumber;       }
  Int_t    GetNextHitNumber() const { return mNextHitNumber;   }
  Int_t    GetTrackNumber()   const { return mTrackNumber;     }
  Long_t   GetPadRow()        const { return mPadRow;          }
  Long_t   GetSector()        const { return mSector;          }
  Long_t   GetNumberPads()    const { return mNumberPads;      }
  Long_t   GetNumberBins()    const { return mNumberBins;      }
  Long_t   GetMaxADC()        const { return mMaxADC;          }
  Long_t   GetCharge()        const { return mCharge;          }
  Long_t   GetFlags()         const { return mFlags;           }
  
  Double_t GetXPrimResidual()     const { return mXPrimResidual;       }
  Double_t GetYPrimResidual()     const { return mYPrimResidual;       }
  Double_t GetRPrimResidual()     const { return mRPrimResidual;       }
  Double_t GetPhiPrimResidual()   const { return mPhiPrimResidual;     }
  Double_t GetXGlobResidual()     const { return mXGlobResidual;       }
  Double_t GetYGlobResidual()     const { return mYGlobResidual;       }
  Double_t GetRGlobResidual()     const { return mRGlobResidual;       }
  Double_t GetPhiGlobResidual()   const { return mPhiGlobResidual;     }

  // setter  
  void    SetX(Double_t f)        {     mCoord.SetX(f); }
  void    SetY(Double_t f)        {     mCoord.SetY(f); } 
  void    SetZ(Double_t f)        {     mCoord.SetZ(f); }
  void    SetXerr(Double_t f)     {     mError.SetX(f); }
  void    SetYerr(Double_t f)     {     mError.SetY(f); }
  void    SetZerr(Double_t f)     {     mError.SetZ(f); }
  
  void    SetGlobalCoord(Bool_t f)  {    SetGlobalFlag(f);  }
  void    SetUsage(Bool_t f)        {   SetTrackedFlag(f);  }
  void    SetHitNumber(Int_t f)     {     mHitNumber =  f;  }
  void    SetNextHitNumber(Int_t f) { mNextHitNumber =  f;  }
  void    SetTrackNumber(Int_t f)   {   mTrackNumber =  f;  }
  void    SetPadRow(Long_t f)       {        mPadRow =  f;  }
  void    SetSector(Long_t f)       {        mSector =  f;  }
  void    SetNumberPads(Long_t f)   {    mNumberPads =  f;  }
  void    SetNumberBins(Long_t f)   {    mNumberBins =  f;  }
  void    SetMaxADC(Long_t f)       {        mMaxADC =  f;  }
  void    SetCharge(Long_t f)       {        mCharge =  f;  }
  void    SetFlags(Long_t f)        {         mFlags =  f;  }
  void    SetSigmaPhi(Double_t f)   {      mSigmaPhi =  f;  }
  void    SetSigmaR(Double_t f)     {        mSigmaR =  f;  }
  
  void    SetResidualsToZero();
  void    SetXPrimResidual(Double_t f)  {      mXPrimResidual = f;  }
  void    SetYPrimResidual(Double_t f)  {      mYPrimResidual = f;  }
  void    SetRPrimResidual(Double_t f)  {      mRPrimResidual = f;  }
  void    SetPhiPrimResidual(Double_t f){    mPhiPrimResidual = f;  }
  void    SetXGlobResidual(Double_t f)  {      mXGlobResidual = f;  }
  void    SetYGlobResidual(Double_t f)  {      mYGlobResidual = f;  }
  void    SetRGlobResidual(Double_t f)  {      mRGlobResidual = f;  }
  void    SetPhiGlobResidual(Double_t f){    mPhiGlobResidual = f;  }
  
  ClassDef(StFtpcPoint, 1)   //Ftpc point class
};


inline void StFtpcPoint::SetResidualsToZero()
{
  // Sets all residuals to 0.

  SetXPrimResidual(0.);
  SetYPrimResidual(0.);
  SetRPrimResidual(0.);
  SetPhiPrimResidual(0.);
  SetXGlobResidual(0.);
  SetYGlobResidual(0.);
  SetRGlobResidual(0.);
  SetPhiGlobResidual(0.);

  return;
}


inline StFtpcTrack *StFtpcPoint::GetTrack(TObjArray *tracks) const
{
  // Returns the pointer to the track to which this hit belongs.

  return (StFtpcTrack*)tracks->At(this->GetTrackNumber());
}


inline void StFtpcPoint::SetTrackedFlag(Bool_t tracked) 
{
  // Sets flag, if the cluster was used for tracking.
  // This has to be done due to consistency with the point bank.

  Long_t old_flag = GetFlags();
  SetFlags((old_flag & 0xFFFFFFDF) | ((Long_t)tracked*32));
}


inline Bool_t StFtpcPoint::GetTrackedFlag()
{
  // Returns true, if 'tracked flag' is set, otherwise returns false.

  return (Bool_t)(GetFlags() & (Long_t)32);
}


inline void StFtpcPoint::SetGlobalFlag(Bool_t global) 
{
  // Sets flag, if the cluster is measured in global coordinates.

  Long_t old_flag = GetFlags();
  SetFlags((old_flag & 0xFFFFFFAF) | ((Long_t)global*64));
}


inline Bool_t StFtpcPoint::GetGlobalFlag()
{
  // Returns true, if 'global flag' is set, otherwise returns false.

  return (Bool_t)(GetFlags() & (Long_t)64);
}


inline void StFtpcPoint::SetUnusableForTrackingFlag(Bool_t global) 
{
  // Sets flag, if the cluster DOES NOT pass all quality criteria to be used for tracking.

  Long_t old_flag = GetFlags();
  SetFlags((old_flag & 0xFFFFFFAF) | ((Long_t)global*128));
}


inline Bool_t StFtpcPoint::GetUnusableForTrackingFlag()
{
  // Returns true, if 'UnusableForTracking flag' is set, otherwise returns false.

  return (Bool_t)(GetFlags() & (Long_t)128);
}


inline Bool_t StFtpcPoint::IsUsable()
{
  // Returns true, if 'UsableForTracking flag' and 'tracked flag' is set, otherwise returns false.
    
  return (Bool_t)((!GetTrackedFlag()) && !(GetUnusableForTrackingFlag()));
}


inline Bool_t StFtpcPoint::IsUnusable()
{
  // Returns true, if 'UsableForTracking flag' and 'tracked flag' is set, otherwise returns false.
    
  return (Bool_t)(GetTrackedFlag() || GetUnusableForTrackingFlag());
}

#endif
