/***************************************************************************
 *
 * $Id: StTpcHitCollection.hh,v 1.2 1999/01/15 22:54:00 wenaus Exp $
 *
 * Author: Thomas Ullrich, Jan 1999
 ***************************************************************************
 *
 * Description:
 *
 ***************************************************************************
 *
 * $Log: StTpcHitCollection.hh,v $
 * Revision 1.2  1999/01/15 22:54:00  wenaus
 * version with constructors for table-based loading
 *
 * Revision 1.2  1999/01/15 22:54:00  wenaus
 * version with constructors for table-based loading
 *
#ifndef StTpcHitCollection_hh
#define StTpcHitCollection_hh
using namespace std;
#include "StEvent/StTpcHit.hh"
#include <vector>

#ifdef ST_NO_TEMPLATE_DEF_ARGS
typedef vector<StTpcHit*, allocator<StTpcHit*> >            StTpcHitCollection;
typedef vector<StTpcHit*, allocator<StTpcHit*> >::iterator  StTpcHitIterator;
#else
typedef vector<StTpcHit*>            StTpcHitCollection;
typedef vector<StTpcHit*>::iterator  StTpcHitIterator;
#endif

#endif
