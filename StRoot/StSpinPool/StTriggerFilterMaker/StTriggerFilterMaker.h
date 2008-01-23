#ifndef ST_TRIGGER_FILTER_MAKER_HH
#define ST_TRIGGER_FILTER_MAKER_HH

// $Id: StTriggerFilterMaker.h,v 1.1 2008/01/23 04:45:08 kocolosk Exp $

/*****************************************************************************
 * @class StTriggerFilterMaker
 * @author A.Kocoloski
 *
 * Privileged Maker which skips events unless they match supplied trigger IDs.
 *****************************************************************************/

#ifndef StMaker_H
#include "StMaker.h"
#endif

#include <vector>
using std::vector;

class StTriggerFilterMaker : public StMaker {
public:
    StTriggerFilterMaker(const char *name = "triggerFilter");
    virtual ~StTriggerFilterMaker();
    
    //virtual void Clear(const char *option="");
    virtual Int_t Init();
    //virtual Int_t InitRun(int runnumber);
    virtual Int_t Make();
    //virtual Int_t Finish();
    
    void addTrigger(unsigned int trigId) { mGoodTriggers.push_back(trigId); }
    
    virtual const char* GetCVS() const
    {static const char cvs[]="Tag $Name:  $ $Id: StTriggerFilterMaker.h,v 1.1 2008/01/23 04:45:08 kocolosk Exp $ built "__DATE__" "__TIME__; return cvs;}
    
private:
    vector<unsigned int> mGoodTriggers; //!
    
    ClassDef(StTriggerFilterMaker,1)
};

#endif

/*****************************************************************************
 * $Log: StTriggerFilterMaker.h,v $
 * Revision 1.1  2008/01/23 04:45:08  kocolosk
 * Privileged Maker which skips events unless they fired any one of a set of supplied trigIDs
 *
 *****************************************************************************/
