/***************************************************************************
 *
 * $Id: StBTofHit.cxx,v 2.3 2009/03/04 04:36:58 ullrich Exp $
 *
 * Author: Xin Dong, Nov 2008
 ***************************************************************************
 *
 * Description:
 *
 ***************************************************************************
 *
 * $Log: StBTofHit.cxx,v $
 * Revision 2.3  2009/03/04 04:36:58  ullrich
 * Added missing check for valid pointer to operator<<
 *
 * Revision 2.2  2009/01/15 00:46:25  ullrich
 * tray() now returns int.
 *
 * Revision 2.1  2008/12/22 20:30:57  ullrich
 * Initial Revision.
 *
 *
 **************************************************************************/
#include "StBTofHit.h"
#include "StTrack.h"

ClassImp(StBTofHit)

StBTofHit::StBTofHit()
{
    mTray             = 0;
    mModule           = 0;
    mCell             = 0;
    mLeadingEdgeTime  = 0.;
    mTrailingEdgeTime = 0.;

    mAssociatedTrack  = 0;
    mIdTruth          = 0;
    mQuality          = 0;
}

StBTofHit::~StBTofHit() {/* noop */}

int
StBTofHit::tray() const { return mTray; }

int
StBTofHit::module() const { return mModule; }

int
StBTofHit::cell() const { return mCell; }

double
StBTofHit::leadingEdgeTime() const { return mLeadingEdgeTime; }

double
StBTofHit::trailingEdgeTime() const { return mTrailingEdgeTime; }

double
StBTofHit::tot() const { return mTrailingEdgeTime - mLeadingEdgeTime; }

StTrack*
StBTofHit::associatedTrack() { return mAssociatedTrack; }

const StTrack*
StBTofHit::associatedTrack() const { return mAssociatedTrack; }

int
StBTofHit::idTruth() const { return mIdTruth; }

int
StBTofHit::qaTruth() const { return mQuality; }

void
StBTofHit::setTray(unsigned char trayId) { mTray = trayId; }

void
StBTofHit::setModule(unsigned char moduleId) { mModule = moduleId; }

void
StBTofHit::setCell(unsigned char cellId) { mCell = cellId; }

void
StBTofHit::setLeadingEdgeTime(double time) { mLeadingEdgeTime = time; }

void
StBTofHit::setTrailingEdgeTime(double time) { mTrailingEdgeTime = time; }

void
StBTofHit::setAssociatedTrack(StTrack* val) { mAssociatedTrack = val; }

void
StBTofHit::setIdTruth(int idtru,int qatru)
{
    if (qatru==0) qatru = (idtru>>16);
    idtru    = idtru&((1<<16)-1);
    mIdTruth = static_cast<UShort_t>(idtru);
    mQuality = static_cast<UShort_t>(qatru);
}

ostream&
operator<<(ostream &os, const StBTofHit& hit)
{
    os << " Tray:" << hit.tray() << "  Module:" << hit.module()
       << " Cell:" << hit.cell() << endl
       << " LeTime " << hit.leadingEdgeTime() 
       << " TeTime " << hit.trailingEdgeTime() << endl
       << " Track " << (hit.associatedTrack() ? hit.associatedTrack()->key() : 0) << endl
       << " IdTruth " << hit.idTruth() << " Quality " << hit.qaTruth() << endl;
    return os;
}
