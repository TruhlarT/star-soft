/***************************************************************************
 *
 * $Id: StTrackDetectorInfo.cxx,v 2.9 2004/07/15 16:36:26 ullrich Exp $
 *
 * Author: Thomas Ullrich, Sep 1999
 ***************************************************************************
 *
 * Description:
 *
 ***************************************************************************
 *
 * $Log: StTrackDetectorInfo.cxx,v $
 * Revision 2.9  2004/07/15 16:36:26  ullrich
 * Removed all clone() declerations and definitions. Use StObject::clone() only.
 *
 * Revision 2.8  2003/10/30 20:07:32  perev
 * Check of quality added
 *
 * Revision 2.7  2001/04/05 04:00:58  ullrich
 * Replaced all (U)Long_t by (U)Int_t and all redundant ROOT typedefs.
 *
 * Revision 2.6  2001/03/24 03:35:00  perev
 * clone() -> clone() const
 *
 * Revision 2.5  2000/04/20 13:29:58  ullrich
 * Added new methods and removed inconsistencies in numberOfPoints().
 *
 * Revision 2.4  2000/01/20 14:43:07  ullrich
 * Fixed bug in numberOfPoints(). Sum was wrong.
 *
 * Revision 2.3  1999/11/01 12:45:09  ullrich
 * Modified unpacking of point counter
 *
 * Revision 2.2  1999/10/28 22:27:27  ullrich
 * Adapted new StArray version. First version to compile on Linux and Sun.
 *
 * Revision 2.1  1999/10/13 19:45:39  ullrich
 * Initial Revision
 *
 **************************************************************************/
#include "StTrackDetectorInfo.h"
#include "StFunctional.h"
#include "StHit.h"
#include "tables/St_dst_track_Table.h"

ClassImp(StTrackDetectorInfo)

static const char rcsid[] = "$Id: StTrackDetectorInfo.cxx,v 2.9 2004/07/15 16:36:26 ullrich Exp $";

StTrackDetectorInfo::StTrackDetectorInfo() : mNumberOfPoints(0)
{ /* noop */ }

StTrackDetectorInfo::StTrackDetectorInfo(const dst_track_st& t) :
    mFirstPoint(t.x_first),  mLastPoint(t.x_last), mNumberOfPoints(t.n_point)
{ /* noop */ }

StTrackDetectorInfo::~StTrackDetectorInfo() { /* noop */ }

const StThreeVectorF&
StTrackDetectorInfo::firstPoint() const { return mFirstPoint; }

const StThreeVectorF&
StTrackDetectorInfo::lastPoint() const { return mLastPoint; }

unsigned short
StTrackDetectorInfo::numberOfPoints() const
{
    return (numberOfPoints(kTpcId) +
            numberOfPoints(kSvtId) +
            numberOfPoints(kSsdId));
}

unsigned short
StTrackDetectorInfo::numberOfPoints(StDetectorId det) const
{
    // 1*tpc + 1000*svt + 10000*ssd (Helen/Spiros Oct 29, 1999)
    switch (det) {
    case kFtpcWestId:
    case kFtpcEastId:
    case kTpcId:
        return mNumberOfPoints%1000;
        break;
    case kSvtId:
        return (mNumberOfPoints%10000)/1000;
        break;
    case kSsdId:
        return mNumberOfPoints/10000;
        break;
    default:
        return 0;
    }
}

unsigned short
StTrackDetectorInfo::numberOfReferencedPoints() const
{
    return static_cast<unsigned short>(mHits.size());
}

unsigned short
StTrackDetectorInfo::numberOfReferencedPoints(StDetectorId id) const
{
    unsigned short count = 0;
    for (StPtrVecHitConstIterator iter=mHits.begin(); iter != mHits.end(); iter++)
        if ((*iter)->detector() == id) count++;
    return count;
}

StPtrVecHit
StTrackDetectorInfo::hits(StHitFilter& filter) const
{
    StPtrVecHit vec;
    for (StPtrVecHitConstIterator iter=mHits.begin(); iter != mHits.end(); iter++)
        if (filter(*iter)) vec.push_back(*iter);
    return vec;
}

StPtrVecHit
StTrackDetectorInfo::hits(StDetectorId id) const
{
    StPtrVecHit vec;
    for (StPtrVecHitConstIterator iter=mHits.begin(); iter != mHits.end(); iter++)
        if ((*iter)->detector() == id) vec.push_back(*iter);
    return vec;
}

StPtrVecHit&
StTrackDetectorInfo::hits() { return mHits; }

const StPtrVecHit&
StTrackDetectorInfo::hits() const { return mHits; }

void
StTrackDetectorInfo::setFirstPoint(const StThreeVectorF& val)
{
    mFirstPoint = val;
}

void
StTrackDetectorInfo::setLastPoint(const StThreeVectorF& val)
{
    mLastPoint = val;
}

void
StTrackDetectorInfo::setNumberOfPoints(unsigned short val)
{
    mNumberOfPoints = val;
}

void
StTrackDetectorInfo::addHit(StHit* hit)
{
    if (hit) {
        mHits.push_back(hit);
        hit->setTrackReferenceCount(hit->trackReferenceCount()+1);
    }
}

void
StTrackDetectorInfo::removeHit(StHit*& hit)
{
    // carefull here: mHits.erase(&hit) is not save at all
    for (StPtrVecHitIterator iter=mHits.begin(); iter != mHits.end(); iter++) {
        if (*iter == hit) mHits.erase(iter);
        int i = hit->trackReferenceCount();
        hit->setTrackReferenceCount(i > 0 ? i-1 : 0);
    }
}
int  StTrackDetectorInfo::bad() const
{
   if(!mFirstPoint.valid()) return 1;
   if(!mLastPoint.valid() ) return 2;
   return 0;
}
