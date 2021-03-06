#ifndef StTpcRTSHitMaker_H
#define StTpcRTSHitMaker_H

/***************************************************************************
 *
 * $Id: StTpcRTSHitMaker.h,v 1.16 2018/06/29 21:46:23 smirnovd Exp $
 * StTpcRTSHitMaker - class to runonline (RTS) cluster maker over StTpcRawData
 * $Log: StTpcRTSHitMaker.h,v $
 * Revision 1.16  2018/06/29 21:46:23  smirnovd
 * Revert iTPC-related changes committed on 2018-06-20 through 2018-06-28
 *
 * Revert "NoDead option added"
 * Revert "Fill mag field more carefully"
 * Revert "Assert commented out"
 * Revert "Merging with TPC group code"
 * Revert "Remove too strong assert"
 * Revert "Restore removed by mistake line"
 * Revert "Remove not used anymore file"
 * Revert "iTPCheckIn"
 *
 * Revision 1.14  2018/04/10 11:38:44  smirnovd
 * StTpcHitMaker: Modified for iTPC era (Yuri and Irakli)
 *
 * Revision 1.13  2018/04/10 11:32:09  smirnovd
 * Minor corrections across multiple files
 *
 * - Remove ClassImp macro
 * - Change white space
 * - Correct windows newlines to unix
 * - Remove unused debugging
 * - Correct StTpcRTSHitMaker header guard
 * - Remove unused preprocessor directives in StiCA
 * - Minor changes in status and debug print out
 * - Remove using std namespace from StiKalmanTrackFinder
 * - Remove includes for unused headers
 *
 * Revision 1.12  2014/08/06 11:43:50  jeromel
 * Suffix on literals need to be space (later gcc compiler makes it an error) - first wave of fixes
 *
 * Revision 1.11  2012/09/13 21:00:04  fisyak
 * Corrections for iTpx, clean up
 *
 * Revision 1.10  2012/05/07 23:01:37  fisyak
 * Add Tonko's interface for variable no. of pad rows
 *
 * Revision 1.9  2012/05/07 15:51:01  fisyak
 * Remove hard coded TPC numbers
 *
 * Revision 1.8  2011/03/08 18:20:44  genevb
 * Limit on number of hits starting at time bin 0
 *
 * Revision 1.7  2010/08/30 18:02:02  genevb
 * Introduce hit maxima for tracking
 *
 * Revision 1.6  2010/01/12 22:55:17  fisyak
 * Add minimum cluster charge in ADC for <= 20090101
 *
 * Revision 1.5  2009/11/25 21:34:04  fisyak
 * replace daqReader by daq_tpx
 *
 * Revision 1.4  2009/11/10 21:05:08  fisyak
 * Add attributes for sector and pad  row selections
 *
 * Revision 1.3  2009/10/07 13:46:35  fine
 * replace  the obsolete rts_reader with the modern daqReader
 *
 * Revision 1.2  2008/12/15 21:04:01  fine
 * For for the NEW_DAQ_READER
 *
 * Revision 1.1.1.1  2008/05/27 14:22:41  fisyak
 * Maker to access TPC DAQ information via EVP_READER
 *
 * Revision 1.1  2008/04/28 14:37:16  fisyak
 * Rearrage TpcHitMaker to make it run for parallel taks, add the first version of online clustering
 *
 * Revision 1.1.1.1  2008/04/03 20:16:39  fisyak
 * Initial version
 *
 *--------------------------------------------------------------------------
 *
 ***************************************************************************/

#include "StMaker.h"

class StTpcDigitalSector;

#include "StDAQMaker/StRtsReaderMaker.h"
class daq_tpx;
class StTpcRTSHitMaker : public StMaker {
 public:
  StTpcRTSHitMaker(const char *name="tpc_hits") : StMaker(name), fTpx(0), fminCharge(0) {memset(mTpx_RowLen, 0, sizeof(mTpx_RowLen));}
  virtual ~StTpcRTSHitMaker();
  
  Int_t               Init();
  Int_t               InitRun(Int_t runnumber);
  Int_t               Make();
 private:
  daq_tpx *fTpx; //!
  Double_t fminCharge; // ! minimum cluster charge in ADC
  Int_t    maxHits[24];
  Int_t    maxBin0Hits;
  Int_t    bin0Hits;
  UChar_t *mTpx_RowLen[24];
  // cvs
  virtual const char *GetCVS() const    {
    static const char cvs[]="Tag $Name:  $Id: built " __DATE__ " " __TIME__ ; return cvs;
  }
  ClassDef(StTpcRTSHitMaker, 1)    //StTpcRTSHitMaker - class to fille the StEvewnt from DAQ reader
};

#endif
