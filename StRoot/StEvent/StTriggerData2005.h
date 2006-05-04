/***************************************************************************
 *
 * $Id: StTriggerData2005.h,v 2.4 2006/05/04 19:05:51 ullrich Exp $
 *
 * Author: Akio Ogawa, Oct 2004
 ***************************************************************************
 *
 * Description:  Concrete implementation of StTriggerData.
 *               For year 2005 only.
 *
 ***************************************************************************
 *
 * $Log: StTriggerData2005.h,v $
 * Revision 2.4  2006/05/04 19:05:51  ullrich
 * Added stuff to handle L2 results data.
 *
 * Revision 2.3  2006/03/22 20:58:21  ullrich
 * Added interface to L2 results (offsets).
 *
 * Revision 2.2  2004/11/30 19:19:12  ullrich
 * Added new access function for EEMC data (Akio).
 *
 * Revision 2.1  2004/11/02 21:18:39  ullrich
 * Initial Revision.
 *
 **************************************************************************/
#ifndef StTriggerData2005_hh
#define StTriggerData2005_hh

#include "StTriggerData.h"

struct TrgDataType2005;

class StTriggerData2005 : public StTriggerData {
public:
    StTriggerData2005();
    StTriggerData2005(const TrgDataType2005*);
    ~StTriggerData2005();
  
    void dump() const;  //dump data into text
  
    // versison and data type information
    unsigned int version() const;           
    unsigned int numberOfPreXing() const;   
    unsigned int numberOfPostXing() const;  
  
    // generic Trigger infomations
    unsigned int token() const;
    unsigned int triggerWord() const;
    unsigned int actionWord() const;      
    unsigned short busyStatus() const;
    unsigned short dsmInput() const;
    unsigned short trgToken() const;
    unsigned short dsmAddress() const;
    unsigned short mAddBits() const;
    unsigned short bcData(int channel) const;

    //L2 offsets
    int L2ResultsOffset(StL2AlgorithmId id, int run) const;  
    bool isL2Triggered(StL2TriggerResultType id, int run) const;
  
    // bunch and spin bits
    unsigned int bunchCounterHigh() const;
    unsigned int bunchCounterLow() const;
    unsigned int bunchId48Bit() const;
    unsigned int bunchId7Bit() const;
    unsigned int spinBit() const;
    unsigned int spinBitYellowFilled() const;
    unsigned int spinBitYellowUp() const;
    unsigned int spinBitYellowDown() const;
    unsigned int spinBitYellowUnpol() const;
    unsigned int spinBitBlueFilled() const;
    unsigned int spinBitBlueUp() const;
    unsigned int spinBitBlueDown() const;
    unsigned int spinBitBlueUnpol() const;
        
    // High Level Trigger info
    unsigned short tcuBits() const;
    unsigned short lastDSM(int address) const;
    unsigned short bemcLayer1DSM(int channel, int prepost=0) const;
    unsigned short eemcLayer1DSM(int channel, int prepost=0) const;
    unsigned short emcLayer2DSM(int channel) const;
    unsigned short fpdLayer1DSMRaw(StBeamDirection eastwest, int channel, int prepost=0) const;
    unsigned short fpdLayer1DSM(StBeamDirection eastwest, int module, int board, int prepost=0) const;
    unsigned short fpdLayer2DSMRaw(int channel) const;
    unsigned short fpdLayer2DSM(StBeamDirection eastwest, int module) const;
    
    // CTB
    unsigned short ctbRaw(int address, int prepost=0) const;
    unsigned short ctb(int pmt, int prepost=0) const;
    unsigned short ctbTraySlat(int tray, int slat, int prepost=0) const;    
    unsigned short ctbSum(int prepost=0) const;

    // MWC
    unsigned short mwc(int pmt, int prepost=0) const;
            
    // BBC
    unsigned short bbcADC(StBeamDirection eastwest, int pmt, int prepost=0) const;
    unsigned short bbcTDC(StBeamDirection eastwest, int pmt, int prepost=0) const;
    unsigned short bbcADCSum(StBeamDirection eastwest, int prepost=0) const;
    unsigned short bbcADCSumLargeTile(StBeamDirection eastwest, int prepost=0) const;
    unsigned short bbcEarliestTDC(StBeamDirection eastwest, int prepost=0) const;
    unsigned short bbcTimeDifference() const;

    // FPD
    unsigned short fpd(StBeamDirection eastwest, int module, int pmt, int prepost=0) const; 
    unsigned short fpdSum(StBeamDirection eastwest, int module) const;
   
    //ZDC
    unsigned short zdcAtChannel(int channel, int prepost=0) const;
    unsigned short zdcAtAddress(int address, int prepost=0) const;
    unsigned short zdcUnAttenuated(StBeamDirection eastwest, int prepost=0) const;
    unsigned short zdcAttenuated(StBeamDirection eastwest, int prepost=0) const;
    unsigned short zdcADC(StBeamDirection eastwest, int pmt, int prepost=0) const;
    unsigned short zdcTDC(StBeamDirection eastwest, int prepost=0) const;
    unsigned short zdcHardwareSum(int prepost=0) const;

    //ZDCSMD
    unsigned short zdcSMD(StBeamDirection eastwest, int verthori, int strip, int prepost=0) const;

    // EMC
    unsigned char bemcHighTower(int patch_id, int prepost=0) const;
    unsigned char bemcJetPatch (int patch_id, int prepost=0) const;
    unsigned char eemcHighTower(int patch_id, int prepost=0) const;
    unsigned char eemcJetPatch (int patch_id, int prepost=0) const;
    unsigned char bemcHighestTowerADC(int prepost=0) const;
    unsigned char eemcHighestTowerADC(int prepost=0) const;

    // experts only
    char* getTriggerStructure();
    TrgDataType2005* getTriggerStructure2005();  
    int getRawSize() const;
    unsigned      char * getDsm0_EEMC(int prepost=0) const;
    unsigned short int * getDsm1_EEMC(int prepost=0) const;
    unsigned short int * getDsm2_EMC()  const;
    unsigned short int * getDsm3()      const;
    
protected:
    TrgDataType2005 *mData;
    
    ClassDef(StTriggerData2005,1) 
};

#endif
