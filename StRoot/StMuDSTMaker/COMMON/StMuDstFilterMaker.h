/***************************************************************************
 *
 * $Id: StMuDstFilterMaker.h,v 1.6 2004/05/02 04:10:14 perev Exp $
 * Author: Frank Laue, BNL, laue@bnl.gov
 ***************************************************************************/
#ifndef StMuDstFilterMaker_hh
#define StMuDstFilterMaker_hh

#include "StMaker.h"
#include "StChain.h"

#include "StMuDstMaker.h"
#include "StMuDst.h"
#include "StMuEvent.h"
#include "StMuTrack.h"

#include <string>

class StMuEmcCollection;

class TTree;
class TFile;

/**
   @class StMuDstFilterMaker
   A small utility maker to create filtered muDst data files
*/
class StMuDstFilterMaker : public StMaker {
 public:
    /// Default constructor; get pointer to StMuDstMaker
    StMuDstFilterMaker(const char* name="muDstFilter");
    ~StMuDstFilterMaker();
    
    int Init();   ///< Create the output file and the TClonesArrays
    int Make();   ///< Filters the muDst and writes the filtered version
    int Finish(); ///< Writes and closes the output file
    virtual const char *GetCVS() const {
	static const char cvs[]="Tag $Name:  $ $Id: StMuDstFilterMaker.h,v 1.6 2004/05/02 04:10:14 perev Exp $ built "__DATE__" "__TIME__ ; 
	return cvs;
    }
  
    void setOutputFileName(const char* name) { mFileName = string(name); }
    void setMuDstMaker( StMuDstMaker* maker) { mMuDstMaker = maker; }
 protected:
    /// specialize this function to apply filters to the individual branches
    template<class T> bool filter(T* t) { return false;}
    /// If this function returns false, the whole event is discarded
    bool filter(StMuDst* mu) {return fabs(mu->event()->primaryVertexPosition().z())<100 ;}
    /// Now I specialize the filter function to select individual object
    bool filter(StMuEvent* ev) {return true; }             // keep all event-wise information
    bool filter(StMuTrack* track);
    bool filter(StMuEmcCollection* emc) { return true; }  // and I want to keep the emc collection   


    StMuDstMaker* mMuDstMaker; // pointer to the StMuDstMaker that is providing the input

    // output file
    TFile* mFile;
    string mFileName;
    TChain* mChain;
    TTree* mTTree;

    void createArrays();
    void clear();
    void close();
    template <class T>
    int addType(TClonesArray* tcaTo , T t);
    
    /// the list of TClonesArrays to copy
    TClonesArray* mArrays[__NARRAYS__];//->
    TClonesArray* mStrangeArrays[__NSTRANGEARRAYS__];//->
    TClonesArray* mEmcArrays[__NEMCARRAYS__];//->
    
    ClassDef(StMuDstFilterMaker, 1)
}; 


#endif

/***************************************************************************
 *
 * $Log: StMuDstFilterMaker.h,v $
 * Revision 1.6  2004/05/02 04:10:14  perev
 * private => protected
 *
 * Revision 1.5  2004/04/29 03:35:57  perev
 * protected ==> protected
 *
 * Revision 1.4  2003/11/24 23:36:36  laue
 * commented the StMuEmcCollection out
 *
 * Revision 1.3  2003/09/07 03:49:03  perev
 * gcc 3.2 + WarnOff
 *
 * Revision 1.2  2003/08/04 14:38:10  laue
 * Alex Suaide's updated for the EMC. Now EEMC is included.
 *
 * Revision 1.1  2003/04/15 18:48:36  laue
 * Minor changes to be able to filter MuDst.root files and an example
 * how to do this. The StMuDstFilterMaker is just an example, it has to be
 * customized (spoilers, chrome weels, etc.) by the user.
 *
 *
 **************************************************************************/
