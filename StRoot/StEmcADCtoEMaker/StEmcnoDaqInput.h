/***************************************************************************
 *
 * $Id: StEmcnoDaqInput.h,v 1.1 2001/07/17 00:14:37 perev Exp $
 *
 * Author: 
 ***************************************************************************
 *
 * Description: RICH offline software
 *              StRchMaker.h - ROOT/STAR Maker for offline chain.
 ***************************************************************************/

#ifdef __ROOT__
#ifndef STAR_StEmcnoDaqInput
#define STAR_StEmcnoDaqInput

#ifndef StMaker_H
#include "StMaker.h"
#endif

#ifndef __CINT__
#include <vector>
#ifndef ST_NO_NAMESPACES
using std::vector;
#endif
#endif

#include "TTable.h"  
//#include "tables/St_emcCalSettings_Table.h"
//#include "tables/St_emcCalSummary_Table.h"
#include "tables/St_emcCalibration_Table.h"
//#include "tables/St_emcEqualization_Table.h"
//#include "tables/St_emcMipCalib_Table.h"                                      
class StEMCReader;
class StEvent;
class TDataset;
class StEmcHandleDB;

class StEmcnoDaqInput {
    
private:
    
protected:
    
public: 
    StEmcnoDaqInput(const StEvent*, const StEMCReader*,const TDataSet*);
    virtual       ~StEmcnoDaqInput();
    virtual Int_t  ProcessInput();
protected:
    
private:
    StEvent* mevent;
    StEMCReader* mTheEmcReader;//!
    TDataSet* m_calibdb;
    ClassDef(StEmcnoDaqInput, 1)   
	};

#endif 
#endif /* __ROOT__ */
