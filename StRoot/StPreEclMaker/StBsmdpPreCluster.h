//
// $id$
//
// $Log: StBsmdpPreCluster.h,v $
// Revision 1.3  2000/08/24 22:11:34  suaide
//
//
// restored some files for background compatibility
//
// Revision 1.1  2000/05/15 21:24:00  subhasis
// initial version
//
// PreClusters Finder Maker for EMC
//
//
// Author: Subhasis Chattopadhyay,
//         Aleksei Pavlinov , July 1999
//

#ifndef STAR_StBsmdpPreCluster
#define STAR_StBsmdpPreCluster

#include "StEmcPreCluster.h"

class StBsmdpPreCluster : public TObject 
{
public:
  StBsmdpPreCluster(TArrayI*);

  ClassDef(StBsmdpPreCluster,1)// Class for Bsmdp cluster
};

#endif
