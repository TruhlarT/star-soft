/*****************************************************************
 *
 * $Id: StTpcDbElectronics.cc,v 1.2 1999/12/08 02:10:41 calderon Exp $
 *
 * Author: Manuel Calderon de la Barca Sanchez & Brian Lasiuk Sept 13, 1999
 *
 *****************************************************************
 * Description: Electronics parameters for TRS taken from DB for
 *              the STAR Main TPC              
 *
 *****************************************************************
 *
 * $Log: StTpcDbElectronics.cc,v $
 * Revision 1.2  1999/12/08 02:10:41  calderon
 * Modified to eliminate warnings on Linux.
 *
 * Revision 1.1  1999/10/11 23:55:20  calderon
 * Version with Database Access and persistent file.
 * Not fully tested due to problems with cons, it
 * doesn't find the local files at compile time.
 * Yuri suggests forcing commit to work directly with
 * files in repository.
 *
 ******************************************************************/
#ifdef __ROOT__
#include "SystemOfUnits.h"
#include "StTpcDbElectronics.hh"
//#include "StUtilities/StMessMgr.h"
#include "StTpcDb/StTpcDb.h"

StTpcElectronics* StTpcDbElectronics::mInstance = 0; // static data member

StTpcDbElectronics::StTpcDbElectronics() { /* nopt */ }

StTpcDbElectronics::StTpcDbElectronics(StTpcDb* globalDbPointer)
{
    gTpcDbPtr            = globalDbPointer;
    mNominalGain         = gTpcDbPtr->Electronics()->nominalGain();
    mSamplingFrequency   = gTpcDbPtr->Electronics()->samplingFrequency();
    mTZero               = gTpcDbPtr->Electronics()->tZero();
    mAdcConversion       = gTpcDbPtr->Electronics()->adcConversion();    
    mAdcConversionCharge = gTpcDbPtr->Electronics()->adcCharge();    
    mNumberOfTimeBins    = gTpcDbPtr->Electronics()->numberOfTimeBins();    
    mAveragePedestal     = static_cast<int>(gTpcDbPtr->Electronics()->averagePedestal());
    mShapingTime         = gTpcDbPtr->Electronics()->shapingTime();
    mTau                 = gTpcDbPtr->Electronics()->tau();

#ifndef ST_NO_NAMESPACES
    using namespace units;
#endif

    //Units Integrity
    mNominalGain         *= (millivolt)/(coulomb*1.e-15);  // mV/fC
    mSamplingFrequency   *= MHz;
    mTZero               *= microsecond;
    mAdcConversion       *= (millivolt);
    mAdcConversionCharge *= (coulomb*1.e-15);
    mShapingTime         *= nanosecond;
    mTau                 *= nanosecond;
}

StTpcElectronics*
StTpcDbElectronics::instance()
{
    if (!mInstance) {
#ifndef ST_NO_EXCEPTIONS
	throw invalid_argument("StTpcDbElectronics::getInstance(): Argument Missing!");
#else
	cerr << "StTpcDbElectronics::getInstance(): Argument Missing!" << endl;
	cerr << "No arguments for instantiantion" << endl;
	cerr << "Exiting..." << endl;
#endif
    }
    return mInstance;
}

StTpcElectronics*
StTpcDbElectronics::instance(StTpcDb* gTpcDbPtr)
{
    if (!mInstance) {
	mInstance = new StTpcDbElectronics(gTpcDbPtr);
    }
    else {
	cerr << "StTpcDbElectronics::getInstance()\a\a\a"  << endl;
	cerr << "\tWARNING:" << endl;
	cerr << "\tSingleton class is already instantiated" << endl;
	cerr << "\tArgument  ignored!!" << endl;
	cerr << "\tContinuing..." << endl;
    }
    return mInstance;
}

double StTpcDbElectronics::channelGain(int sector, int row, int pad) const
{
    // This should be where channel by channel gains are looked up
    // Note: the DB has getGain(), getOnlineGain(), getNominalGain(), and
    //       getRelativeGain().  We use Nominal gain I believe.
    return gTpcDbPtr->Gain(sector)->getNominalGain(row,pad);
}

double StTpcDbElectronics::channelGain(StTpcPadCoordinate& coord) const
{
    return channelGain(coord.sector(), coord.row(), coord.pad());
}

int StTpcDbElectronics::pedestal(int sector, int row, int pad, int timeB) const
{
    return averagePedestal();
}

int StTpcDbElectronics::pedestal(StTpcPadCoordinate& coord) const
{
    return pedestal(coord.sector(), coord.row(), coord.pad(), coord.timeBucket());
}
double StTpcDbElectronics::tZero(int sector, int row, int pad) const
{
    return gTpcDbPtr->T0(sector)->getT0(row,pad);
}
double StTpcDbElectronics::tZero(StTpcPadCoordinate& coord) const
{
    return tZero(coord.sector(), coord.row(), coord.pad());
}
void StTpcDbElectronics::print(ostream& os) const
{
#ifndef ST_NO_NAMESPACES
    using namespace units;
#endif
    os << "Electronics Data Base Parameters"                         << endl;
    os << "======================================="                         << endl;
    os << "Analog:"                                                         << endl;
    os << "nominalGain:         " << mNominalGain/((volt*.001)/(coulomb*1.e-15))  << " mV/fC"       << endl;
    os << "samplingFrequency:   " << mSamplingFrequency/MHz   << " MHz"         << endl;
    os << "tZero:               " << mTZero/microsecond       << " us"          << endl;
    os << "shapingTime:         " << mShapingTime/nanosecond  << " ns"          << endl;
    os << "shapingTime2:        " << mTau/nanosecond          << " ns"          << endl;

    os << "\nDigital:"                                                      << endl;
    os << "adcConversion:       " << mAdcConversion/(volt*.001) << " mV/channel" << endl;
    os << "adcConversionCharge: " << mAdcConversionCharge/(coulomb*1.e-15)  << " mV/fC"      << endl;    
    os << "numberOfTimeBins:    " << mNumberOfTimeBins                      << endl;    
    os << "averagePedestal:     " << mAveragePedestal      << " channels"   << endl;
    os << endl;
//     os << "Example of Gain per pad for Sector 1, Row 1" << endl;
//     os << " Row      Pad      Gain for this Pad" << endl;
//     os << "==========================================" << endl;
//     for(int i=0; i<gTpcDbPtr->PadPlaneGeometry()->numberOfPadsAtRow(1); i++) {
// 	os.width(3);
// 	os.setf(ios::right,ios::adjustfield);
// 	os << 1;
// 	os.width(9);
// 	os << i+1;
// 	os.width(15);
// 	os << channelGain(1,1,i+1) << endl;
//     }
//     os << endl;
}
#endif
