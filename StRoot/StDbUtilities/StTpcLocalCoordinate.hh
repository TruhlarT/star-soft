/*********************************************************************
 *
 * $Id: StTpcLocalCoordinate.hh,v 1.3 2003/09/02 17:57:51 perev Exp $
 *
 * Author: brian May 20, 1998
 *
 **********************************************************************
 *
 * Description:  Raw data information along with access functions
 *
 **********************************************************************
 *
 * $Log: StTpcLocalCoordinate.hh,v $
 * Revision 1.3  2003/09/02 17:57:51  perev
 * gcc 3.2 updates + WarnOff
 *
 * Revision 1.2  2000/02/02 23:01:38  calderon
 * Changes for CC5
 * Tests withs StTpcDb still going.
 *
 * Revision 1.1  1999/11/19 19:01:08  calderon
 * First version of files for StDbUtilities.
 * Note: this package uses StTpcDb.
 * There are some parameters
 * that are not yet kept in StTpcDb.  When StTpcDb has them, the code
 * will be changed to use them from StTpcDb.
 * There are no Ftpc or Svt Coordinate transformations in here yet.
 *
 * Revision 1.4  1999/10/25 18:38:29  calderon
 * changed mPos and pos() to mPosition and position() to
 * be compatible with StEvent/StMcEvent.
 *
 * Revision 1.3  1998/11/16 19:40:19  lasiuk
 * constructors do not use reference for doubles
 *
 * Revision 1.2  1998/11/13 21:29:29  lasiuk
 * allow setting coordinates individually
 *
 * Revision 1.1  1998/11/10 17:12:06  fisyak
 * Put Brian trs versin into StRoot
 *
 * Revision 1.2  1998/11/01 16:21:03  lasiuk
 * remove 'St' from variable declarations
 * add set functions in local Coordinates
 *
 * Revision 1.1  1998/05/21 21:27:38  lasiuk
 * Initial revision
 *
 *
 **********************************************************************/
#ifndef ST_TPC_LOCAL_COORDINATE_HH
#define ST_TPC_LOCAL_COORDINATE_HH

#include <Stiostream.h>


#include "StThreeVector.hh"

class StTpcLocalCoordinate
{
public:
    StTpcLocalCoordinate();
    StTpcLocalCoordinate(const double, const double, const double);
    StTpcLocalCoordinate(const StThreeVector<double>&);

    virtual ~StTpcLocalCoordinate();
    //StTpcLocalCoordinate(const StTpcLocalCoordinate&);
    //StTpcLocalCoordinate& operator=(const StTpcLocalCoordinate&);
    
    int operator==(const StTpcLocalCoordinate&) const;
    int operator!=(const StTpcLocalCoordinate&) const;
    // access functions provided by StThreeVector
    const StThreeVector<double>& position()  const;
    void setPosition(const StThreeVector<double>&);
    StThreeVector<double>& position();

protected:
    StThreeVector<double> mPosition;

};

inline const StThreeVector<double>& StTpcLocalCoordinate::position() const { return(mPosition); }
inline StThreeVector<double>& StTpcLocalCoordinate::position() { return(mPosition); }
inline void StTpcLocalCoordinate::setPosition(const StThreeVector<double>& val) { mPosition = val; }

// Non-member
ostream& operator<<(ostream&, const StTpcLocalCoordinate&);
#endif
