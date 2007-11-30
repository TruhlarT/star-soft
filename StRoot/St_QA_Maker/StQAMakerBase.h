// $Id: StQAMakerBase.h,v 2.16 2007/11/30 05:38:50 genevb Exp $ 
// $Log: StQAMakerBase.h,v $
// Revision 2.16  2007/11/30 05:38:50  genevb
// Changes for Run8: mostly silicon removal, TOF addition
//
// Revision 2.15  2005/02/08 17:22:46  genevb
// PMD histo changes, handle estGlobal/ITTF tracks
//
// Revision 2.14  2004/12/13 15:52:37  genevb
// Numerous updates: PMD, primtrk, FPD, QAShift lists
//
// Revision 2.13  2004/02/12 05:03:17  genevb
// Year 4 AuAu changes. New SVT histos.
//
// Revision 2.12  2004/01/10 01:10:18  genevb
// Preparations for Year 5, added some svt plots
//
// Revision 2.11  2003/02/28 06:17:56  genevb
// Allow StQAMakerBase::Make to be called for all events
//
// Revision 2.10  2003/02/20 20:09:54  genevb
// Several changes for new trigger scheme, dAu data
//
// Revision 2.9  2003/02/19 06:38:29  genevb
// Rework trigger and mult/event class sections
//
// Revision 2.8  2003/02/15 22:00:52  genevb
// Add tpcSectors, fix ftpc east/west charge
//
// Revision 2.7  2002/04/23 01:59:56  genevb
// Addition of BBC/FPD histos
//
// Revision 2.6  2002/01/26 03:04:07  genevb
// Fixed some problems with fcl histos
//
// Revision 2.5  2001/12/28 09:19:13  genevb
// Adjustments for pp running
//
// Revision 2.4  2001/08/29 20:45:15  genevb
// Trigger word histos
//
// Revision 2.3  2001/05/16 20:57:03  lansdell
// new histograms added for qa_shift printlist; some histogram ranges changed; StMcEvent now used in StEventQA
//
// Revision 2.2  2001/04/28 22:05:13  genevb
// Added EMC histograms
//
// Revision 2.1  2000/08/25 16:04:10  genevb
// Introduction of files
//
//
///////////////////////////////////////////////////////////////////////////
//                                                                       //
//  StQAMakerBase base class for QA Histogram Makers                     //
//                                                                       //
///////////////////////////////////////////////////////////////////////////

#ifndef STAR_StQAMakerBase
#define STAR_StQAMakerBase

enum StQAHistSetType {
  StQA_Undef = -1,
  StQA_MC = 0,
  StQA_AuAuOld = 1,
  StQA_pp = 2,
  StQA_dAu = 3,
  StQA_AuAu = 4,
  StQA_run8 = 5
};

#include "StMaker.h"
class StQABookHist;
class TObjArray;
class TH1F;
class TH2F;

class StQAMakerBase : public StMaker {

// **************** Public Member Functions ***************************
 public:
  StQAMakerBase() {}
  StQAMakerBase(const char *name, const char *title, const char *type);
  virtual       ~StQAMakerBase();
  virtual Int_t  Init();
  virtual Int_t  Make();
  virtual void   Clear(Option_t *);
  virtual void   UseHistSet(Int_t s) { histsSet=s; }
// the following is a ROOT macro  that is needed in all ROOT code
  virtual const char *GetCVS() const
  {static const char cvs[]="Tag $Name:  $ $Id: StQAMakerBase.h,v 2.16 2007/11/30 05:38:50 genevb Exp $ built "__DATE__" "__TIME__ ; return cvs;}


// ******************** Histogram Booking Constants ************************
 protected:

  Int_t ntrk;
  Int_t nmnpt;  
  Int_t nmneta; 
  Int_t nxyz;   

// ***************** Histogram Pointers ***************************
 public:
  // histogram for number of events without primary vertex
  TH1F     *mNullPrimVtx;         //!
  // histogram for number of events in mult classes
  TH1F     *mMultClass;           //!
  // histograms for event trigger words/bits
  TH1F     *mTrigWord;            //!
  TH1F     *mTrigBits;            //!
  // for method MakeEvSum - from software monitor
  TH2F     *m_glb_trk_chg;        //! all charge east/west (TPC) 
  TH2F     *m_glb_trk_chgF;       //! all charge east/west (FTPC) 
  // histograms for TPC hits sector by sector
  TH2F     *mTpcSectorPlot[24];   //!

  // FTPC histograms
  TH1F     *m_ftpc_chargestepW; //! Chargestep from ftpc west
  TH1F     *m_ftpc_chargestepE; //! Chargestep from ftpc east
  TH1F     *m_ftpc_fcl_radialW;  //! ftpc west cluster radial position
  TH1F     *m_ftpc_fcl_radialE;  //! ftpc east cluster radial position


// **************** Members For Internal Use ***************************
 protected:
  TString QAMakerType;  // character string to prepend to each hist name/title
  TObjArray histsList;  //! pointers to the histogram classes for the
  StQABookHist* hists;  //! event class-dependent histograms
  Int_t histsSet;
  TString prefix[32];
  Int_t eventClass;
  Int_t eventCount;
  Bool_t firstEventClass;
  Bool_t fillHists;
  Bool_t ITTF;
  Int_t EST;
  Bool_t allTrigs;

  virtual void NewQABookHist();
  virtual TH2F* MH1F(const Text_t* name, const Text_t* title,
                     Int_t nbinsx, Axis_t xlow, Axis_t xup);

  virtual void BookHist();
  virtual void BookHistGeneral();
  virtual void BookHistTrigger();
  virtual void BookHistEvSum();
  virtual void BookHistFcl();

  virtual void MakeHistEvSum() = 0;
  virtual void MakeHistGlob() = 0;
  virtual void MakeHistDE() = 0;
  virtual void MakeHistPrim() = 0;
  virtual void MakeHistPID() = 0;
  virtual void MakeHistVertex() = 0;
  virtual void MakeHistPoint() = 0;
  virtual void MakeHistEMC() {}
  virtual void MakeHistEval() = 0;
  virtual void MakeHistBBC() {}
  virtual void MakeHistFPD() {}
  virtual void MakeHistPMD() {}
  virtual void MakeHistTOF() {}

  ClassDef(StQAMakerBase,0)   //needed for all code that will be used in CINT
};
    
#endif
