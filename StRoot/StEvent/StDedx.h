/***************************************************************************
 *
 * $Id: StDedx.h,v 1.6 1999/09/24 01:23:00 fisyak Exp $
 *
 * Author: Thomas Ullrich, Jan 1999
 *
 * History:
 * 14/01/1999 T. Wenaus  Add table-based constructor
 *
 ***************************************************************************
 *
 * Description:
 *
 ***************************************************************************
 *
 * $Log: StDedx.h,v $
 * Revision 1.6  1999/09/24 01:23:00  fisyak
 * Reduced Include Path
 *
 * Revision 1.6  1999/09/24 01:23:00  fisyak
 * Reduced Include Path
 *
 * Revision 1.5  1999/04/30 13:16:26  fisyak
 * add StArray for StRootEvent
 *
 * Revision 1.4  1999/04/28 22:27:29  fisyak
 * New version with pointer instead referencies
 *
 * Revision 1.3  1999/01/30 23:03:10  wenaus
 * table load intfc change; include ref change
 *
 * Revision 1.2  1999/01/15 22:53:32  wenaus
 * version with constructors for table-based loading
 *
 **************************************************************************/
#ifndef StDedx_hh
#define StDedx_hh

#include "StObject.h"
#include "dst_dedx.h"

class StDedx : public StObject {
public:
    StDedx();
    ~StDedx();
    StDedx(dst_dedx_st*);
    // StDedx(const StDedx &right);      use default
    // const StDedx & operator=(const StDedx &right);
    
    UShort_t numberOfPointsUsed() const;
    Float_t          mean() const;
    Float_t          variance() const;
    ULong_t  status() const;

    void setNumberOfPointsUsed(UShort_t);
    void setMean(Float_t);
    void setVariance(Float_t);
    void setStatus(ULong_t);
    
protected:
    UShort_t mNumberOfPointsUsed;
    Float_t          mMean;
    Float_t          mVariance;
    ULong_t  mStatus;              
  ClassDef(StDedx,1)  //StDedx structure
};

inline UShort_t StDedx::numberOfPointsUsed() const { return mNumberOfPointsUsed; }

inline Float_t StDedx::mean() const { return mMean; }

inline Float_t StDedx::variance() const { return mVariance; }

inline ULong_t StDedx::status() const { return mStatus; }


#endif
