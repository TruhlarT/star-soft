/***************************************************************************
 *
 * $Id: StMcRichHit.cc,v 2.3 2000/05/05 15:25:43 calderon Exp $
 * $Log: StMcRichHit.cc,v $
 * Revision 2.3  2000/05/05 15:25:43  calderon
 * Reduced dependencies and made constructors more efficient
 *
 * Revision 2.2  2000/04/18 00:55:14  calderon
 * added printout of local momentum to operator<<
 *
 * Revision 2.1  2000/03/06 18:05:21  calderon
 * 1) Modified SVT Hits storage scheme from layer-ladder-wafer to
 * barrel-ladder-wafer.
 * 2) Added Rich Hit class and collection, and links to them in other
 * classes.
 *
 *
 **************************************************************************/
#include "StMcRichHit.hh"
#include "StMcTrack.hh"
#include "tables/St_g2t_rch_hit_Table.h"

static const char rcsid[] = "$Id: StMcRichHit.cc,v 2.3 2000/05/05 15:25:43 calderon Exp $";

StMemoryPool StMcRichHit::mPool(sizeof(StMcRichHit));

StMcRichHit::StMcRichHit() { /* noop */ };

StMcRichHit::StMcRichHit(const StThreeVectorF& x,const StThreeVectorF& p,
		       const float de, const float ds,
		       StMcTrack* parent)  : StMcHit(x, p, de, ds, parent)
{ /* noop */ }


StMcRichHit::StMcRichHit(g2t_rch_hit_st* pt)
: StMcHit(StThreeVectorF(pt->x[0], pt->x[1], pt->x[2]),
	  StThreeVectorF(pt->p[0], pt->p[1], pt->p[2]),
	  pt->de,
	  0,
	  0),
  mVolumeId(pt->volume_id),
  mTof(pt->tof)
{/* noop */ }

StMcRichHit::~StMcRichHit() {/* noop */}

ostream&  operator<<(ostream& os, const StMcRichHit& h)
{
    os << "Position       : " << h.position() << endl; 
    os << "Local Momentum : " << h.localMomentum()    << endl;
    os << "Pad            : " << h.pad()    << endl;
    os << "Row            : " << h.row()   << endl;
    os << "T. of Flight   : " << h.tof()   << endl;
    return os;
}
