// $Id: StScfWafer.hh,v 1.5 2006/09/15 21:04:49 bouchet Exp $
//
// $Log: StScfWafer.hh,v $
// Revision 1.5  2006/09/15 21:04:49  bouchet
// noise of the strips and clusters coded as a float ; read the noise from ssdStripCalib
//
// Revision 1.4  2005/06/14 12:20:25  bouchet
// cleaner version
//
// Revision 1.3  2005/06/13 16:01:00  reinnart
// Jonathan and Joerg changed the update function
//
// Revision 1.2  2005/05/17 14:16:34  lmartin
// CVS tags added
//
#ifndef STSCFWAFER_HH
#define STSCFWAFER_HH
#include <stdlib.h>
#include <math.h>
#include "StScfListCluster.hh"
#include "StScfListStrip.hh"
#include "StScfCluster.hh"
#include "StScfStrip.hh"

#include "tables/St_slsCtrl_Table.h"
#include "tables/St_scf_ctrl_Table.h"

class StScfWafer
{
 public:
                    StScfWafer(int id);
                    ~StScfWafer();
  
 
  StScfListCluster* getClusterP();
  StScfListCluster* getClusterN();
  StScfListStrip*   getStripP();
  StScfListStrip*   getStripN();
  void              addStrip(StScfStrip *ptr, int iSide);
  void              setSigmaStrip(int iStrip, int iSide, int iSigma, slsCtrl_st *slsCtrl);
  void              setSigmaStrip(int iStrip, int iSide, float iSigma, slsCtrl_st *slsCtrl);
  void              sortCluster();
  void              sortStrip();
  void              doClusterisation(int *numberOfCluster,St_slsCtrl *my_slsCtrl,St_scf_ctrl *my_scf_ctrl);
private:
  int               mId;
  StScfListStrip    *mStripP;
  StScfListStrip    *mStripN;
  StScfListCluster  *mClusterP;
  StScfListCluster  *mClusterN;
  int               doFindCluster(St_slsCtrl *my_slsCtrl,St_scf_ctrl *my_scf_ctrl,int iSide);
  int               doClusterSplitting(St_scf_ctrl *my_scf_ctrl,int iSide);
};
  
#endif
