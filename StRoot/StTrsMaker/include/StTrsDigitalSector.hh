/***************************************************************************
 *
 * $Id: StTrsDigitalSector.hh,v 1.6 2000/01/10 23:11:31 lasiuk Exp $
 *
 * Author: bl prelim
 ***************************************************************************
 *
 * Description: Store the digital information in a space
 *              efficient manner:
 * Data:
 * TimeBin   0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15...
 * ADC Vaue  0  0  0  5  9  4  0  0  0  0  7  9  3  0  0  1...
 *
 * will be stored as an array of short in a compressed manner
 * where the ADC values remain and the number of zeros are compressed
 * and stored as a negative number.  The data above will be stored
 * as:
 *
 *           -3 5 9 4 -4 7 9 3 -2 1....
 *           
 *  This will be the format coming from the DigitalSignalGenerator
 *  NOTE: Encapsulation is broken in this class to allow easy
 *        access to the data via the TPC data reader interface!
 ***************************************************************************
 *
 * $Log: StTrsDigitalSector.hh,v $
 * Revision 1.6  2000/01/10 23:11:31  lasiuk
 * Include MACROS for compatibility with SUN CC5.0
 *
 * Revision 1.5  1999/11/05 22:17:04  calderon
 * Made private copy constructor and operator= in StTrsDigitalSector.
 * Renamed DigitalSignalGenerators: Fast -> Old, Parameterized -> Fast
 * and use new "Fast" as default.
 * Added StTrsDetectorReader and StTrsZeroSuppressedReader for DAQ type
 * data access.
 *
 * Revision 1.4  1999/10/19 21:17:57  calderon
 * New format of data for the Digital Sector without mZeros.
 * Member functions modified accordingly.  Not tested yet, but
 * committed because cons still can't handle changes in the
 * TRS header files.
 *
 * Revision 1.3  1999/10/11 23:55:10  calderon
 * Version with Database Access and persistent file.
 * Not fully tested due to problems with cons, it
 * doesn't find the local files at compile time.
 * Yuri suggests forcing commit to work directly with
 * files in repository.
 *
 * Revision 1.2  1999/01/22 08:06:03  lasiuk
 * use unsigned char for compatibilty with interface.
 * requires use of two arrays...ugly but fine for now.
 * use of pair<>; values returned by pointer
 *
 * Revision 1.1  1999/01/18 10:23:42  lasiuk
 * initial Revision
 *
 *
 **************************************************************************/
#ifndef ST_TRS_DIGITAL_SECTOR_HH
#define ST_TRS_DIGITAL_SECTOR_HH

#include <vector>
#include <utility>
#if defined (__SUNPRO_CC) && __SUNPRO_CC >= 0x500
using std::vector;
#endif

#include "StTrsAnalogSignal.hh"
#include "StTpcGeometry.hh"

#include "StTpcPadCoordinate.hh"

#ifndef ST_NO_TEMPLATE_DEF_ARGS
typedef vector<unsigned char>      digitalTimeBins;
typedef vector<digitalTimeBins>    digitalPadRow;
typedef vector<digitalPadRow>      digitalSector;

typedef vector<unsigned char>::iterator digitalTimeBinIterator;
#else
typedef vector<unsigned char, allocator<unsigned char> >     digitalTimeBins;
typedef vector<digitalTimeBins, allocator<digitalTimeBins> > digitalPadRow;
typedef vector<digitalPadRow, allocator<digitalPadRow> >     digitalSector;

typedef vector<unsigned char, allocator<unsigned char> >::iterator digitalTimeBinIterator;
#endif

typedef digitalPadRow::iterator                  digitalPadRowIterator;
typedef digitalSector::iterator                  digitalRowIterator;

class StTrsDigitalSector {
public:
    StTrsDigitalSector(StTpcGeometry*);
    ~StTrsDigitalSector();
    

    // access functions
    digitalTimeBins*   timeBinsOfRowAndPad(int, int);
    digitalPadRow*     padsOfRow(int);
    digitalSector*     rows();

    int  numberOfRows()             const;
    int  numberOfPadsInRow(int)     const;
    int  numberOfTimeBins(int, int) const;
    
    // Adding
    void clear();

    void assignTimeBins(int, int, digitalTimeBins*);
    void assignTimeBins(StTpcPadCoordinate&, digitalTimeBins*);
    // When writing, make sure we don't carry unnecessary zeros:
    int cleanup();
public:
    digitalSector mData;
//     digitalSector mZeros;
private:
    StTrsDigitalSector(const StTrsDigitalSector&);
    StTrsDigitalSector& operator=(const StTrsDigitalSector&);

};
inline digitalTimeBins* StTrsDigitalSector::timeBinsOfRowAndPad(int rowN, int padN)
{
    return (&mData[(rowN-1)][(padN-1)]);
}
inline digitalPadRow* StTrsDigitalSector::padsOfRow(int rowN)
{
    return(&mData[(rowN-1)]);
}
inline digitalSector* StTrsDigitalSector::rows()
{
    return (&mData);
}
inline int StTrsDigitalSector::numberOfRows() const { return mData.size();}
inline int StTrsDigitalSector::numberOfPadsInRow(int rowN) const { return mData[(rowN-1)].size();}
inline int StTrsDigitalSector::numberOfTimeBins(int rowN, int padN) const { return mData[(rowN-1)][(padN-1)].size();}
#endif
