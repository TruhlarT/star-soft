// $Id: StStrangeControllerInclude.h,v 3.0 2000/07/14 12:56:49 genevb Exp $
// $Log: StStrangeControllerInclude.h,v $
// Revision 3.0  2000/07/14 12:56:49  genevb
// Revision 3 has event multiplicities and dedx information for vertex tracks
//
// Revision 2.1  2000/06/09 22:17:10  genevb
// Allow MC data to be copied between DSTs, other small improvements
//
// Revision 2.0  2000/06/05 05:19:42  genevb
// New version of Strangeness micro DST package
//
//
#ifndef STAR_StStrangeControllerInclude
#define STAR_StStrangeControllerInclude
//////////////////////////////////////////////////////////////////////////
//                                                                      //
// StStrangeControllerInclude: include file for controller classes      //
// StV0Controller strangeness micro DST controller for V0s              //
// StXiController strangeness micro DST controller for Xis              //
// StKinkController strangeness micro DST controller for Kinks          //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
#include "StStrangeControllerBase.h"
#include "StStrangeMuDstMaker.h"
#include "StMessMgr.h"


//_____________________________________________________________________________
inline void StStrangeControllerBase::PrintNumCand(const char* text, Int_t num) {
  gMessMgr->Info() << IsA()->GetName() << ": " << text << " "
                   << num << " " << GetName() << " candidates" << endm;
}
//_____________________________________________________________________________
inline StStrangeControllerBase* StStrangeControllerBase::GetDstController() {
  return dstMaker->Get(GetName());
}
//_____________________________________________________________________________

class StV0Controller : public StStrangeControllerBase {
 public:
  StV0Controller();
  virtual ~StV0Controller();
  virtual Int_t MakeReadDst();
  virtual Int_t MakeCreateDst(StEvent& event);
  virtual Int_t MakeCreateMcDst(StMcVertex* mcVert);
  ClassDef(StV0Controller,3)
};

class StXiController : public StStrangeControllerBase {
 public:
  StXiController();
  virtual ~StXiController();
  virtual Int_t MakeReadDst();
  virtual Int_t MakeCreateDst(StEvent& event);
  virtual Int_t MakeCreateMcDst(StMcVertex* mcVert);
  ClassDef(StXiController,3)
};

class StKinkController : public StStrangeControllerBase {
 public:
  StKinkController();
  virtual ~StKinkController();
  virtual Int_t MakeReadDst();
  virtual Int_t MakeCreateDst(StEvent& event);
  virtual Int_t MakeCreateMcDst(StMcVertex* mcVert);
  ClassDef(StKinkController,3)
};

#endif
