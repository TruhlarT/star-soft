#ifndef StiSsdHitLoader_H
#define StiSsdHitLoader_H

#include "StiHitLoader.h"
class StEvent;
class StiGeometryTransform;

/*! \class StiSsdHitLoader
  StiSsdHitLoader is a concrete class implementing the StiHitLoader abstract
  interface. It is used to load hits from Star StEvent into the StiHitContainer
  for Sti tracking. StEvent hits from the TPC are converted using the 
  StiGeometryTransform class.
  <p>
  This class is essentially morphed from the class StiHitFiller 
  originally written by Mike Miller.

  \author Claude A Pruneau (Wayne) and M.L. Miller (Yale Software)
 */
class StiSsdHitLoader : public StiHitLoader<StEvent,StiGeometryTransform>
{
public:

    StiSsdHitLoader();
    StiSsdHitLoader(StiHitContainer      * hitContainer,
		    Factory<StiHit>      * hitFactory,
		    StiGeometryTransform * transform);
    virtual ~StiSsdHitLoader();
    virtual void loadHits(StEvent* source);
};

#endif
