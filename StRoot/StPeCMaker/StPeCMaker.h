// $Id: StPeCMaker.h,v 1.13 2002/12/19 18:09:53 yepes Exp $
//
// $Log: StPeCMaker.h,v $
// Revision 1.13  2002/12/19 18:09:53  yepes
// MuDST input added
//
// Revision 1.12  2002/04/18 19:02:12  meissner
// Change Init to  InitRun
//
// Revision 1.11  2001/09/14 18:00:22  perev
// Removed references to StRun.
//
// Revision 1.10  2001/02/12 21:15:57  yepes
// New version of StPeCMaker, lots of changes
//
// Revision 1.7  2000/04/21 19:09:42  nystrand
// Update StPeCPair class, new histograms
//
// Revision 1.6  2000/03/24 22:36:16  nystrand
// First version with StPeCEvent
//
// Revision 1.5  2000/01/20 23:03:15  nystrand
// First Version of StPeCMaker with new StEvent
//
// Revision 1.3  1999/07/15 13:57:21  perev
// cleanup
//
// Revision 1.2  1999/04/08 16:37:27  nystrand
// MakeBranch,SetBranch removed
//
// Revision 1.1  1999/04/06 20:47:35  akio
// The first version
//
// Revision 1.0  1999/03/05 11:00:00  Nystrand
// First Version
//
///////////////////////////////////////////////////////////////////////////////
//
// StPeCMaker
//
// Description: 
//  Sample maker to access and analyze Peripheral Collisions through StEvent
//
// Environment:
//  Software developed for the STAR Detector at Brookhaven National Laboratory
//
// Author List: 
//  Joakim Nystrand, LBNL
//
// History:
//
///////////////////////////////////////////////////////////////////////////////
#ifndef StPeCMaker_HH
#define StPeCMaker_HH
#include "StMaker.h"
#include "StPeCEvent.h"
#include "StPeCTrigger.h"
#include "StPeCGeant.h"
#include "TH1.h"
#include "TH2.h"
#include "TNtuple.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"

class StEvent;
class StPeCEvent;
class TH1F;
class TH2F;
class StMuDst;

class StPeCMaker : public StMaker
{
public:
	StPeCMaker(const Char_t *name = "analysis");
	virtual ~StPeCMaker();
	virtual Int_t Init();
	virtual Int_t InitRun(Int_t runnr);
	virtual Int_t Make();
	virtual Int_t Finish();

	void setInfoLevel(Int_t in) {infoLevel = in ;};
	void setFilter(Int_t fi) {filter = fi;};
	void setMuDst(StMuDst* mu) {muDst = mu;};	//Accessor for muDst pointer
	void setFileName ( TString name ) { treeFileName = name ; } ;
	void setOutputPerRun ( Int_t in = 1 ) { outputPerRun = in ; } ;

	TString treeFileName ;
protected:
	TFile* m_outfile;

	TTree* uDstTree;
	TTree* geantTree;

	StPeCEvent* pevent;
	StPeCTrigger* trigger;
	StPeCGeant* geant;

	Int_t   infoLevel;
	Int_t   filter;	//1 == two prong, 2 == four prong
	Int_t   outputPerRun ; // 1=output per run 0(default)=one output file
private:
	StMuDst* muDst;


	Int_t Cuts(StEvent* event, StPeCEvent* pevent);
	Int_t Cuts4Prong(StEvent* event, StPeCEvent* pevent);
	Int_t triggerSim(StEvent*);

	virtual const char *GetCVS() const
	{static const char cvs[]="Tag $Name:  $ $Id: StPeCMaker.h,v 1.13 2002/12/19 18:09:53 yepes Exp $ built "__DATE__" "__TIME__ ; return cvs;}

	ClassDef(StPeCMaker, 1)
};

#endif



