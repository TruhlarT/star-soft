/***************************************************************************
 *
 * $Id: StTriggerDetectorCollection.h,v 1.5 1999/04/30 13:16:30 fisyak Exp $
 *
 * Author: Thomas Ullrich, Jan 1999
 ***************************************************************************
 *
 * Description:
 *
 ***************************************************************************
 *
 * $Log: StTriggerDetectorCollection.h,v $
 * Revision 1.5  1999/04/30 13:16:30  fisyak
 * add StArray for StRootEvent
 *
 * Revision 1.5  1999/04/30 13:16:30  fisyak
 * add StArray for StRootEvent
 *
 * Revision 1.4  1999/04/28 22:27:39  fisyak
 * New version with pointer instead referencies
 *
 * Revision 1.2  1999/01/15 22:54:14  wenaus
 * version with constructors for table-based loading
 *
 **************************************************************************/
#ifndef StTriggerDetectorCollection_hh
#define StTriggerDetectorCollection_hh
#include "StObject.h"
#include "StZdcSummary.h"
#include "StVpdSummary.h"
#include "StZdcSegment.h"
#include "StVpdCounter.h"
#include "StMwcSector.h"
#include "StCtbCounter.h"
#include "StCtbCounter.h"
#include "StMwcSector.h"
#include "StVpdCounter.h"
#include "StZdcSegment.h"

class StTriggerDetectorCollection : public StObject {
public:
    StTriggerDetectorCollection();
    ~StTriggerDetectorCollection();
    // StTriggerDetectorCollection(const StTriggerDetectorCollection&);
    // const StTriggerDetectorCollection & operator=(const StTriggerDetectorCollection&);
    
    StVecPtrCtbCounter& ctbCounters();
    StVecPtrMwcSector&  mwcSectors();
    StVecPtrVpdCounter& vpdCounters();
    StVecPtrZdcSegment& zdcSegments();
    StZdcSummary&    zdcSummary();
    StVecPtrCtbCounter mCtbCounters;
    StVecPtrMwcSector  mMwcSectors;
    StVecPtrVpdCounter mVpdCounters;
    StVecPtrZdcSegment mZdcSegments;
    StVpdSummary    mVpdSummary;
    StZdcSummary    mZdcSummary;
    StVecPtrZdcSegment *mZdcSegments;
    StVpdSummary       *mVpdSummary;
    StZdcSummary       *mZdcSummary;
inline StVecPtrCtbCounter& StTriggerDetectorCollection::ctbCounters() { return mCtbCounters; }
};
inline StVecPtrMwcSector&  StTriggerDetectorCollection::mwcSectors() { return mMwcSectors; }
inline StVecPtrCtbCounter& StTriggerDetectorCollection::ctbCounters() { return *mCtbCounters; }
inline StVecPtrVpdCounter& StTriggerDetectorCollection::vpdCounters() { return mVpdCounters; }
inline StVecPtrMwcSector&  StTriggerDetectorCollection::mwcSectors() { return *mMwcSectors; }
inline StVecPtrZdcSegment& StTriggerDetectorCollection::zdcSegments() { return mZdcSegments; }
inline StVecPtrVpdCounter& StTriggerDetectorCollection::vpdCounters() { return *mVpdCounters; }
inline StZdcSummary& StTriggerDetectorCollection::zdcSummary() { return mZdcSummary; }
inline StVecPtrZdcSegment& StTriggerDetectorCollection::zdcSegments() { return *mZdcSegments; }
inline StVpdSummary& StTriggerDetectorCollection::vpdSummary() { return mVpdSummary; }
inline StZdcSummary& StTriggerDetectorCollection::zdcSummary() { return *mZdcSummary; }

inline StVpdSummary& StTriggerDetectorCollection::vpdSummary() { return *mVpdSummary; }

#endif
