/***************************************************************************
 *
 * $Id: StTrigger.cxx,v 1.2 1999/02/10 02:17:36 fisyak Exp $
 *
 * Author: Thomas Ullrich, Jan 1999
 ***************************************************************************
 *
 * Description:
 *
 ***************************************************************************
 *
 * $Log: StTrigger.cxx,v $
 * Revision 1.2  1999/02/10 02:17:36  fisyak
 * Merging with new Torre stuff
 *
 * Revision 1.4  1999/04/28 22:27:38  fisyak
 * New version with pointer instead referencies
 *
 * Revision 1.2  1999/01/15 22:54:11  wenaus
 * version with constructors for table-based loading
 *
 **************************************************************************/
#include "StTrigger.h"
#ifdef __ROOT__

static const Char_t rcsid[] = "$Id: StTrigger.cxx,v 1.2 1999/02/10 02:17:36 fisyak Exp $";
#endif

ClassImp(StTrigger)

StTrigger::StTrigger()
{
    mTriggerActionWord = 0;
    mTriggerWord = 0;
}

StTrigger::StTrigger(UShort_t aw, UShort_t w)
{
    mTriggerActionWord = aw;
    mTriggerWord = w;
}

StTrigger::~StTrigger() { /* noop */}

Int_t StTrigger::operator==(const StTrigger& t) const
{
    return mTriggerActionWord == t.mTriggerActionWord &&
	mTriggerWord == t.mTriggerWord;
}

Int_t StTrigger::operator!=(const StTrigger& t) const
{
    return !(t == *this);
}

void StTrigger::setTriggerActionWord(UShort_t val) { mTriggerActionWord = val; }

void StTrigger::setTriggerWord(UShort_t val) { mTriggerActionWord = val; }
