/*!
 * \class StBbcTriggerDetector 
 * \author Akio Ogawa, Jan 2002
 */
/***************************************************************************
 *
 * $Id: StBbcTriggerDetector.h,v 2.4 2002/10/17 02:07:49 akio Exp $
 *
 * Author: Akio Ogawa, Jan 2002
 ***************************************************************************
 *
 * Description:
 *
 ***************************************************************************
 *
 * $Log: StBbcTriggerDetector.h,v $
 * Revision 2.4  2002/10/17 02:07:49  akio
 * Increase # of PMT from 32 to 48 for 2003 run.
 * Schema evolution should take care for reading old files.
 * Some of access functions (for east west separately, or sums)
 * will give wrong answer if you are using new 2003 mapping.
 * One should access data through raw adc values until improvements.
 * These functions do correct job for 2002 data.
 *
 * Revision 2.3  2002/02/22 22:56:46  jeromel
 * Doxygen basic documentation in all header files. None of this is required
 * for QM production.
 *
 * Revision 2.2  2002/01/28 19:28:10  jeromel
 * Wrong format of an enum list corrected. Solaris picked this up.
 *
 * Revision 2.1  2002/01/03 20:57:37  ullrich
 * Initial Revision.
 *
 **************************************************************************/
#ifndef StBbcTriggerDetector_hh
#define StBbcTriggerDetector_hh
#include "StObject.h"

class StBbcTriggerDetector : public StObject {
public:
    StBbcTriggerDetector();
    virtual ~StBbcTriggerDetector();
    // StBbcTriggerDetector(const StBbcTriggerDetector&);            use default
    // StBbcTriggerDetector& operator=(const StBbcTriggerDetector&); use default
    
    unsigned int   numberOfPMTs() const;
    unsigned int   numberOfRegisters() const;
    unsigned int   numberOfPedestalData() const;
    unsigned int   numberOfScalars() const;
    
    unsigned short adc(unsigned int) const;
    unsigned short tdc(unsigned int) const;
    unsigned short bbcRegister(unsigned int) const;
    unsigned short pedestalData(unsigned int) const;
    unsigned int   scalar(unsigned int) const;
    
    unsigned short pedestal(unsigned int id) const;
    unsigned short pedestalWidth(unsigned int id) const;
    unsigned short mip(unsigned int id) const;
    unsigned short mipWidth(unsigned int id) const;
    
    int   nHitEast();
    int   nHitWest();
    int   nHitAll();
    int   adcSumEast(); 
    int   adcSumWest();
    int   adcSumAll();
    float zVertex(); //z vertex in cm
    
    void  setAdc(unsigned int, unsigned short);
    void  setTdc(unsigned int, unsigned short);
    void  setRegister(unsigned int, unsigned short);
    void  setPedestal(unsigned int, unsigned short);
    void  setScalar(unsigned int, unsigned int);
    
    void  dump();
    
protected:
    enum {
      mMaxPMTs = 48,
      mMaxRegisters = 2,
      mMaxPedData = 128,
      mMaxScalars = 32
    };
    UShort_t mAdc[mMaxPMTs];
    UShort_t mTdc[mMaxPMTs];
    UShort_t mReg[mMaxRegisters];
    UShort_t mPed[mMaxPedData];
    UShort_t mScl[mMaxScalars];
    
    ClassDef(StBbcTriggerDetector,2)
};

inline unsigned int
StBbcTriggerDetector::numberOfPMTs() const {return mMaxPMTs;}

inline unsigned int
StBbcTriggerDetector::numberOfRegisters() const {return mMaxRegisters;}

inline unsigned int
StBbcTriggerDetector::numberOfPedestalData() const {return mMaxPedData;}

inline unsigned int
StBbcTriggerDetector::numberOfScalars() const {return mMaxScalars;}
        
inline unsigned short
StBbcTriggerDetector::pedestal(unsigned int id) const {return pedestalData(id);}

inline unsigned short
StBbcTriggerDetector::pedestalWidth(unsigned int id) const {return pedestalData(id+32);}

inline unsigned short
StBbcTriggerDetector::mip(unsigned int id) const {return pedestalData(id+64);}

inline unsigned short
StBbcTriggerDetector::mipWidth(unsigned int id) const {return pedestalData(id+96);}

#endif
