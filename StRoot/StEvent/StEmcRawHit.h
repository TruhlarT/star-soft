/***************************************************************************
 *
 * $Id: StEmcRawHit.h,v 2.4 2001/03/24 03:34:46 perev Exp $
 *
 * Author: Akio Ogawa, Jan 2000
 ***************************************************************************
 *
 * Description: 
 *
 ***************************************************************************
 *
 * $Log: StEmcRawHit.h,v $
 * Revision 2.4  2001/03/24 03:34:46  perev
 * clone() -> clone() const
 *
 * Revision 2.3  2000/07/28 19:49:28  akio
 * Change in Detector Id for Endcap SMD
 *
 * Revision 2.2  2000/05/22 19:21:54  akio
 * Bug fix, add delta into EMcPoint, wider bits for Eta in RawHit
 *
 * Revision 2.1  2000/02/23 17:34:14  ullrich
 * Initial Revision
 *
 **************************************************************************/
#ifndef StEmcRawHit_hh
#define StEmcRawHit_hh

#include "StObject.h"
#include "StEnumerations.h"

class StEmcRawHit : public StObject {
public:
  StEmcRawHit();
  StEmcRawHit(StDetectorId, UInt_t, UInt_t, UInt_t, UInt_t);
  StEmcRawHit(StDetectorId, UInt_t, UInt_t, UInt_t, UInt_t, Float_t);
  StEmcRawHit(const StEmcRawHit&);
  // StEmcRawHit& operator=(const StEmcRawHit&); use default
  ~StEmcRawHit();
  
  StDetectorId detector() const;        
  UInt_t    module() const;        
  UInt_t    eta() const;        
  Int_t     sub() const;        
  UInt_t    calibrationType() const;
  UInt_t    adc() const;        
  Float_t   energy() const;

  void setId(StDetectorId, UInt_t, UInt_t, UInt_t);
  void setCalibrationType(const UInt_t);
  void setAdc(const UInt_t);
  void setEnergy(const Float_t);
  
protected:
  UInt_t    bits(UInt_t, UInt_t) const;        
  
protected:
  UInt_t    mId;
  UInt_t    mAdc;        
  Float_t   mEnergy;
  
  StObject* clone() const;
  ClassDef(StEmcRawHit,1)  
};
#endif


