//*-- Author :Christof Struck
//
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//                       Stl3CounterMaker                               //
//                                                                      //
//  calculates trigger counters                                         //
//  - nProcessed                                                        //
//  - nAccepted                                                         //
//  - nBuild                                                            //
//  for each l3 algorithm switched on for the given run                 //
//  and the global counters                                             //
//  - nProcessed                                                        //
//  - nReconstructed                                                    //
//  and writes this to the database on a daq-file basis                 //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
//
//
//  $Id: Stl3CounterMaker.cxx,v 1.3 2002/02/20 23:31:10 struck Exp $
//
//  $Log: Stl3CounterMaker.cxx,v $
//  Revision 1.3  2002/02/20 23:31:10  struck
//  final tune-up
//
//  Revision 1.2  2002/02/20 22:09:49  struck
//  added some debugging info
//
//  Revision 1.1  2002/02/13 22:36:31  struck
//  major code clean-up for Stl3RawReaderMaker, first version of Stl3CounterMaker
//
//
//
//////////////////////////////////////////////////////////////////////////


#include <stdlib.h>
#include "Stl3CounterMaker.h"
#include "StChain.h"
#include "St_DataSetIter.h"
#include "StMessMgr.h"
#include "StDAQMaker/StDAQReader.h"
#include "tables/St_l3RunSummary_Table.h"
#include "tables/St_l3AlgorithmInfo_Table.h"
#include "tables/St_l3AlgorithmCount_Table.h"
#include "tables/St_l3GlobalCounter_Table.h"
#include "Rtypes.h"
#include "TSystem.h"

ClassImp(Stl3CounterMaker)

//_____________________________________________________________________________
Stl3CounterMaker::Stl3CounterMaker(const char *name):StMaker(name){
 //  l3Counter constructor
}

//_____________________________________________________________________________
Stl3CounterMaker::~Stl3CounterMaker(){
}


//_____________________________________________________________________________
Int_t Stl3CounterMaker::Init(){
  //  Init - is a first method the top level StChain calls to initialize all its makers

  // Make Connection to raw data
  DAQReaderSet = GetDataSet("StDAQReader");
 
  // set switches
  mL3On = kFALSE;
  mStoreDbTables = kTRUE;

  //SetDebug(1);

  mDaqFileName = new TString(GetBroadcast("DAQFile"));
  if (m_DebugLevel) cout << "daq file: " << mDaqFileName->Data() << endl;

  // extract file sequence number
  TString seq((*mDaqFileName)(mDaqFileName->Index("_physics_"), 30));
  if (seq.Contains(".daq")) {
        TString fileNo = seq(21,4);
	TString rowNo = seq(9,7);
	mDaqFileSequenceNumber = atoi(fileNo.Data());
	mRunNumber = atoi(rowNo.Data());
  }
  else {
        mDaqFileSequenceNumber = 999;
	mRunNumber = 9999999;
	cout << "Stl3CounterMaker::Init(): Could not extract daq file run/sequence number." << endl;
  }
  if (m_DebugLevel) cout << "run number: " << mRunNumber << ",  sequence number: " << mDaqFileSequenceNumber << endl;

  // reset database pointer
  mDbSet = 0;

  // get new database tables
  mAlgorithmCounterTable = new St_l3AlgorithmCount("l3AlgorithmCount", 1);
  mGlobalCounterTable = new St_l3GlobalCounter("l3GlobalCounter", 1);

  l3GlobalCounter_st totalCounterRow;
  totalCounterRow.runNumber      = mRunNumber;
  totalCounterRow.fileNumber     = mDaqFileSequenceNumber;
  totalCounterRow.nProcessed     = 0;
  totalCounterRow.nReconstructed = 0;
  mGlobalCounterTable->AddAt(&totalCounterRow);

  for (int i=0; i<MaxNumberOfAlgorithms; i++) {
        l3AlgorithmCount_st totalAlgCounterRow;
	totalAlgCounterRow.runNumber  = mRunNumber;
        totalAlgCounterRow.algId      = 0;
	totalAlgCounterRow.fileNumber = mDaqFileSequenceNumber;
	totalAlgCounterRow.nProcessed = 0;
	totalAlgCounterRow.nAccept    = 0;
	totalAlgCounterRow.nBuild     = 0;
	mAlgorithmCounterTable->AddAt(&totalAlgCounterRow);
  }

  mNumberOfGl3Nodes = 0;
  mNumberOfAlgorithms = 0;
  mEventCounter = 0;

  // reset counter
  for (int i=0; i<MaxNumberOfGl3Nodes; i++) {
        mGlobalCounter[i].nProcessed = 0;
	mGlobalCounter[i].nReconstructed = 0;
	for (int j=0; j<MaxNumberOfAlgorithms; j++) {
	      mAlgorithmCounter[i][j].algId = 0;
	      mAlgorithmCounter[i][j].nProcessed = 0;
	      mAlgorithmCounter[i][j].nAccept = 0;
	      mAlgorithmCounter[i][j].nBuild = 0;
	}
  }

  // return
  return StMaker::Init();
}


//_____________________________________________________________________________
Int_t Stl3CounterMaker::Make()
{
    //
    //  Make - this method is called in loop for each event
    //
       
    // here we start
    cout << "Now we start l3Counter Maker. \n" ;

    // get the l3 daqreader
    StDAQReader *daqReader = (StDAQReader*)(DAQReaderSet->GetObject()) ;
    if (daqReader) { 
          ml3reader = daqReader->getL3Reader();

	  if (ml3reader) {

	        // set flag L3 ON
	        mL3On = kTRUE;

		// debug output
	        if (m_DebugLevel) {
		      if (ml3reader->getGlobalTrackReader())
			    cout << ml3reader->getGlobalTrackReader()->getNumberOfTracks()
				 << " global tracks found.\n";
		}

		if (GetCounters()) {
		      gMessMgr->Error("Stl3CounterMaker: problems getting l3 counters.");
		      return kStErr;
		}

	  } // if (ml3reader)

	  else {
	        // if L3 is on for this run
	        // crash chain
	        if (mL3On) {
		      cout << "ERROR: L3 is ON, but no l3 data found in this event." << endl;
		      return kStErr;
		}
		// if L3 is off so far
		// it may be switched off for this run
		// so don't crash the chain
		else {
		      cout << "WARNING: no l3 data found." << endl;
		      return kStWarn;
		}
	  } 

    } // if (daqReader)

    // go home
    return kStOk;
}



//_____________________________________________________________________________

Int_t Stl3CounterMaker::GetCounters()
{

  // get Gl3AlgorithmReader
  Gl3AlgorithmReader* gl3Reader = ml3reader->getGl3AlgorithmReader();
  if (!gl3Reader) {
        cout << "ERROR: L3 is ON, but L3 summary data is missing!" << endl;
	return 1;
  }

  // check data
  // L3_summary.on==0 indicates that the event crashed in
  // L3 online and raw data contains no valid information for us
  if (ml3reader->getL3_Summary()->on == 0) {
        cout << "Warning: L3 crashed online on this event, no usefull information."
	     << endl;
	return 0;
  }

  // get database info
  mDbSet = GetDataBase("RunLog/l3");
  // if we didn't get the db use maximum values as default
  if (mDbSet) {
        // get number of gl3 nodes
        TTable* l3runSummaryTable = (TTable* )mDbSet->Find("l3RunSummary");
	// database can be there, but no tables :-(
	if (l3runSummaryTable) {
	      l3RunSummary_st* data = (l3RunSummary_st* )l3runSummaryTable->GetArray();
	      mNumberOfGl3Nodes = data->nGl3Nodes;
	      if (m_DebugLevel) {
		    cout << "database: runNumber = " << data->runNumber << endl;
		    cout << "database: nGl3Nodes = " << data->nGl3Nodes << endl;
	      }
	      // check limit
	      if (mNumberOfGl3Nodes>MaxNumberOfGl3Nodes) {
		    cout << " ERROR: number of gl3 nodes too high: db -> " << mNumberOfGl3Nodes
			 << "  max -> " << MaxNumberOfGl3Nodes << endl;
		    return 1;
	      }
	}
	else {
	      mNumberOfGl3Nodes = MaxNumberOfGl3Nodes;
	      cout << "  no table entry for this run in 'l3RunSummary' found!" << endl;
	      cout << "  using default values." << endl;
	}
  }
  else {
        mNumberOfGl3Nodes = MaxNumberOfGl3Nodes;
	cout << "  no database 'Runlog/l3' found!" << endl;
	cout << "  using default values." << endl;
  }

  // gl3 node which built this event
  int gl3Id = ml3reader->getGl3Id();

  // number of algorithms
  mNumberOfAlgorithms = gl3Reader->getNumberofAlgorithms();
  
  // check number of algorithms and gl3 node id
  if (mNumberOfAlgorithms >= MaxNumberOfAlgorithms) {
        cout << "ERROR: number of algorithms exceeds limit: found "
	     << mNumberOfAlgorithms << ", limit " << MaxNumberOfAlgorithms
	     << endl;
	return 1;
  }
  if (gl3Id<=0 || gl3Id>= MaxNumberOfGl3Nodes) {
        cout << "ERROR: gl3 id exceeds limit: found "
	     << gl3Id << ", limit " << MaxNumberOfGl3Nodes
	     << endl;
	return 1;
  }

  //--------------------------
  // now do the bookkeeping
  // and fill the results 
  // directly into the db tables
  //--------------------------

  // increase the event counter
  mEventCounter++;

  // first: global counter
  mGlobalCounter[gl3Id-1].nProcessed     = gl3Reader->getNumberOfProcessedEvents();
  mGlobalCounter[gl3Id-1].nReconstructed = gl3Reader->getNumberOfReconstructedEvents();
  // second: algorithm counter
  Algorithm_Data* algData = gl3Reader->getAlgorithmData();
  for (int i=0; i<mNumberOfAlgorithms; i++) {
        mAlgorithmCounter[gl3Id-1][i].algId      = algData[i].algId;
	mAlgorithmCounter[gl3Id-1][i].nProcessed = algData[i].nProcessed;
	mAlgorithmCounter[gl3Id-1][i].nAccept    = algData[i].nAccept;
	mAlgorithmCounter[gl3Id-1][i].nBuild     = algData[i].nBuild;
  }

  // get total counters
  // and put them into the db tables
  l3GlobalCounter_st* totalCounter = (l3GlobalCounter_st*) mGlobalCounterTable->GetTable();
  mAlgorithmCounterTable->SetNRows(mNumberOfAlgorithms);
  l3AlgorithmCount_st* totalAlgCounter = (l3AlgorithmCount_st*) mAlgorithmCounterTable->GetTable();

  totalCounter->nProcessed     = 0;
  totalCounter->nReconstructed = 0;

  for (int i=0; i<mNumberOfAlgorithms; i++) {
        totalAlgCounter[i].algId      = 0;
	totalAlgCounter[i].nProcessed = 0;
	totalAlgCounter[i].nAccept    = 0;
	totalAlgCounter[i].nBuild     = 0;
  }
 
  
  for (int i=0; i<mNumberOfGl3Nodes; i++) {
        // if one gl3 node wasn't seen so far,
        // the counters are still undefined
        if (mGlobalCounter[i].nProcessed==0 && mEventCounter<(2*mNumberOfGl3Nodes)) {
	      totalCounter->nProcessed     = -1;
	      totalCounter->nReconstructed = -1;
	      for (int j=0; j<mNumberOfAlgorithms; j++) {
		    totalAlgCounter[j].algId      = mAlgorithmCounter[gl3Id-1][j].algId;
		    totalAlgCounter[j].nProcessed = -1;
		    totalAlgCounter[j].nAccept    = -1;
		    totalAlgCounter[j].nBuild     = -1;
	      }
	      break;
	}
	// summ-up the counters of all gl3 nodes
	// we have seen so far after #(mNumberOfGl3Nodes*2) events
	totalCounter->nProcessed     += mGlobalCounter[i].nProcessed;
	totalCounter->nReconstructed += mGlobalCounter[i].nReconstructed;
	for (int k=0; k<mNumberOfAlgorithms; k++) {
	      totalAlgCounter[k].algId       = mAlgorithmCounter[gl3Id-1][k].algId;
	      totalAlgCounter[k].nProcessed += mAlgorithmCounter[i][k].nProcessed;
	      totalAlgCounter[k].nAccept    += mAlgorithmCounter[i][k].nAccept;
	      totalAlgCounter[k].nBuild     += mAlgorithmCounter[i][k].nBuild;
	}
  }

  // debugging
  if (m_DebugLevel) {
        cout << " Global counters:   nProcessed = " << totalCounter->nProcessed
	     << ",   nReconstructed = " << totalCounter->nReconstructed << endl;
	cout << " algId\tnProcessed\tnAccept\tnBuild" << endl;
	for (int k=0; k<mNumberOfAlgorithms; k++) {
	      cout << totalAlgCounter[k].algId << "\t"
		   << totalAlgCounter[k].nProcessed << "\t"
		   << totalAlgCounter[k].nAccept << "\t"
		   << totalAlgCounter[k].nBuild << endl;
	}
	cout << " ------------------------------------ " << endl;
  }


  // all right go home
  return 0 ;  
}



//____________________________________________________________________________
Int_t Stl3CounterMaker::Finish()
{

  if (!mStoreDbTables) return 0;

  // write db tables into file
  char filename[80];

  sprintf(filename,"./StarDb/RunLog/l3counters.%08d.%06d.C",GetDate(),GetTime());
  TString dirname = gSystem->DirName(filename);

  if (Debug()) cout << "output dir: " << dirname.Data() << endl;

  if (gSystem->OpenDirectory(dirname.Data())==0) { 
        if (gSystem->mkdir(dirname.Data())) {
	      cout << "Stl3CounterMaker::Finish(): Directory " << dirname << " creation failed" << endl;
	      cout << "Stl3CounterMaker::Finish(): Putting l3counters.C in current directory" << endl;
	      for (int i=0;i<80;i++) filename[i]=0;
	      sprintf(filename,"l3counters.%08d.%06d.C",GetDate(),GetTime());
	}
  }
  ofstream *out = new ofstream(filename);
  mGlobalCounterTable->SavePrimitive(*out,"");
  mAlgorithmCounterTable->SavePrimitive(*out,"");
  delete out;

  return 0;
}
