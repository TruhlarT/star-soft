/***************************************************************************
 *
 * $Id: StFpdMaker.h,v 1.1 2002/01/16 20:21:07 akio Exp $ 
 *
 * Author: AKIO OGAWA
 *
 ***************************************************************************
 *
 * Description: FPD offline software
 ***************************************************************************
 *
 * $Log: StFpdMaker.h,v $
 * Revision 1.1  2002/01/16 20:21:07  akio
 * first version
 *
 *
 **************************************************************************/
#ifndef STAR_StFpdMaker
#define STAR_StFpdMaker
#include "StMaker.h"

//#define FPDP_DEBUG

class TH1F;
class StEvent;
class StDAQReader;
class StFpdReaderInterface;

// class definition
class StFpdMaker : public StMaker {
public: 
  StFpdMaker(const char *name="fpd");
  virtual ~StFpdMaker();
  virtual Int_t Init();
  virtual Int_t Make();
  virtual Int_t Finish();
  
  virtual const char *GetCVS() const
  {static const char cvs[]="Tag $Name:"__DATE__" "__TIME__ ; return cvs;}
  
protected:
  
private:
  StEvent* mEvent;

  ClassDef(StFpdMaker, 1)   //StAF chain virtual base class for Makers
};
#endif
