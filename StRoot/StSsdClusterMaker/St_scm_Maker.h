// $Id: St_scm_Maker.h,v 1.9 2005/05/17 14:16:41 lmartin Exp $
//
// $Log: St_scm_Maker.h,v $
// Revision 1.9  2005/05/17 14:16:41  lmartin
// CVS tags added
//
/*!
 * \class St_scm_Maker
 * \author B.Hippolyte, W.Pinganaud   
 * \date 2000
 *
 *  Cluster matching  for the Silicon Strip Detectors
 * 
 *  This maker controls  the space-point reconstruction in the SSD :
 *  clusters from each side of a single silicon strip detector
 *  are associated in different packages types. Solving the
 *  cluster package give one or several solutions for the hits   
 *  positions in the silicon strip detector.
 * 
 * See documentation at http://star.in2p3.fr/STAR_informatique/hit_reconstruction.html#scm
 */
#ifndef STAR_St_scm_Maker
#define STAR_St_scm_Maker

#ifndef StMaker_H
#include "StMaker.h"
#endif
class TFile;
class TH1S;
class TH2S;

class St_sdm_geom_par;
class St_sdm_condition_db;
class St_svg_geom;
class St_sls_ctrl;
class St_scm_ctrl;

class St_scm_Maker : public StMaker {
 private:
  St_sdm_geom_par      *m_geom_par;//!
  St_sdm_condition_db  *m_condition_db;//!
  St_svg_geom          *m_geom;//!
  St_sls_ctrl          *m_sls_ctrl;//!
  St_scm_ctrl          *m_scm_ctrl;//!
  void makeScmCtrlHistograms(); //!
  
 protected:
  
  TFile *ScmCtrlFile; //!
  TH2S *matchisto;    //! (1p-1n) packages control matching.
  TH1S *orthoproj;    //! orthonormal projection and perfect matching deviation.

 public: 
                  St_scm_Maker(const char *name="scm_spt");
   virtual       ~St_scm_Maker();
   virtual Int_t  Init();
   virtual Int_t  Make();
   virtual Int_t  Finish();
   virtual void   PrintInfo();

   virtual const char *GetCVS() const
     {static const char cvs[]="Tag $Name:  $ $Id: St_scm_Maker.h,v 1.9 2005/05/17 14:16:41 lmartin Exp $ built "__DATE__" "__TIME__ ; return cvs;}


   ClassDef(St_scm_Maker, 1)   //StAF chain virtual base class for Makers
};
#endif

/***************************************************************************
 *
 * $Log: St_scm_Maker.h,v $
 * Revision 1.9  2005/05/17 14:16:41  lmartin
 * CVS tags added
 *
 * Revision 1.8  2005/05/13 15:16:54  bouchet
 * reading ssd/geom and no more writeScfCtrlHistograms and writeScmCtrlHistograms methods
 *
 * Revision 1.7  2004/01/26 23:03:49  perev
 * WarnOff
 *
 * Revision 1.6  2003/10/08 03:18:09  suire
 * *** empty log message ***
 *
 * Revision 1.3  2002/03/25 20:13:05  suire
 * Small memory leak fixes, doxygen documentation
 *
 *
 **************************************************************************/

