/**********************************************************************
 *
 * $Id: StEStruct2ptCorrelations.h,v 1.3 2004/09/16 23:37:25 chunhuih Exp $
 *
 * Author: Jeff Porter adaptation of Aya's 2pt-analysis
 *
 **********************************************************************
 *
 * Description:  Analysis code for 2pt-analysis. 
 *    The analysis runs as follows:
 *       1D and 2D arrays (in yt,eta,phi) are setup
 *       and filled for each of the 6 pair types:
 *       Sibling (++,+- & -+, --)
 *       Mixed   (++,+- & -+, --)
 *       The 2D versions are additionally divided into yt1,yt2 slices
 *       and (via the StEStructBuffer) z-vertex
 *       After arrays are filled (looped over all events/job), Histograms are 
 *       created, filled, and written out to the data file for further
 *       processing.
 *
 *
 ***********************************************************************/
#ifndef __STEBYE2PTCORRELATIONS__H
#define __STEBYE2PTCORRELATIONS__H


#include "TROOT.h"
#include "StEStructPool/AnalysisMaker/StEStructAnalysis.h"
#include "StEStructPairCuts.h"
#include "StEStructBinning.h"
#include "StEStructBuffer.h"

class TFile;
class TH1F;
class TH2F;
class StEStructEvent;
class StTimer;


class StEStruct2ptCorrelations: public StEStructAnalysis {

 protected:

  int  manalysisMode; //! simple enumeration of analyses ...
  bool mskipPairCuts; //!
  bool mdoPairCutHistograms; //!
  bool mInit;  //! found need when overridding this class
  bool mDeleted;//! "     " ...

  StEStructEvent*        mCurrentEvent;  //!  pointer to EStruct2pt data 
  StEStructPairCuts      mPair; //! for pairs (1 at a time) and all pair cuts

  char*     moutFileName; //!
  StTimer*  mtimer;       //!

  StEStructEvent*     mMixingEvent;  //! dummy      //  Previous Event Stored 
  StEStructBuffer      mbuffer[10];  // 10 slices in z-vertex
  int             mbuffCounter[10];

  //-> (pre) histograms & histograms for analysis.
  // All are arrays of 6 for 6 charged sign and combinatoric types;
  // 0,1,2 for Sibling (++,+-,--)
  // 3,4,5, for Mixed  (++,+-,--)
  
  int numPairs[6];
  int numPairsProcessed[6];
  int mpossiblePairs[6];

  TH1F* mHNEvents[2];

  deltaMtBins mDeltaMt[6]; //!
  TH1F * mHDeltaMt[6];//!
 
  // -> 1D hists....
  dmtBins mdmts[6];
  smtBins msmts[6];
  detaBins mdetas[6];
  setaBins msetas[6];
  dphiBins mdphis[6];
  sphiBins msphis[6];

  TH1F* mHdmts[6];
  TH1F* mHsmts[6];
  TH1F* mHdetas[6];
  TH1F* mHsetas[6];
  TH1F* mHdphis[6];
  TH1F* mHsphis[6];

  //-> X vs X 
  mtBins **mMtMt[6]; //!
  etaBins **mEtaEta[6]; //!
  phiBins **mPhiPhi[6]; //!

  TH2F ** mHMtMt[6]; //!
  TH2F ** mHEtaEta[6]; //!
  TH2F ** mHPhiPhi[6]; //!

  // Delta Y vs Delta X
  dphiBins **mJtDMtDPhi[6]; //!
  dmtBins  **mJtDEtaDMt[6]; //!
  dphiBins **mJtDEtaDPhi[6]; //!

  TH2F ** mHJtDMtDPhi[6];
  TH2F ** mHJtDEtaDMt[6];
  TH2F ** mHJtDEtaDPhi[6];

  // Sum Y vs Delta X
  dmtBins  **mAtSMtDMt[6];     //! smt array of dmt bins
  detaBins **mAtSEtaDEta[6];  //! seta array of deta bins
  dphiBins **mAtSPhiDPhi[6];  //! sphi array of dphi bins

  TH2F ** mHAtSMtDMt[6];
  TH2F ** mHAtSEtaDEta[6];
  TH2F ** mHAtSPhiDPhi[6];

  // Sum Y vs Sum X
  sphiBins **mJtSMtSPhi[6]; //!
  smtBins  **mJtSEtaSMt[6]; //!
  sphiBins **mJtSEtaSPhi[6];//! 

  TH2F ** mHJtSMtSPhi[6];//!
  TH2F ** mHJtSEtaSMt[6];//!
  TH2F ** mHJtSEtaSPhi[6];//!

  void  moveEvents();

 public:

  StEStruct2ptCorrelations(int mode=0);
  StEStruct2ptCorrelations(const char* cutFileName, int mode=0);
  virtual ~StEStruct2ptCorrelations();

  StEStructPairCuts& getPairCuts();
  void  setAnalysisMode(int mode);
  void  setCutFile(const char* cutFileName);  

  //---> support of interface  
  void  setOutputFileName(const char* outFileName);
  bool  doEvent(StEStructEvent* p);

  void  init();
  void  cleanUp();
  void  finish();
  virtual void  fillHistograms();
  virtual void  writeHistograms(TFile* tf);
  virtual void  initArraysAndHistograms();
  virtual void  deleteArraysAndHistograms();

  // analysis specific functions 
  bool  makeSiblingAndMixedPairs();
  virtual void  makePairs(StEStructEvent* e1, StEStructEvent* e2, int j);

  int   getNumPairs(int i){ return numPairs[i]; };
  int   getNumPairsProcessed(int i){ return numPairsProcessed[i]; };
  int   getPossiblePairs(int i){ return mpossiblePairs[i]; };

  void logStats(ostream& os);

    ClassDef(StEStruct2ptCorrelations,1)
};   

inline void StEStruct2ptCorrelations::setAnalysisMode(int mode){ manalysisMode=mode;};

inline void StEStruct2ptCorrelations::setCutFile(const char* cutFileName){
  mPair.setCutFile(cutFileName);
  mPair.loadCuts();
}

inline void StEStruct2ptCorrelations::setOutputFileName(const char* fName){
  if(!fName) return;
  moutFileName=new char[strlen(fName)+1];
  strcpy(moutFileName,fName);
}

inline StEStructPairCuts& StEStruct2ptCorrelations::getPairCuts() {
  return mPair;
}

inline void StEStruct2ptCorrelations::logStats(ostream& os){
  char* htp[]={"SibPP","SibPM","SibMM","MixPP","MixPM","MixMM"};
  for(int i=0;i<6;i++){
    os<<"<pairType>"<<htp[i]<<" "<<endl;;
   os<<"   <processStat \"possiblePairs\">"<<getPossiblePairs(i);
   os<<"</processStat> "<<endl;;
   os<<"   <processStat \"inputPairs\">"<<getNumPairs(i);
   os<<"</processStat> "<<endl;;
   os<<"   <processStat \"outputPairs\">"<<getNumPairsProcessed(i);
   os<<"</processStat> "<<endl;
   os<<"</pairType>"<<endl;
  }
};



#endif


/***********************************************************************
 *
 * $Log: StEStruct2ptCorrelations.h,v $
 * Revision 1.3  2004/09/16 23:37:25  chunhuih
 *
 * changed a number of methods to be virtual, so that its behavior can
 * be dynamically changed.
 *
 * Revision 1.2  2004/06/25 03:11:49  porter
 * New cut-binning implementation and modified pair-cuts for chunhui to review
 *
 * Revision 1.1  2003/10/15 18:20:46  porter
 * initial check in of Estruct Analysis maker codes.
 *
 *
 *********************************************************************/





