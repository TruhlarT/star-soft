/***************************************************************************
*
* $Id: StIstSimpleClusterAlgo.h,v 1.12 2014/09/07 13:54:45 ypwang Exp $
*
* Author: Yaping Wang, March 2013
***************************************************************************/

#ifndef StIstSimpleClusterAlgo_hh
#define StIstSimpleClusterAlgo_hh

#include "StIstIClusterAlgo.h"

class StIstRawHit;
class StIstCluster;
class StIstCollection;
class StIstRawHitCollection;
class StIstClusterCollection;


/**
* Description:
* 1) Reads all raw hits per ladder (six sensors) and writes into a vector.
* 2) Starts from the 1st raw hit, and loops the vector to look for
* neighboring raw hits (in a sensor area) and do clustering. The found
* cluster will be filled into a ladder cluster collection.
* 3) A case-by-case splitting algorithm can be enabled/disabled for the
* found clusters (here only works for cases with cluster size <= 4).
*/
class StIstSimpleClusterAlgo : public StIstIClusterAlgo
{

public:
   StIstSimpleClusterAlgo();
   virtual Int_t doClustering(const StIstCollection &istCollection, StIstRawHitCollection &rawHits, StIstClusterCollection &clusters );

protected:
   enum {kIstSimpleClusterAlgo = 1};

   Int_t doSplitting(StIstClusterCollection &clusters, unsigned char numTimeBins);
   Int_t splitCluster(int cSize, int clusterSizeList[], StIstRawHit *rawHitPtr[], StIstCluster *clusterIt, StIstClusterCollection &clusters, unsigned char numTimeBins);

private:
   ClassDef(StIstSimpleClusterAlgo, 0);
};

#endif


/***************************************************************************
*
* $Log: StIstSimpleClusterAlgo.h,v $
* Revision 1.12  2014/09/07 13:54:45  ypwang
* move setUsedTimeBin() and setSplitFlag() setters from inherited classes to their base class StIstIClusterAlgo.h
*
* Revision 1.11  2014/09/07 11:41:36  ypwang
* ClassDef version updated from 1 to 0, and remove Init() function
*
* Revision 1.10  2014/08/22 21:38:20  smirnovd
* Restored declaration removed by mistake
*
* Revision 1.9  2014/08/22 21:32:45  smirnovd
* Moved doxygen comment to where it belongs
*
* Revision 1.8  2014/08/22 21:27:27  smirnovd
* Decalred methods virtual as that what they are. Makes the code better to understand
*
* Revision 1.7  2014/08/22 15:55:15  smirnovd
* Fixed style with astyle -s3 -p -H -A3 -k3 -O -o -y -Y -f
*
* Revision 1.6  2014/08/22 15:50:00  smirnovd
* Moved CVS history to the end of file
*
* Revision 1.5  2014/02/16 21:42:54  ypwang
* getting number of time bins used in current event by StIstCollection::getNumTimeBins() function
*
* Revision 1.4  2014/02/10 16:33:44  smirnovd
* Trimmed trailing spaces, expanded tabs to eight spaces
*
* Revision 1.3  2014/02/08 03:34:16  ypwang
* updating scripts
*
*
****************************************************************************
* StIstSimpleClusterAlgo.h,v 1.0
* Revision 1.0 2013/11/04 15:55:30 Yaping
* Initial version
****************************************************************************/
