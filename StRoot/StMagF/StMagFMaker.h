// $Id: StMagFMaker.h,v 1.6 2005/08/29 22:54:27 fisyak Exp $
// $Log: StMagFMaker.h,v $
// Revision 1.6  2005/08/29 22:54:27  fisyak
// switch to StarMagField
//
// Revision 1.5  2003/09/10 19:47:21  perev
// ansi corrs
//
// Revision 1.4  2001/05/21 21:40:36  fisyak
// Merge geant and production mag. fields
//
// Revision 1.3  2001/05/17 20:38:26  fisyak
// Move check for mag. scale factor into InitRun
//
// Revision 1.2  2000/01/07 00:42:33  fisyak
// merge Make with Init
//
// Revision 1.1  2000/01/04 20:44:41  fisyak
// Add StMagFMaker
//
#ifndef STAR_StMagFMaker
#define STAR_StMagFMaker

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// StMagFMaker virtual base class for Maker                            //
//                                                                      //
//  Submit any problem with this code via begin_html <A HREF="http://www.rhic.bnl.gov/STAR/html/comp_l/sofi/bugs/send-pr.html"><B><I>"STAR Problem Report Form"</I></B></A> end_html
//
//////////////////////////////////////////////////////////////////////////
#ifndef StMaker_H
#include "StMaker.h"
#endif
class St_MagFactor;
class StMagFMaker : public StMaker {
 private:
  St_MagFactor *fMagFactor; //!
 protected:
 public: 
                  StMagFMaker(const char *name="MagField");
   virtual       ~StMagFMaker();
   virtual Int_t  Init() {return kStOK;}
   virtual Int_t  InitRun(Int_t run);
   Int_t          Make() {return kStOK;}
   virtual const char *GetCVS() const
  {static const char cvs[]="Tag $Name:  $ $Id: StMagFMaker.h,v 1.6 2005/08/29 22:54:27 fisyak Exp $ built "__DATE__" "__TIME__ ; return cvs;}

   ClassDef(StMagFMaker,0)   //StAF chain virtual base class for Makers
};

#endif
