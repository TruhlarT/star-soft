/***************************************************************************
*
* $Id: StIstScanClusterAlgo.h,v 1.3 2014/02/08 03:34:16 ypwang Exp $
*
* Author: Yaping Wang, October 2013
****************************************************************************
* Description: 
* 1) Reads all raw hits per ladder (six sensors) and groups into vectors 
* (each vector is corresponding to a sensor column).
* 2) Does clustering in individual column.
* 3) Does clustering in neighboring columns.
* 4) Fill hit collections.
****************************************************************************
*
* $Log: StIstScanClusterAlgo.h,v $
* Revision 1.3  2014/02/08 03:34:16  ypwang
* updating scripts
*
*
****************************************************************************
* StIstScanClusterAlgo.h,v 1.0
* Revision 1.0 2013/11/04 15:55:30 Yaping
* Initial version
****************************************************************************/

#ifndef StIstScanClusterAlgo_hh
#define StIstScanClusterAlgo_hh

#include "StIstIClusterAlgo.h"

class StIstCollection;
class StIstRawHitCollection;
class StIstClusterCollection;

class StIstScanClusterAlgo :public StIstIClusterAlgo
{

public:
    StIstScanClusterAlgo();
    Int_t doClustering(const StIstCollection& istCollection, StIstRawHitCollection& rawHits, StIstClusterCollection& clusters );
    Int_t Init();

    void setUsedTimeBin(unsigned char tb = -1);    
    void setSplitFlag( bool splitFlag = 1);
 
protected:
    Bool_t mSplitCluster;
    UChar_t mTimeBin;
    
    enum {kIstScanClusterAlgo=2};

 private:
  ClassDef(StIstScanClusterAlgo,1);
};

inline void StIstScanClusterAlgo::setSplitFlag( bool splitFlag )		{ mSplitCluster = splitFlag; };
inline void StIstScanClusterAlgo::setUsedTimeBin(unsigned char tb)		{ mTimeBin = tb; };
#endif
