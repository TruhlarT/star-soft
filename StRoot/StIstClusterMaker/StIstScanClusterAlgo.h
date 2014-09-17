#ifndef StIstScanClusterAlgo_hh
#define StIstScanClusterAlgo_hh

#include "StRoot/StIstClusterMaker/StIstIClusterAlgo.h"

class StIstCollection;
class StIstRawHitCollection;
class StIstClusterCollection;


/**
 * Concrete implementation of a simple algorithm for clustering of the raw hits
 * registered by the 2D IST sensors. The clustering is done sequentially--first
 * in columns and then the column-wise proto-clusters are grouped in neighboring
 * columns.
 *
 * 1) Reads all raw hits per ladder (six sensors) and groups into vectors
 * (each vector corresponds to a sensor column).
 * 2) Does clustering in individual column.
 * 3) Does clustering in neighboring columns.
 * 4) Fill hit collections.
 *
 * \author Yaping Wang
 * \date March 2013
 */
class StIstScanClusterAlgo : public StIstIClusterAlgo
{

protected:
   enum {kIstScanClusterAlgo = 2};

   virtual Int_t doClustering(const StIstCollection &istCollection, StIstRawHitCollection &rawHits, StIstClusterCollection &clusters );
   ClassDef(StIstScanClusterAlgo, 0);
};

#endif


/***************************************************************************
*
* $Log: StIstScanClusterAlgo.h,v $
* Revision 1.11  2014/09/17 20:36:20  smirnovd
* Simplified public interface by reducing the number of unnecessarily required parameters
*
* Revision 1.10  2014/09/17 20:33:32  smirnovd
* Squashed commit of the following:
*
* commit 72dc19a6663ea31c719c1a61f6d2b4752dd766aa
* Author: Dmitri Smirnov <d.s@plexoos.com>
* Date:   Wed Sep 17 12:34:42 2014 -0400
*
*     Minor code refactoring, clean up
*
* commit e083a10a9fb60b7dcce692ef8043b9227c12768b
* Author: Dmitri Smirnov <d.s@plexoos.com>
* Date:   Wed Sep 17 12:18:16 2014 -0400
*
*     Removed pointless comments
*
* commit 88d51857362c91c954704cec4a31a0b0fa7fccc5
* Author: Dmitri Smirnov <d.s@plexoos.com>
* Date:   Wed Sep 17 12:17:26 2014 -0400
*
*     Updated description in doxygen comments
*
* commit eb09527489179fc7dab6aa7f23fd132b25185bb1
* Author: Dmitri Smirnov <d.s@plexoos.com>
* Date:   Tue Sep 9 15:15:56 2014 -0400
*
*     StIstScanClusterAlgo: Removed unused variable
*
* commit 1a8df63533c71a0e2ba4d8275ebf89f4e3004765
* Author: Dmitri Smirnov <d.s@plexoos.com>
* Date:   Fri Aug 22 16:04:47 2014 -0400
*
*     Neatened headers: Removed unused, spelled paths in includes explicitly as it slightly helps in identifying dependencies
*
* commit 972e8ed41403bd680ade5ecc509f8bca004e86ee
* Author: Dmitri Smirnov <d.s@plexoos.com>
* Date:   Wed Sep 17 12:34:20 2014 -0400
*
*     Minor stylistic changes
*
* commit 57daf5a1e0b3246fd12f1dd1c2ca089b62930c83
* Author: Dmitri Smirnov <d.s@plexoos.com>
* Date:   Tue Sep 16 16:29:14 2014 -0400
*
*     Improved doxygen comments
*
* Revision 1.9  2014/09/07 13:54:45  ypwang
* move setUsedTimeBin() and setSplitFlag() setters from inherited classes to their base class StIstIClusterAlgo.h
*
* Revision 1.8  2014/09/07 11:41:36  ypwang
* ClassDef version updated from 1 to 0, and remove Init() function
*
* Revision 1.7  2014/08/22 21:32:45  smirnovd
* Moved doxygen comment to where it belongs
*
* Revision 1.6  2014/08/22 21:27:27  smirnovd
* Decalred methods virtual as that what they are. Makes the code better to understand
*
* Revision 1.5  2014/08/22 15:55:15  smirnovd
* Fixed style with astyle -s3 -p -H -A3 -k3 -O -o -y -Y -f
*
* Revision 1.4  2014/08/22 15:50:00  smirnovd
* Moved CVS history to the end of file
*
* Revision 1.3  2014/02/08 03:34:16  ypwang
* updating scripts
*
*
****************************************************************************
* StIstScanClusterAlgo.h,v 1.0
* Revision 1.0 2013/11/04 15:55:30 Yaping
* Initial version
****************************************************************************/
