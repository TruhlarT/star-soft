/***************************************************************************
 *
 * $Id: StTpcDbSlowControl.hh,v 1.1 1999/10/11 23:55:09 calderon Exp $
 *
 * Author: Manuel Calderon de la Barca Sanchez & Brian Lasiuk Sept 13, 1999
 ***************************************************************************
 *
 * Description:   Class to hold Slow Control parameters for TRS taken
 *                from the STAR TPC DB. Class implemented as Singleton
 *
 ***************************************************************************
 *
 * $Log: StTpcDbSlowControl.hh,v $
 * Revision 1.1  1999/10/11 23:55:09  calderon
 * Version with Database Access and persistent file.
 * Not fully tested due to problems with cons, it
 * doesn't find the local files at compile time.
 * Yuri suggests forcing commit to work directly with
 * files in repository.
 *
 *
 **************************************************************************/
#ifdef __ROOT__
#ifndef ST_TPC_DB_SLOW_CONTROL_HH
#define ST_TPC_DB_SLOW_CONTROL_HH

#include <iostream.h>


#include "SystemOfUnits.h"
#include "StTpcSlowControl.hh"
#include "StTpcDb/StTpcDb.h"
class StTpcDbSlowControl : public StTpcSlowControl {
public:
    ~StTpcDbSlowControl();
    
    static StTpcSlowControl* instance();
    static StTpcSlowControl* instance(StTpcDb*);
    
    double driftVelocity()                const;

    // voltage
    double driftVoltage()                 const;
	
    double innerSectorAnodeVoltage()      const;
    double innerSectorGatingGridVoltage() const;
    double outerSectorAnodeVoltage()      const;
    double outerSectorGatingGridVoltage() const;

    // environment
    double hallTemperature()              const;
    double hallPressure()                 const;

    // Gas Gain
    double innerSectorGasGain()           const;
    double innerSectorGasGainVzero()      const;
    double innerSectorGasGainb()          const;
    
    double outerSectorGasGain()           const;
    double outerSectorGasGainVzero()      const;
    double outerSectorGasGainb()          const;

    // Diagnostic
    void print(ostream& os = cout)        const;
    
private:
    StTpcDbSlowControl();
    StTpcDbSlowControl(StTpcDb*);
    
private:
    static StTpcSlowControl* mInstance;
    StTpcDb* gTpcDbPtr;

//     double mDriftVelocity;

//     // Environment
//     double mHallTemperature;
//     double mHallPressure;
    
//     // Voltages
//     double mDriftVoltage;
    
//     double mISAnodeVoltage;
//     double mISGatingGridVoltage;
//     double mOSAnodeVoltage;
//     double mOSGatingGridVoltage;

//     // Gas Gain
//     double mISGasGain;
//     double mISGasGainVzero;
//     double mISGasGainb;

//     double mOSGasGain;
//     double mOSGasGainVzero;
//     double mOSGasGainb;
    // ClassDef(StTpcDbSlowControl,0)
};

inline double StTpcDbSlowControl::driftVelocity() const {return gTpcDbPtr->SlowControlSim()->driftVelocity()*(centimeter/(microsecond));}
    // Voltages
inline double StTpcDbSlowControl::driftVoltage() const{return gTpcDbPtr->SlowControlSim()->driftVoltage()*volt;}
inline double StTpcDbSlowControl::innerSectorAnodeVoltage() const{return gTpcDbPtr->SlowControlSim()->innerSectorAnodeVoltage()*volt;}
inline double StTpcDbSlowControl::innerSectorGatingGridVoltage() const{return gTpcDbPtr->SlowControlSim()->innerSectorGatingGridV()*volt;}
inline double StTpcDbSlowControl::outerSectorAnodeVoltage() const{return gTpcDbPtr->SlowControlSim()->outerSectorAnodeVoltage()*volt;}
inline double StTpcDbSlowControl::outerSectorGatingGridVoltage() const{return gTpcDbPtr->SlowControlSim()->outerSectorGatingGridV()*volt;}
    // Environment
inline double StTpcDbSlowControl::hallTemperature() const{return gTpcDbPtr->SlowControlSim()->hallTemperature();}
inline double StTpcDbSlowControl::hallPressure() const{return gTpcDbPtr->SlowControlSim()->hallPressure()*atmosphere;}
    // Gas Gain
inline double StTpcDbSlowControl::innerSectorGasGain() const{return gTpcDbPtr->SlowControlSim()->innerSectorGasGain();}
inline double StTpcDbSlowControl::innerSectorGasGainVzero() const{return gTpcDbPtr->SlowControlSim()->innerSectorGasGainVzero()*volt;}
inline double StTpcDbSlowControl::innerSectorGasGainb() const{return gTpcDbPtr->SlowControlSim()->outerSectorGasGainb()/volt;}

inline double StTpcDbSlowControl::outerSectorGasGain() const{return gTpcDbPtr->SlowControlSim()->outerSectorGasGain();}
inline double StTpcDbSlowControl::outerSectorGasGainVzero() const{return gTpcDbPtr->SlowControlSim()->outerSectorGasGainVzero()*volt;}
inline double StTpcDbSlowControl::outerSectorGasGainb() const{return gTpcDbPtr->SlowControlSim()->outerSectorGasGainb()/volt;}

// inline double StTpcDbSlowControl::driftVelocity() const {return mDriftVelocity;}
//     // Voltages
// inline double StTpcDbSlowControl::driftVoltage() const {return mDriftVoltage;}
// inline double StTpcDbSlowControl::innerSectorAnodeVoltage() const {return mISAnodeVoltage;}
// inline double StTpcDbSlowControl::innerSectorGatingGridVoltage() const {return mISGatingGridVoltage;}
// inline double StTpcDbSlowControl::outerSectorAnodeVoltage() const {return mOSAnodeVoltage;}
// inline double StTpcDbSlowControl::outerSectorGatingGridVoltage() const {return mOSGatingGridVoltage;}
//     // Environment
// inline double StTpcDbSlowControl::hallTemperature() const {return mHallTemperature;}
// inline double StTpcDbSlowControl::hallPressure() const {return mHallPressure;}
//     // Gas Gain
// inline double StTpcDbSlowControl::innerSectorGasGain() const {return mISGasGain;}
// inline double StTpcDbSlowControl::innerSectorGasGainVzero() const {return mISGasGainVzero;}
// inline double StTpcDbSlowControl::innerSectorGasGainb() const {return mISGasGainb;}

// inline double StTpcDbSlowControl::outerSectorGasGain() const {return mOSGasGain;}
// inline double StTpcDbSlowControl::outerSectorGasGainVzero() const {return mOSGasGainVzero;}
// inline double StTpcDbSlowControl::outerSectorGasGainb() const {return mOSGasGainb;}
#endif
#endif
