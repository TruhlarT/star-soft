//////////////////////////////////////////////////////////////////////
//
// $Id: StppEvent.h,v 1.4 2002/06/24 13:22:59 akio Exp $ 
// $Log: StppEvent.h,v $
// Revision 1.4  2002/06/24 13:22:59  akio
// numerous bug fix & updates
//
// Revision 1.3  2002/02/11 20:30:48  akio
// Many updates, including very first version of jet finder.
//
// Revision 1.2  2002/01/24 17:38:33  akio
// add L3 info, zdc info & fix phi/psi confusion
//
// Revision 1.1  2002/01/16 20:22:53  akio
// First version
//
//
// Revision 1.0  2001/06/14 Akio Ogawa
// First Version of StppEvent 
//
//////////////////////////////////////////////////////////////////////
//
// StppEvent
//
// Event class for Spin pp uDst
//
//////////////////////////////////////////////////////////////////////
#ifndef StppEvent_h
#define StppEvent_h

#define _Jet_

#include "TObject.h"
#include "TClonesArray.h"

class StppTrack;
class StEvent;
class StMuDst;
class StJet;

class StppEvent : public TObject {
 public:  
  StppEvent();
  virtual ~StppEvent();
  
#ifndef __CINT__
  Int_t fill(StEvent* event);  //event=0 for reading from MuDst
#endif /*__CINT__*/
  void clear();
  void reset();
  void setMuDst(StMuDst* dst) {mudst=dst;}; 
    
  Int_t        runN;
  Int_t        eventN;
  Int_t        token;
  Int_t        triggerWord;
  Long_t       time;
  Int_t        bunchId;
  Int_t        bunchId7bit;
  Int_t        doubleSpinIndex;

  // The function corrects for a shift by three bunch crossings
  // of the bunchId7bit number, and this goes from 1 to 60.
  Int_t        correctedBunchId();

  TClonesArray *tracks;
  Int_t        nPrimTrack;
  Int_t        nGoodTrack;
  Float_t      xVertex;
  Float_t      yVertex;
  Float_t      zVertex;  
  Int_t        LCP;
  Float_t      sumPt;
  Float_t      vectorSumPt;
  Float_t      weightedEta;
  Float_t      weightedPhi;

  Int_t        bbcAdcSumEast;   
  Int_t        bbcAdcSumWest;   
  Int_t        bbcNHitEast;   
  Int_t        bbcNHitWest;   
  Float_t      zVertexBbc;

  Int_t        fpdAdcSumNorth;   
  Int_t        fpdAdcSumSouth;   
  Int_t        fpdAdcSumTop;   
  Int_t        fpdAdcSumBottom;   
  Int_t        fpdAdcSumPres1;   
  Int_t        fpdAdcSumPres2;   
  Int_t        fpdAdcSumSmdX;   
  Int_t        fpdAdcSumSmdY;   
  Int_t        fpdSouthVeto;   

  Float_t      fpdPi0Mass;
  Float_t      fpdPi0E;
  Float_t      fpdPi0Eta;
  Float_t      fpdPi0Phi;
  Float_t      fpdPi0EShare;  

  Float_t      ctbAdcSum;   
  Int_t        ctbNHit;   
  Int_t        zdcEast;   
  Int_t        zdcWest;   
  Int_t        zdcTdcEast;   
  Int_t        zdcTdcWest;   
  Float_t      zdcRatioEast;   
  Float_t      zdcRatioWest;   

  Int_t        svtNHit;   
  Float_t      emcHighTower;   
  
#ifdef _Jet_
  Int_t nJets;
  TClonesArray *jets;  
  Float_t jetRadius() const {return jetR;} 
  Float_t jetMinSeed() const {return jetSeed;}
  Float_t jetCutOff() const {return jetCut;}
  void setjetRadius(Float_t v){jetR=v;}
  void setjetMinSeed(Float_t v){jetSeed=v;}
  void setjetCutOff(Float_t v){jetCut=v;}
#endif

  void setInfoLevel(int level) {infoLevel = level;}  
  void setTrackChoice(int choice) {trackChoice = choice;}
  Int_t getInfoLevel() const {return infoLevel;} 
  Int_t getTrackChoice() const {return trackChoice;}

private:
  StMuDst* mudst; 
  Int_t infoLevel; //!  
  Int_t trackChoice; // 0=primary, 1=global, 2=l3
#ifdef _Jet_
  Float_t jetR;
  Float_t jetSeed;
  Float_t jetCut;
#endif
  Int_t BunchIdDifference;

  ClassDef(StppEvent,3)
};

#endif
