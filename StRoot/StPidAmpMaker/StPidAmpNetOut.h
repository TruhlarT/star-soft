/***************************************************************************
 *
 * $Id: StPidAmpNetOut.h,v 1.1 2000/03/09 17:48:34 aihong Exp $
 *
 * Author: Aihong Tang & Richard Witt (FORTRAN Version),Kent State U.
 *         Send questions to aihong@cnr.physics.kent.edu
 ***************************************************************************
 *
 * Description:part of StPidAmpMaker package
 *             This is the object to be written out.
 *             It contains: (if all filled)
 *             1.Parameters for describing the band
 *             2.Parameters for describing the amplitude
 *             3.Parameters for describing the resolution
 *             4.Parameters for calibration
 *             5.Geant ID for the net type
 ***************************************************************************
 *
 * $Log: StPidAmpNetOut.h,v $
 * Revision 1.1  2000/03/09 17:48:34  aihong
 * Initial revision
 *
 **************************************************************************/

//this class do not implement STL, so be careful with index, bounding, etc.
 
#ifndef ROOT_StPidAmpNetOut
#define ROOT_StPidAmpNetOut

#ifndef ROOT_TObject
//*KEEP, TObject.
#include "TObject.h"
//*KEND.
#endif 

#include "TNamed.h"
#include "TArrayD.h"

class StPidAmpNetOut : public TNamed {

 public:

  StPidAmpNetOut();
  StPidAmpNetOut(const StPidAmpNetOut&);
  StPidAmpNetOut(Text_t* name,Text_t* title, Int_t id,TArrayD bandParAry, TArrayD ampParAry, TArrayD linrParAry); 
  virtual  ~StPidAmpNetOut();
  void SetBandParArray(TArrayD bandParAry);
  void SetAmpParArray(TArrayD ampParAry);
  void SetResoParArray(TArrayD linrAry);
  void SetGeantID(Int_t id);
  void SetCalibConst(Double_t cal);


  TArrayD   GetBandParArray();
  TArrayD   GetAmpParArray();
  TArrayD   GetResoParArray();

  Int_t     GetNBandPars();
  Int_t     GetNAmpPars();
  Int_t     GetNResoPars();

  Int_t     GetGeantID();
  Double_t  GetCalibConst();

 private:

  Int_t    mGeantID;
  Double_t mCalibConst;

  TArrayD mBandParArray;
  TArrayD mAmpParArray;
  TArrayD mResoParArray;

 ClassDef(StPidAmpNetOut,1)

   };

#endif

