#ifndef StDetectorDbRichScalers_h
#define StDetectorDbRichScalers_h

#include "StMaker.h"

class  osstream;
struct trigDetSums_st;
struct richvoltages_st;
struct y1Mult_st;

class StDetectorDbRichScalers{
public:
    static StDetectorDbRichScalers* instance();
    
    double getCTBWest();
    double getCTBEast();
    double getCTBOrTOFp();
    double getTOFp();
    double getZDCWest();
    double getZDCEast();
    double getZDCX();
    double getMult();
    double getL0();
    double getBBCX();
    double getBBCXCTB();
    unsigned int getRichHVStatus();
    void update(StMaker*);
    
    friend class nodbody; // For virtual ~
    friend ostream& operator<<(ostream& os, StDetectorDbRichScalers& v);

protected:
    trigDetSums_st* mScalers;
    richvoltages_st* mVolts;
    y1Mult_st* mY1Mults;
    
    StDetectorDbRichScalers();
    virtual ~StDetectorDbRichScalers();
private:
    static StDetectorDbRichScalers* sInstance;
};

#endif
