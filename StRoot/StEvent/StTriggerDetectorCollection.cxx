/***************************************************************************
 *
 * $Id: StTriggerDetectorCollection.cxx,v 2.4 2003/01/23 23:49:32 ullrich Exp $
 *
 * Author: Thomas Ullrich, Sep 1999
 ***************************************************************************
 *
 * Description:
 *
 ***************************************************************************
 *
 * $Log: StTriggerDetectorCollection.cxx,v $
 * Revision 2.4  2003/01/23 23:49:32  ullrich
 * Feeding now tables to BBC instance as well.
 *
 * Revision 2.3  2002/02/20 03:12:15  ullrich
 * Added EMC trigger.
 *
 * Revision 2.2  2002/01/03 20:59:33  ullrich
 * Added BBC and FPD.
 *
 * Revision 2.1  1999/10/28 22:27:58  ullrich
 * Adapted new StArray version. First version to compile on Linux and Sun.
 *
 * Revision 2.0  1999/10/12 18:43:18  ullrich
 * Completely Revised for New Version
 *
 **************************************************************************/
#include "StTriggerDetectorCollection.h"
#include "tables/St_dst_TrgDet_Table.h"

static const char rcsid[] = "$Id: StTriggerDetectorCollection.cxx,v 2.4 2003/01/23 23:49:32 ullrich Exp $";

ClassImp(StTriggerDetectorCollection)

StTriggerDetectorCollection::StTriggerDetectorCollection() {/* noop */}

StTriggerDetectorCollection::StTriggerDetectorCollection(const dst_TrgDet_st& t) :
    mCtb(t), mMwc(t), mVpd(t), mZdc(t), mEmc(t), mBbc(t) {/* noop */}

StTriggerDetectorCollection::~StTriggerDetectorCollection() {/* noop */}

StBbcTriggerDetector&
StTriggerDetectorCollection::bbc() { return mBbc; }

const StBbcTriggerDetector&
StTriggerDetectorCollection::bbc() const { return mBbc; }

StCtbTriggerDetector&
StTriggerDetectorCollection::ctb() { return mCtb; }

const StCtbTriggerDetector&
StTriggerDetectorCollection::ctb() const { return mCtb; }

StMwcTriggerDetector&
StTriggerDetectorCollection::mwc() { return mMwc; }

const StMwcTriggerDetector&
StTriggerDetectorCollection::mwc() const { return mMwc; }

StVpdTriggerDetector&
StTriggerDetectorCollection::vpd() { return mVpd; }

const StVpdTriggerDetector&
StTriggerDetectorCollection::vpd() const { return mVpd; }

StZdcTriggerDetector&
StTriggerDetectorCollection::zdc() { return mZdc; }

const StZdcTriggerDetector&
StTriggerDetectorCollection::zdc() const { return mZdc; }

StEmcTriggerDetector&
StTriggerDetectorCollection::emc() { return mEmc; }

const StEmcTriggerDetector&
StTriggerDetectorCollection::emc() const { return mEmc; }

