// $Id: StFtpcDriftMapMaker.h,v 1.5 2001/04/02 12:06:36 jcs Exp $
// $Log: StFtpcDriftMapMaker.h,v $
// Revision 1.5  2001/04/02 12:06:36  jcs
// get FTPC calibrations,geometry from MySQL database
//
// Revision 1.4  2001/03/19 15:53:05  jcs
// use ftpcDimensions from database
//
// Revision 1.3  2001/03/09 13:54:26  jcs
// write out cstructs with new values so that they can be added to database
//
// Revision 1.2  2001/03/07 15:12:39  jcs
// use MySQL database instead of params
//
// Revision 1.1  2000/12/20 08:44:02  jcs
// Replace pam/ftpc/fmg with maker
//
//
#ifndef STAR_StFtpcDriftMapMaker
#define STAR_StFtpcDriftMapMaker

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// StFtpcDriftMapMaker class                                            //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
#ifndef StMaker_H
#include "StMaker.h"
#endif

class St_ftpcClusterPars;
class St_ftpcSlowSimGas;
class St_ftpcSlowSimPars;
class St_ftpcDimensions;
class St_ftpcPadrowZ;
class St_ftpcEField;
class St_ftpcVDrift;
class St_ftpcDeflection;
class St_ftpcdVDriftdP;
class St_ftpcdDeflectiondP;
class St_ftpcGas;
class St_ftpcDriftField;

class TH1F;
class TH2F;

class StFtpcDriftMapMaker : public StMaker {
 private:
   char*   fTableName;      // c-structure name that is same as table in database
   char*   fOutputFileName; // file name for output
  // static Char_t m_VersionCVS = "$Id: StFtpcDriftMapMaker.h,v 1.5 2001/04/02 12:06:36 jcs Exp $";
  // Int_t         m_mode;        // mode 1 = primaries;
   St_ftpcClusterPars   *m_clusterpars;   //!
   St_ftpcSlowSimGas    *m_slowsimgas;    //!
   St_ftpcSlowSimPars   *m_slowsimpars;   //!
   St_ftpcDimensions    *m_dimensions;    //!
   St_ftpcPadrowZ       *m_padrow_z;      //!
   St_ftpcEField        *m_efield;        //!
   St_ftpcVDrift        *m_vdrift;        //!
   St_ftpcDeflection    *m_deflection;    //!
   St_ftpcdVDriftdP     *m_dvdriftdp;     //!
   St_ftpcdDeflectiondP *m_ddeflectiondp; //!
   St_ftpcGas           *m_gas;           //!
   St_ftpcDriftField    *m_driftfield;    //!
  void                  MakeHistograms();// Histograms for FTPC drift map
  
 protected:
 public: 
  StFtpcDriftMapMaker(const char *name="ftpc_raw");
  virtual       ~StFtpcDriftMapMaker();
  virtual Int_t Init();
  virtual Int_t  Make();
  // virtual void Set_mode       (Int_t   m =      2){m_mode       = m;} // *MENU*
  virtual const char *GetCVS() const
    {static const char cvs[]="Tag $Name:  $ $Id: StFtpcDriftMapMaker.h,v 1.5 2001/04/02 12:06:36 jcs Exp $ built "__DATE__" "__TIME__ ; return cvs;}
  
  ClassDef(StFtpcDriftMapMaker, 1)  
};
    
#endif
    
