// $Id: St_ctf_Maker.h,v 1.3 1999/01/25 23:39:13 fisyak Exp $
// $Log: St_ctf_Maker.h,v $
// Revision 1.3  1999/01/25 23:39:13  fisyak
// Add tof
//
// Revision 1.2  1999/01/02 19:08:14  fisyak
// Add ctf
//
// Revision 1.1  1999/01/01 02:39:38  fisyak
// Add ctf Maker
//
// Revision 1.7  1998/10/31 00:25:45  fisyak
// Makers take care about branches
//
// Revision 1.6  1998/10/06 18:00:31  perev
// cleanup
//
// Revision 1.5  1998/08/26 12:15:13  fisyak
// Remove asu & dsl libraries
//
// Revision 1.4  1998/08/14 15:25:58  fisyak
// add options
//
// Revision 1.3  1998/08/10 02:32:07  fisyak
// Clean up
//
// Revision 1.2  1998/07/20 15:08:15  fisyak
// Add tcl and tpt
//
#ifndef STAR_St_ctf_Maker
#define STAR_St_ctf_Maker

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// St_ctf_Maker virtual base class for Maker                            //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
#ifndef StMaker_H
#include "StMaker.h"
#endif
class St_ctg_geo;
class St_ctg_slat_phi;
class St_ctg_slat_eta;
class St_ctg_slat;
class St_cts_mpara;
class St_ctf_Maker : public StMaker {
 private:
   Bool_t drawinit;
   St_ctg_geo       *m_ctb;          //!
   St_ctg_slat_phi  *m_ctb_slat_phi; //!
   St_ctg_slat_eta  *m_ctb_slat_eta; //!
   St_ctg_slat      *m_ctb_slat;     //!
   St_cts_mpara     *m_cts_ctb;      //!
   St_ctg_geo       *m_tof;          //!
   St_ctg_slat_phi  *m_tof_slat_phi; //!
   St_ctg_slat_eta  *m_tof_slat_eta; //!
   St_ctg_slat      *m_tof_slat;     //!
   St_cts_mpara     *m_cts_tof;      //!
 protected:
 public: 
                  St_ctf_Maker(const char *name="ctf", const char *title="event/data/ctf");
   virtual       ~St_ctf_Maker();
   virtual Int_t Init();
   virtual Int_t  Make();
   virtual void   PrintInfo();
   ClassDef(St_ctf_Maker, 1)   //StAF chain virtual base class for Makers
};

#endif
