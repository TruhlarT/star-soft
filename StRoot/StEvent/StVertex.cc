/***************************************************************************
 *
 * $Id: StVertex.cc,v 1.2 1999/01/15 22:54:22 wenaus Exp $
 *
 * Author: Thomas Ullrich, Jan 1999
 *
 * History:
 * 15/01/1999 T. Wenaus  Add table-based constructor
 ***************************************************************************
 *
 * Description:
 *
 ***************************************************************************
 *
 * $Log: StVertex.cc,v $
 * Revision 1.2  1999/01/15 22:54:22  wenaus
 * version with constructors for table-based loading
 *
 **************************************************************************/
#include "StEvent/StVertex.hh"

static const char rcsid[] = "$Id: StVertex.cc,v 1.2 1999/01/15 22:54:22 wenaus Exp $";

StVertex::StVertex()
{
    mType = undefined;                           
    mParent = 0;                
    mQualityBitmask = 0;        
    mChiSquared = 0;            
}

StVertex::StVertex(dst_vertex_st* vtx)
{
  mPosition.setX(vtx->x);
  mPosition.setY(vtx->y);
  mPosition.setZ(vtx->z);
  mPositionError.setX(vtx->sigma[0]);
  mPositionError.setY(vtx->sigma[1]);
  mPositionError.setZ(vtx->sigma[2]);
  mChiSquared = vtx->pchi2;
  mQualityBitmask = vtx->iflag;
}

StVertex::~StVertex() { /* noop */}


int StVertex::operator==(const StVertex& v) const
{
    return mType == v.mType &&mPosition == v.mPosition;
}

int StVertex::operator!=(const StVertex& v) const
{
    return !(v == *this);
}

void StVertex::setType(StVertexType val) { mType = val; }           

void StVertex::setParent(StGlobalTrack*  val) { mParent = val; }         

void StVertex::setPosition(const StThreeVector<float>& val) { mPosition = val; }       

void StVertex::setPositionError(const StThreeVector<float>& val) { mPositionError = val; }  

void StVertex::setQualityBitmask(unsigned long val) { mQualityBitmask = val; } 

void StVertex::setChiSquared(float val) { mChiSquared = val; }     
