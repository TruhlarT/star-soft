/***************************************************************************
 *
 * $Id: 
 *
 * Author: Mike Lisa, Ohio State, lisa@mps.ohio-state.edu
 ***************************************************************************
 *
 * Description: part of STAR HBT Framework: StHbtMaker package
 *   a do-nothing V0 cut that always says "yes" to every V0
 *
 ***************************************************************************
 *
 * $Log: 
 *
 **************************************************************************/


#ifndef dummyV0Cut_hh
#define dummyV0Cut_hh

#ifndef StMaker_H
#include "StMaker.h"
#endif

#include "StHbtMaker/Base/StHbtV0Cut.hh"

class dummyV0Cut : public StHbtV0Cut{
public:
  dummyV0Cut();
  //~dummyV0Cut(){/* no-op*/}


  virtual bool Pass(const StHbtV0*);

  virtual StHbtString Report();

  virtual void SetMass(const double& mass);


  ClassDef(dummyV0Cut, 1)

private:
  long mNpassed;
  long mNfailed;
};

#endif
