/***************************************************************************
 *
 * $Id: StTpcHitMaker.cxx,v 1.48 2013/01/29 23:28:16 fisyak Exp $
 *
 * Author: Valeri Fine, BNL Feb 2007
 ***************************************************************************
 *
 * Description:  Fill the StEvent from the DAQ clusters
 *               
 * Input:  DAQReader
 * Output: StTpcHit collection added to StEvent
 *
 ***************************************************************************
 *
 * $Log: StTpcHitMaker.cxx,v $
 * Revision 1.48  2013/01/29 23:28:16  fisyak
 * comment out occupancy print outs
 *
 * Revision 1.47  2013/01/28 20:26:50  fisyak
 * Simplify loop over clusters
 *
 * Revision 1.46  2012/12/06 14:33:47  fisyak
 * Keep only clusters with flag == 0 or FCF_ONEPAD | FCF_MERGED | FCF_BIG_CHARGE. Tonko's instruction
 *
 * Revision 1.45  2012/11/20 22:55:56  fisyak
 * Set the same cuts for online cluster maker as for offline one
 *
 * Revision 1.44  2012/10/24 13:36:06  fisyak
 * Increase no. of pad rows
 *
 * Revision 1.43  2012/09/13 21:00:04  fisyak
 * Corrections for iTpx, clean up
 *
 * Revision 1.42  2012/05/07 15:51:01  fisyak
 * Remove hard coded TPC numbers
 *
 * Revision 1.41  2011/06/09 20:52:08  genevb
 * Set sanity flag
 *
 * Revision 1.40  2011/04/07 23:33:12  genevb
 * Restore to version before previous commit
 *
 * Revision 1.38  2011/03/31 19:31:12  fisyak
 * Add adc to Tpc hit
 *
 * Revision 1.37  2011/03/08 18:20:44  genevb
 * Limit on number of hits starting at time bin 0
 *
 * Revision 1.36  2011/01/21 18:35:25  fisyak
 * change flag type from UChar_t to UShort_t
 *
 * Revision 1.35  2011/01/20 18:26:30  genevb
 * Add FCF_flags include, and exclude any flagged hit from AfterBurner()
 *
 * Revision 1.34  2010/11/05 16:25:19  genevb
 * No longer include hits found on dead padrows
 *
 * Revision 1.33  2010/11/04 19:39:12  genevb
 * Maintain backward reproducibility
 *
 * Revision 1.32  2010/11/04 18:30:47  genevb
 * Typo correction
 *
 * Revision 1.31  2010/11/04 18:29:58  genevb
 * Max hits scaling does not need to use PadGainT0 table
 *
 * Revision 1.30  2010/10/04 19:06:56  fisyak
 * Use FCF flag definition
 *
 * Revision 1.29  2010/09/08 15:44:41  genevb
 * Slightly better arrangement for limiting excessive TPC events
 *
 * Revision 1.28  2010/09/01 21:14:33  fisyak
 * Add codes for S-shape correction (disactivated)
 *
 * Revision 1.27  2010/08/31 15:19:36  genevb
 * Lower bound on reduced hit maxima
 *
 * Revision 1.26  2010/08/31 14:16:30  genevb
 * Correct mistake from prev commit of location of TPC cluster check
 *
 * Revision 1.25  2010/08/30 18:02:01  genevb
 * Introduce hit maxima for tracking
 *
 * Revision 1.24  2010/08/02 23:06:15  fisyak
 * Fix format
 *
 * Revision 1.23  2010/03/25 15:05:54  fisyak
 * Add AfterBurner
 *
 * Revision 1.22  2010/02/19 23:36:08  fisyak
 * Add hit Id
 *
 * Revision 1.21  2010/01/12 22:54:36  fisyak
 * Propagate flags from online clustering into StEvent
 *
 * Revision 1.20  2009/11/18 14:29:02  fisyak
 * Restore slewing correction
 *
 * Revision 1.19  2009/11/10 21:05:08  fisyak
 * Add attributes for sector and pad  row selections
 *
 * Revision 1.18  2009/09/11 22:11:58  genevb
 * Introduce TPC slewing corrections
 *
 * Revision 1.17  2009/03/18 14:21:06  fisyak
 * Move sector check under condition that there is some TPC data
 *
 * Revision 1.16  2009/03/17 19:19:21  fisyak
 * Account new Valery's interface for adc values
 *
 * Revision 1.15  2009/03/16 13:41:45  fisyak
 * Switch to new scheme (avoid legacy) for TPX cluster reading
 *
 * Revision 1.14  2009/03/11 18:38:20  fisyak
 * Add 22 time bins to account subtracted by Tonko, clean up
 *
 * Revision 1.13  2009/02/20 22:06:15  fisyak
 * Restore access to TPX
 *
 * Revision 1.12  2008/12/29 23:58:06  fine
 * Optimize the DAQ data access
 *
 * Revision 1.11  2008/12/29 21:14:41  fine
 * Sort out  the tps/tpc data handling
 *
 * Revision 1.10  2008/12/29 18:23:48  fine
 * avoid using the dummy data
 *
 * Revision 1.9  2008/12/18 20:20:25  fine
 * access two different detectors tpx/tpc
 *
 * Revision 1.8  2008/12/17 23:27:04  fine
 * Clean up
 *
 * Revision 1.7  2008/12/17 23:26:00  fine
 * Adjust the sector number
 *
 * Revision 1.6  2008/12/17 02:04:28  fine
 * fix the sector number to make the new interface happy
 *
 * Revision 1.5  2008/12/16 20:43:25  fine
 * add the DAQ_READER compliant access to the tpx sector
 *
 * Revision 1.4  2008/12/15 21:04:01  fine
 * For for the NEW_DAQ_READER
 *
 * Revision 1.3  2008/07/31 20:45:26  fisyak
 * Add TpcMixer
 *
 * Revision 1.2  2008/06/23 20:13:53  fisyak
 * Add real data pixel annotation
 *
 * Revision 1.1.1.1  2008/05/27 14:22:41  fisyak
 * Maker to access TPC DAQ information via EVP_READER
 *
 * Revision 1.3  2008/05/27 14:18:18  fisyak
 * Freeze before moving to STAR repository
 *
 * Revision 1.2  2008/04/28 14:37:15  fisyak
 * Rearrage TpcHitMaker to make it run for parallel taks, add the first version of online clustering
 *
 * Revision 1.1.1.1  2008/04/03 20:16:41  fisyak
 * Initial version
 *
 * Revision 1.9  2008/01/29 02:44:38  fine
 * INFO
 *
 * Revision 1.8  2008/01/29 02:42:31  fine
 * remove 16th sector constarin. EVP_READER can read all of them alone now.
 *
 * Revision 1.7  2008/01/28 23:48:39  fine
 * use the new base class
 *
 * Revision 1.6  2008/01/10 01:12:49  fine
 *  makr to use the full TPC + TPX
 *
 * Revision 1.5  2008/01/09 15:16:48  fine
 * Correct the sector number
 *
 * Revision 1.4  2008/01/09 00:43:29  fine
 * Working version. It can be used as the protopty for anither maker that calles RTS_READER to fill the 16-th TPX sector
 *
 * Revision 1.3  2008/01/07 19:04:07  fine
 * Add the  interface to access the DAQ clusters
 *
 * Revision 1.2  2008/01/07 17:37:39  fine
 * check for tpcHitCollection and new StTpcHit object
 *
 * Revision 1.1  2008/01/04 17:52:32  fine
 * New maker to populate the StEvent from the tpc structure filled by the new EVP_READER package
 *
 *
 * StTpcHitMaker - class to fille the StEvewnt from DAQ reader
 *
 **************************************************************************/
#include <assert.h>
#include "StEvent/StTpcHit.h"
#include <algorithm>
#include "StTpcHitMaker.h"

#include "TDataSetIter.h"
#include "StDAQMaker/StDAQReader.h"
#include "TError.h"
#include "string.h"
#include "StEvent.h"
#include "StEvent/StTpcHitCollection.h"
#include "StEvent/StTpcHit.h"
#include "RTS/src/DAQ_TPX/tpxFCF_flags.h" // for FCF flag definition
#include "StTpcRawData.h"
#include "StThreeVectorF.hh"

#include "StDaqLib/TPC/trans_table.hh"
#include "StRtsTable.h"
#include "StDbUtilities/StTpcCoordinateTransform.hh"
#include "StTpcDb/StTpcDb.h"
#include "StDbUtilities/StCoordinates.hh"
#include "StDetectorDbMaker/St_tss_tssparC.h"
#include "StDetectorDbMaker/St_tpcSlewingC.h"
#include "StDetectorDbMaker/St_TpcPadCorrectionC.h"
#include "StDetectorDbMaker/St_tpcPadGainT0BC.h"
#include "StDetectorDbMaker/St_tpcAnodeHVavgC.h"
#include "StDetectorDbMaker/St_tpcMaxHitsC.h"
#include "StDetectorDbMaker/StDetectorDbTpcRDOMasks.h"
#include "StDetectorDbMaker/St_tpcPadPlanesC.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TH2.h"
#include "St_tpc_cl.h"
TableClassImpl(St_tpc_cl,tcl_cl);
#include "St_daq_cld.h"
TableClassImpl(St_daq_cld,tcl_cl);
#include "St_daq_sim_cld.h"
TableClassImpl(St_daq_sim_cld,tcl_cl);
#include "St_daq_adc_tb.h"
TableClassImpl(St_daq_adc_tb,daq_adc_tb);
#include "St_daq_sim_adc_tb.h"
TableClassImpl(St_daq_sim_adc_tb,daq_sim_adc_tb);
ClassImp(StTpcHitMaker);
static TNtuple *pulserP = 0;
Float_t StTpcHitMaker::fgDp    = .1;             // hardcoded errors
Float_t StTpcHitMaker::fgDt    = .2;
Float_t StTpcHitMaker::fgDperp = .1;
static Int_t _debug = 0;
//#define __MAKE_NTUPLE__
//#define __CORRECT_S_SHAPE__
//_____________________________________________________________
Int_t StTpcHitMaker::Init() {
  LOG_INFO << "StTpcHitMaker::Init as\t"  << GetName() << endm;
  const Char_t *Names[kAll] = {"undef",
			       "tpc_hits","tpx_hits",
			       "TpcPulser","TpxPulser",
			       "TpcDumpPxls2Nt","TpxDumpPxls2Nt",
			       "TpxRaw","TpxRaw","TpcAvLaser","TpxAvLaser"};
  TString MkName(GetName());
  for (Int_t k = 1; k < kAll; k++) {
    if (MkName.CompareTo(Names[k],TString::kIgnoreCase) == 0) {kMode = (EMode) k; break;}
  }
  assert(kMode);
  memset(maxHits,0,sizeof(maxHits));
  maxBin0Hits = 0;
  bin0Hits = 0;
  return kStOK ;
}
//_____________________________________________________________
Int_t StTpcHitMaker::InitRun(Int_t runnumber) {
  static Bool_t Done = kFALSE;
  SetAttr("minSector",1);
  SetAttr("maxSector",24);
  SetAttr("minRow",1);
  NoInnerPadRows = St_tpcPadPlanesC::instance()->innerPadRows();
  NoRows = NoInnerPadRows + St_tpcPadPlanesC::instance()->outerPadRows();
  SetAttr("maxRow",NoRows);
  if (! Done) {
    if (kMode == kTpxAvLaser || kMode == kTpcAvLaser) {
      TFile *f = GetTFile();
      if (! f) {gMessMgr->Error() << "with Tpx/Tpc AvLaser you must provide TFile as the 5-th parameter in bfc.C macro" << endm; assert(0);}
      f->cd();
      enum {NoDim = 3};
      const Char_t *NameV[NoDim] = {     "row", "pad","time"};
      const Double_t xMin[NoDim] = {0.5       ,   0.5,  -0.5};
      const Double_t xMax[NoDim] = {0.5+NoRows, 182.5, 399.5};
      Int_t  nBins[NoDim]  = {    NoRows,   182,   400};
      fAvLaser = new THnSparseF *[24];
      for (Int_t s = 1; s <= 24; s++) {
	fAvLaser[s-1] = new THnSparseF(Form("AvLaser_%02i",s), Form("Averaged laser event for sector %02i",s), NoDim, nBins, xMin, xMax);
	fAvLaser[s-1]->CalculateErrors(kTRUE);
	for (Int_t i = 0; i < NoDim; i++) { 
	  fAvLaser[s-1]->GetAxis(i)->SetName(NameV[i]);
	}
	f->Add(fAvLaser[s-1]);
      }
    }
    Done = kTRUE;
  }
  // Prepare scaled hit maxima

  // No hit maxima if these DB params are 0
  Int_t maxHitsPerSector = St_tpcMaxHitsC::instance()->maxSectorHits();
  Int_t maxBinZeroHits = St_tpcMaxHitsC::instance()->maxBinZeroHits();
  Int_t livePads = 0;
  Int_t totalPads = 0;
  Float_t liveFrac = 1;
  for(Int_t sector=1;sector<=24;sector++) {
    Int_t liveSecPads = 0;
    Int_t totalSecPads = 0;
    if (maxHitsPerSector > 0 || maxBinZeroHits > 0) {
      for(Int_t row=1;row<=NoRows;row++) {
        Int_t numPadsAtRow = St_tpcPadPlanesC::instance()->padsPerRow(row);
        totalSecPads += numPadsAtRow;
        if (StDetectorDbTpcRDOMasks::instance()->isOn(sector,
            StDetectorDbTpcRDOMasks::instance()->rdoForPadrow(row)) &&
            St_tpcAnodeHVavgC::instance()->livePadrow(sector,row))
          liveSecPads += numPadsAtRow;
      }
      livePads += liveSecPads;
      totalPads += totalSecPads;
    }
    if (maxHitsPerSector > 0) {
      liveFrac = TMath::Max((Float_t) 0.1,
                 ((Float_t) liveSecPads) / ((Float_t) totalSecPads));
      maxHits[sector-1] = (Int_t) (liveFrac * maxHitsPerSector);
      if (Debug()) {LOG_INFO << "maxHits in sector " << sector
                             << " = " << maxHits[sector-1] << endm;}
    } else {
      maxHits[sector-1] = 0;
      if (Debug()) {LOG_INFO << "No maxHits in sector " << sector << endm;}
    }
  }
  if (maxBinZeroHits > 0) {
    liveFrac = TMath::Max((Float_t) 0.1,
               ((Float_t) livePads) / ((Float_t) totalPads));
    maxBin0Hits = (Int_t) (liveFrac * maxBinZeroHits);
    if (Debug()) {LOG_INFO << "maxBinZeroHits " << maxBin0Hits << endm;}
  } else {
    maxBin0Hits = 0;
    if (Debug()) {LOG_INFO << "No maxBinZeroHits" << endm;}
  }
  // write event header for AvLaser
  if (kMode == kTpxAvLaser || kMode == kTpcAvLaser) {
    StEvtHddr *header = GetEvtHddr();
    if (header) {
      TFile *f = GetTFile();
      if (! f) {gMessMgr->Error() << "with Tpx/Tpc AvLaser you must provide TFile as the 5-th parameter in bfc.C macro" << endm; assert(0);}
      f->cd();
      header->Write();
    }
  }  
  return kStOK;
}
//_____________________________________________________________
Int_t StTpcHitMaker::Make() {
  Int_t minSector = IAttr("minSector");
  Int_t maxSector = IAttr("maxSector");
  Int_t minRow    = IAttr("minRow");
  Int_t maxRow    = IAttr("maxRow");
  
  bin0Hits = 0;

  for (Int_t sector = minSector; sector <= maxSector; sector++) {
    fId = 0;
    // invoke tpcReader to fill the TPC DAQ sector structure
    TString cldadc("cld");
    if ( kMode == kTpxRaw || kMode == kTpcRaw || 
	 kMode == kTpcAvLaser || kMode == kTpxAvLaser) cldadc = "adc";
    mQuery = Form("tpx/%s[%i]",cldadc.Data(),sector);
    StRtsTable *daqTpcTable = GetNextDaqElement(mQuery);
    if (daqTpcTable) {
      kReaderType = kStandardTpx;
    } else {
      mQuery = Form("tpc/legacy[%i]",sector);
      daqTpcTable = GetNextDaqElement(mQuery);
      if (daqTpcTable) {
	kReaderType = kLegacyTpc;
      } else {
	mQuery = Form("tpx/legacy[%i]",sector);
	daqTpcTable = GetNextDaqElement(mQuery);
	if (daqTpcTable) {
	  kReaderType = kLegacyTpx;
	}
      }
    }
    Int_t hitsAdded = 0;
    while (daqTpcTable) {
      assert(Sector() == sector);
      Int_t row = NoRows;
      fTpc = 0;
      if (kReaderType == kLegacyTpx || kReaderType == kLegacyTpc) fTpc = (tpc_t*)*DaqDta()->begin();
      else 	                                                  row = daqTpcTable->Row();
      if (row >= minRow && row <= maxRow) {
	switch (kMode) {
	case kTpc: 
	case kTpx:            hitsAdded += UpdateHitCollection(sector); break;
	case kTpcPulser:       
	case kTpxPulser:      if (fTpc) DoPulser(sector);               break;
	case kTpcAvLaser:   
	case kTpxAvLaser:   
	  if ( fTpc)                    TpcAvLaser(sector);
	  else 	                        TpxAvLaser(sector);
	  break;
	case kTpcDumpPxls2Nt:  
	case kTpxDumpPxls2Nt: if (fTpc) DumpPixels2Ntuple(sector);     break;
	case kTpcRaw: 
	case kTpxRaw: 
	  if ( fTpc) RawTpcData(sector);
	  else 	     RawTpxData(sector);          
	  break;
	default:
	  break;
	}
      }
      daqTpcTable = GetNextDaqElement(mQuery);
    }
    if (maxHits[sector-1] && hitsAdded > maxHits[sector-1]) {
      LOG_ERROR << "Too many hits (" << hitsAdded << ") in one sector ("
                << sector << "). Skipping event." << endm;
      return kStSkip;
    }
  }
  if (maxBin0Hits && bin0Hits > maxBin0Hits) {
      LOG_ERROR << "Too many hits (" << bin0Hits
                << ") starting at time bin 0. Skipping event." << endm;
      return kStSkip;
  }
  if (kMode == kTpc || kMode == kTpx) {
    StEvent *pEvent = dynamic_cast<StEvent *> (GetInputDS("StEvent"));
    if (Debug()) {LOG_INFO << "StTpcHitMaker::Make : StEvent has been retrieved " <<pEvent<< endm;}
    if (! pEvent) {LOG_INFO << "StTpcHitMaker::Make : StEvent has not been found " << endm; return kStWarn;}
    StTpcHitCollection *hitCollection = pEvent->tpcHitCollection();
    if (hitCollection) AfterBurner(hitCollection);
  }
  return kStOK;
}
//_____________________________________________________________
Int_t  StTpcHitMaker::Finish() {
  if (GetTFile() && fAvLaser) {
    for (Int_t sector = 1; sector <= 24; sector++) {
      if (fAvLaser[sector-1]) {
	THnSparseF *hnew = CompressTHn(fAvLaser[sector-1]);
	GetTFile()->Remove(fAvLaser[sector-1]);
	delete fAvLaser[sector-1];
	fAvLaser[sector-1] = hnew;
	GetTFile()->Add(fAvLaser[sector-1]);
      }
    }
  }
  return StMaker::Finish();
}
//_____________________________________________________________
Int_t StTpcHitMaker::UpdateHitCollection(Int_t sector) {
  // Populate StEvent with StTpcHit collection
  StEvent *pEvent = dynamic_cast<StEvent *> (GetInputDS("StEvent"));
  if (Debug()) {LOG_INFO << "StTpcHitMaker::Make : StEvent has been retrieved " <<pEvent<< endm;}
  if (! pEvent) {LOG_INFO << "StTpcHitMaker::Make : StEvent has not been found " << endm; return 0;}
  StTpcHitCollection *hitCollection = pEvent->tpcHitCollection();
  if ( !hitCollection )  {
    // Save the hit collection to StEvent...if needed
    hitCollection = new StTpcHitCollection();
    pEvent->setTpcHitCollection(hitCollection);
  }
  Int_t NRows = DaqDta()->GetNRows();
  if (NRows <= 0) return 0;
  Int_t nhitsBefore = hitCollection->numberOfHits();
  Int_t sec = DaqDta()->Sector();
  Int_t row = DaqDta()->Row();
  if (kReaderType == kLegacyTpc || kReaderType == kLegacyTpx) {
    tpc_t *tpc = (tpc_t *) DaqDta()->GetTable();
    for (Int_t l = 0; l < NRows; tpc++) {
      if ( !tpc->has_clusters )  return 0;
      for(Int_t padrow=0;padrow<NoRows;padrow++) {
        if (! St_tpcPadGainT0BC::instance()->livePadrow(sector,padrow+1)) continue;
	tpc_cl *c = &tpc->cl[padrow][0];
	Int_t ncounts = tpc->cl_counts[padrow];
	for(Int_t j=0;j<ncounts;j++,c++) {
	  if (! c || ! c->charge) continue;
	  if (c->flags &&
	     (c->flags & ~(FCF_ONEPAD | FCF_MERGED | FCF_BIG_CHARGE)))  continue;
	  Int_t iok = hitCollection->addHit(CreateTpcHit(*c,sector,padrow+1));
	  assert(iok);
	}
      }
    }
  } else if (St_tpcPadGainT0BC::instance()->livePadrow(sector,row)) {
    // kReaderType == kStandardTpx
    daq_cld *cld = (daq_cld *) DaqDta()->GetTable();
    if (Debug() > 1) {
      LOG_INFO << Form("CLD sec %2d: row %2d: clusters: %3d",sec, row, NRows) << endm;
    }
    for (Int_t l = 0; l < NRows; l++, cld++) {
      if (Debug() > 1) {
	LOG_INFO << Form("    pad %f[%d:%d], tb %f[%d:%d], cha %d, fla 0x%X",//, Id %d, Q %d ",
			 cld->pad,
			 cld->p1,
			 cld->p2,
			 cld->tb,
			 cld->t1,
			 cld->t2,
			 cld->charge,
			 cld->flags
			 ) << endm;
      }
      if (! cld->pad || ! cld->charge) continue;
      if (cld->tb >= __MaxNumberOfTimeBins__) continue;
      if (cld->flags &&
	 (cld->flags & ~(FCF_ONEPAD | FCF_MERGED | FCF_BIG_CHARGE)))  continue;
      Int_t iok = hitCollection->addHit(CreateTpcHit(*cld,sector,row));
      assert(iok);
    }
  }
  Int_t nhits = hitCollection->numberOfHits() - nhitsBefore;
  if (Debug()) {
    LOG_INFO << " Total hits in Sector : row " << sector << " : " << row << " = " << nhits << endm;
  }
  return nhits;
}
//_____________________________________________________________
StTpcHit *StTpcHitMaker::CreateTpcHit(const tpc_cl &cluster, Int_t sector, Int_t row) {
  // Create  an instance of the StTpcHit from the tpcReader data

  Float_t pad  = cluster.p;
  Float_t time = cluster.t;
  if (kReaderType == kLegacyTpx) time += 22; // remove Tonko's offset
  static StTpcCoordinateTransform transform(gStTpcDb);
  static StTpcLocalSectorCoordinate local;
  static StTpcLocalCoordinate global;
  StTpcPadCoordinate padcoord(sector, row, pad, time);
  transform(padcoord,local,kFALSE);
  transform(local,global);
    
  UInt_t hw = 1;   // detid_tpc
  hw += sector << 4;     // (row/100 << 4);   // sector
  hw += row    << 9;     // (row%100 << 9);   // row
#if 0  
  Int_t npads = TMath::Abs(cluster.p2 - cluster.p1) + 1;
  hw += (npads   << 15);  // npads
  
  Int_t ntmbk = TMath::Abs(cluster.t2 - cluster.t1) + 1;
  hw += (ntmbk << 22);  // ntmbks...
#endif
  static StThreeVector<double> hard_coded_errors(fgDp,fgDt,fgDperp);

  Double_t gain = (row<=NoInnerPadRows) ? St_tss_tssparC::instance()->gain_in() : St_tss_tssparC::instance()->gain_out();
  Double_t wire_coupling = (row<=NoInnerPadRows) ? St_tss_tssparC::instance()->wire_coupling_in() : St_tss_tssparC::instance()->wire_coupling_out();
  Double_t q = cluster.charge * ((Double_t)St_tss_tssparC::instance()->ave_ion_pot() * 
				 (Double_t)St_tss_tssparC::instance()->scale())/(gain*wire_coupling) ;

  StTpcHit *hit = StTpcHitFlag(global.position(),hard_coded_errors,hw,q
			       , (UChar_t ) 0  // c
			       , (UShort_t) 0  // idTruth=0
			       , (UShort_t) 0  // quality=0,
			       , ++fId         // id
			       , cluster.p1 //  mnpad
			       , cluster.p2 //  mxpad
			       , cluster.t1 //  mntmbk
			       , cluster.t2 //  mxtmbk
			       , pad
			       , time 
			       , cluster.charge
			       , cluster.flags);
  if (hit->minTmbk() == 0) bin0Hits++;
//  LOG_INFO << p << " sector " << sector << " row " << row << endm;

  return hit;
}
//_____________________________________________________________
StTpcHit *StTpcHitMaker::CreateTpcHit(const daq_cld &cluster, Int_t sector, Int_t row) {
  // Create  an instance of the StTpcHit from the tpcReader data

  Float_t pad  = cluster.pad;
  Float_t time = cluster.tb;

  Double_t gain = (row<=NoInnerPadRows) ? St_tss_tssparC::instance()->gain_in() : St_tss_tssparC::instance()->gain_out();
  Double_t wire_coupling = (row<=NoInnerPadRows) ? St_tss_tssparC::instance()->wire_coupling_in() : St_tss_tssparC::instance()->wire_coupling_out();
  Double_t q = cluster.charge * ((Double_t)St_tss_tssparC::instance()->ave_ion_pot() * 
				 (Double_t)St_tss_tssparC::instance()->scale())/(gain*wire_coupling) ;

  // Correct for slewing (needs corrected q, and time in microsec)
  Double_t freq = gStTpcDb->Electronics()->samplingFrequency();
  time = freq * St_tpcSlewingC::instance()->correctedT(row,q,time/freq);

  static StTpcCoordinateTransform transform(gStTpcDb);
  static StTpcLocalSectorCoordinate local;
  static StTpcLocalCoordinate global;
  StTpcPadCoordinate padcoord(sector, row, pad, time);
  transform(padcoord,local,kFALSE);
  transform(local,global);
    
  UInt_t hw = 1;   // detid_tpc
  hw += sector << 4;     // (row/100 << 4);   // sector
  hw += row    << 9;     // (row%100 << 9);   // row
#if 0  
  Int_t npads = TMath::Abs(cluster.p2 - cluster.p1) + 1;
  hw += (npads   << 15);  // npads
  
  Int_t ntmbk = TMath::Abs(cluster.t2 - cluster.t1) + 1;
  hw += (ntmbk << 22);  // ntmbks...
#endif
  static StThreeVector<double> hard_coded_errors(fgDp,fgDt,fgDperp);

  StTpcHit *hit = StTpcHitFlag(global.position(),hard_coded_errors,hw,q
			       , (UChar_t ) 0  // c
			       , (UShort_t) 0  // idTruth=0
			       , (UShort_t) 0  // quality=0,
			       , ++fId         // id =0
			       , cluster.p1 //  mnpad
			       , cluster.p2 //  mxpad
			       , cluster.t1 //  mntmbk
			       , cluster.t2 //  mxtmbk
			       , pad
			       , time 
			       , cluster.charge
			       , cluster.flags);
  if (hit->minTmbk() == 0) bin0Hits++;
//  LOG_INFO << p << " sector " << sector << " row " << row << endm;
  return hit;
}
//________________________________________________________________________________
void StTpcHitMaker::DoPulser(Int_t sector) {
  struct Pulser_t {Float_t sector, row, pad, gain, t0, nnoise, noise, npeak;};
  static const Char_t *names = "sector:row:pad:gain:t0:nnoise:noise:npeak";
  static Pulser_t Pulser;
  if (! pulserP) {
    TFile *f = GetTFile();
    assert(f);
    f->cd();
    pulserP = new TNtuple("pulserP","Pulser analysis",names);
  }
  Int_t r, p, tb, tbmax;
  Int_t npeak, nnoise;
  if (! fTpc) return;
  if (! fTpc->channels_sector) return;
  for(Int_t row = 1; row <= NoRows; row++) {
    r = row - 1;
    if (! fTpc->cl_counts[r]) continue;
    for (Int_t pad = 1; pad <= 182; pad++) {
      p = pad - 1;
      Int_t ncounts = fTpc->counts[r][p];
      if (! ncounts) continue;
      static UShort_t adc[512];
      memset (adc, 0, sizeof(adc));
      tbmax = 513;
      UShort_t adcmax = 0;
      for (Int_t i = 0; i < ncounts; i++) {
	tb = fTpc->timebin[r][p][i];
	adc[tb] = log8to10_table[fTpc->adc[r][p][i]]; 
	if (adc[tb] > adcmax) {
	  tbmax = tb;
	  adcmax = adc[tb];
	}
      }
      if (tbmax < 2 || tbmax > 504) continue;
      npeak =  nnoise = 0;
      Int_t i1s = TMath::Max(  0, tbmax - 2);
      Int_t i2s = TMath::Min(511, tbmax + 7);
      Int_t i1  = TMath::Max(0  ,i1s - 20);
      Int_t i2  = TMath::Min(511,i2s + 20);
      Double_t peak = 0;
      Double_t noise = 0;
      Double_t t0 = 0;
      for (Int_t i = i1; i <= i2; i++) {
	if (i >= i1s && i <= i2s) continue;
	nnoise++;
	noise += adc[i];
      }
      if (nnoise) noise /= nnoise;
      for (Int_t i = i1s; i <= i2s; i++) {
	npeak++;
	peak += adc[i] - noise;
	t0   += i*(adc[i] - noise);
      }
      if (peak <= 0) continue;
      t0    /= peak;
      Pulser.sector = sector;
      Pulser.row    = row;
      Pulser.pad    = pad;
      Pulser.gain   = peak;
      Pulser.t0     = t0;
      Pulser.nnoise = nnoise;
      Pulser.noise  = noise;
      Pulser.npeak  = npeak;
      pulserP->Fill(&Pulser.sector);
    }
  }
}
//________________________________________________________________________________
void StTpcHitMaker::TpcAvLaser(Int_t sector) {
  if (! fTpc || !fAvLaser) return;
  Int_t npixels = 0;
  struct pixl_t {
    Double_t sector, row, pad, time;
  };
  if (fAvLaser[sector-1]->GetNbins() > 500000) {
    THnSparseF *hnew = CompressTHn(fAvLaser[sector-1]);
    GetTFile()->Remove(fAvLaser[sector-1]);
    delete fAvLaser[sector-1];
    fAvLaser[sector-1] = hnew;
    GetTFile()->Add(fAvLaser[sector-1]);
  }
  pixl_t pixel;
  pixel.sector = sector;
  for(Int_t r = 0; r < NoRows; r++) {
    pixel.row = r+1;
    for (Int_t pad = 1; pad <= 182; pad++) {
      pixel.pad = pad;
      Int_t p = pad - 1;
      Double_t gain = St_tpcPadGainT0BC::instance()->Gain(pixel.sector,pixel.row,pixel.pad);
      if (gain <= 0) continue;
      Int_t ncounts = fTpc->counts[r][p];
      if (! ncounts) continue;
      for (Int_t i = 0; i < ncounts; i++) {
	pixel.time = fTpc->timebin[r][p][i];
	Double_t adc = log8to10_table[fTpc->adc[r][p][i]]; 
	fAvLaser[sector-1]->Fill(&pixel.row,gain*adc);
	npixels++;
      }
    }
  }
  LOG_INFO << " Total pixels in Sector : " << sector << " = " << npixels  << endm;
}
//________________________________________________________________________________
void StTpcHitMaker::TpxAvLaser(Int_t sector) {
  assert(fAvLaser[sector-1]);
  if (fAvLaser[sector-1]->GetNbins() > 1000000) {
    THnSparseF *hnew = CompressTHn(fAvLaser[sector-1]);
    GetTFile()->Remove(fAvLaser[sector-1]);
    delete fAvLaser[sector-1];
    fAvLaser[sector-1] = hnew;
    GetTFile()->Add(fAvLaser[sector-1]);
  }
  Int_t r=Row() ;	// I count from 1
  if(r==0) return;	// TPC does not support unphy. rows so we skip em
  r-- ;			// TPC wants from 0
  Int_t p = Pad() - 1 ;	// ibid.
  if (p < 0 || p >= St_tpcPadPlanesC::instance()->padsPerRow(r+1)) return;
  struct pixl_t {
    Double_t sector, row, pad, time;
  };
  pixl_t pixel;
  pixel.sector = sector;
  pixel.row = r+1;
  pixel.pad = p+1;
  TGenericTable::iterator iword = DaqDta()->begin();
  for (;iword != DaqDta()->end();++iword) {
    daq_adc_tb &daqadc = (*(daq_adc_tb *)*iword);
    pixel.time   = daqadc.tb;
    Double_t adc  = daqadc.adc;
    if (adc < 6) continue;
    fAvLaser[sector-1]->Fill(&pixel.row,adc);
  }
}
//________________________________________________________________________________
void StTpcHitMaker::DumpPixels2Ntuple(Int_t sector) {
  struct BPoint_t {
    Float_t sector, row, pad, tb, adc, ped, t0, peak;
  };
  static const Char_t *BName = "sector:row:pad:tb:adc:ped:t0:peak";
  static TNtuple *adcP = 0;
  if (! adcP) {
    assert(GetTFile());
    GetTFile()->cd();
    adcP = new TNtuple("adcP","Pulser ADC",BName);
  }
  static BPoint_t P;
  if (! fTpc) return;
  Int_t r, p, tb, tbmax;
  //  if (! fTpc->channels_sector) return;
  for(Int_t row = 1; row <= NoRows; row++) {
    r = row - 1;
    for (Int_t pad = 1; pad <= 182; pad++) {
      p = pad - 1;
      Int_t ncounts = fTpc->counts[r][p];
      if (! ncounts) continue;
      static UShort_t adc[512];
      memset (adc, 0, sizeof(adc));
      tbmax = 513;
      UShort_t adcmax = 0;
      for (Int_t i = 0; i < ncounts; i++) {
	tb = fTpc->timebin[r][p][i];
	adc[tb] = log8to10_table[fTpc->adc[r][p][i]]; 
	if (adc[tb] > adcmax) {
	  tbmax = tb;
	  adcmax = adc[tb];
	}
      }
      if (tbmax < 2 || tbmax > 504) continue;
      Int_t npeak = 0, nped = 0;
      Int_t i1s = TMath::Max(  0, tbmax - 2);
      Int_t i2s = TMath::Min(511, tbmax + 7);
      Int_t i1  = TMath::Max(0  ,i1s - 20);
      Int_t i2  = TMath::Min(511,i2s + 20);
      Double_t peak = 0;
      Double_t ped = 0;
      Double_t t0 = 0;
      for (Int_t i = i1; i <= i2; i++) {
	if (i >= i1s && i <= i2s) continue;
	nped++;
	ped += adc[i];
      }
      if (nped) ped /= nped;
      for (Int_t i = i1s; i <= i2s; i++) {
	npeak++;
	peak += adc[i] - ped;
	t0   += i*(adc[i] - ped);
      }
      if (peak <= 0) continue;
      t0    /= peak;
      i1 = (Int_t) TMath::Max(0.,t0 - 20);
      i2 = (Int_t) TMath::Min(511., t0 + 80);
      for (Int_t i = i1; i <= i2; i++) {
	P.sector = sector;
	P.row    = row;
	P.pad    = pad;
	P.tb     = i - t0;
	P.adc    = adc[i];
	P.ped    = ped;
	P.t0     = t0;
	P.peak   = peak;
	adcP->Fill(&P.sector);
      }
    }
  }
}
//________________________________________________________________________________
void StTpcHitMaker::PrintSpecial(Int_t sector) {
  // example usage: calculate total charge and 
  // print occupancy
  Int_t r,p,t ;
  UInt_t adc = 0;
  UChar_t val ;
  if (! fTpc) return;
  if(fTpc->mode==0) {	// normal event
    UInt_t tot_pix = 0 ;
    UInt_t cl_count = 0 ;
    Int_t i ;
    
    for(r=0;r<NoRows;r++) {	// padrow
      for(p=0;p<182;p++) {	// pad
	for(t=0;t<fTpc->counts[r][p];t++) {	
	  val = fTpc->adc[r][p][t] ;										
	  Int_t vali = log8to10_table[val];
	  adc += val ;
	  if(val) tot_pix++ ;
	  if (Debug() > 1) {
	    Int_t timebin = fTpc->timebin[r][p][t] ;
	    printf("%d %d %d %d %d\n",sector,r+1,p+1,timebin,vali) ;
	  }
	}
      }
      
      if(fTpc->has_clusters) {
	cl_count += fTpc->cl_counts[r] ;
      }
      if (Debug() > 1) {
	if(fTpc->has_clusters) {
	  for(i=0;i<fTpc->cl_counts[r];i++) {
	    tpc_cl *c = &fTpc->cl[r][i] ;
	    
	    printf("%d %d %f %f %d %d %d %d %d %d\n",
		   sector,r+1,c->p,c->t,c->charge,c->flags,c->p1,c->p2,c->t1,c->t2) ;
	  }
	}
      }
    }
    LOG_INFO << Form("TPC: Sector %d: occupancy %3d %%, charge %d, pixels %u, clusters %d",sector,
		     (int)(100.0 *((double)fTpc->channels_sector/(double)fTpc->max_channels_sector)),
		     adc,tot_pix,cl_count) << endm;
  }
}
//________________________________________________________________________________
StTpcDigitalSector *StTpcHitMaker::GetDigitalSector(Int_t sector) {
  TDataSet *event = GetData("Event");
  StTpcRawData *data = 0;
  if (! event) {
    data = new StTpcRawData(24);
    event = new TObjectSet("Event", data);
    AddData(event);
  } else data = (StTpcRawData *) event->GetObject();
  assert(data);
  StTpcDigitalSector *digitalSector = data->GetSector(sector);
  if (! digitalSector) {
    digitalSector = new StTpcDigitalSector();
    data->setSector(sector,digitalSector);
  }
  return digitalSector;
}
//________________________________________________________________________________
Int_t StTpcHitMaker::RawTpxData(Int_t sector) {
  Short_t  ADCs2[512];
  UShort_t IDTs2[512];
  memset(ADCs, 0, sizeof(ADCs));
  memset(IDTs, 0, sizeof(IDTs));
  StTpcDigitalSector *digitalSector = 0;
  Int_t r_old = -1;
  Int_t p_old = -1;
  Int_t Total_data = 0;
  Int_t r=Row() ;	// I count from 1
  if(r==0) return 0 ;	// TPC does not support unphysical rows so we skip them
  r-- ;			// TPC wants from 0
  Int_t p = Pad() - 1 ;	// ibid.
  if (p < 0 || p >= St_tpcPadPlanesC::instance()->padsPerRow(r+1)) return 0;
  TGenericTable::iterator iword = DaqDta()->begin();
  Int_t some_data = 0;
  do {
    if (some_data) {
      Total_data += some_data;
      some_data = 0;
      if (! digitalSector) digitalSector = GetDigitalSector(sector);
      Int_t ntbold = digitalSector->numberOfTimeBins(r_old+1,p_old+1);
      if (ntbold) {
#if 0
	LOG_INFO << "digitalSector " << sector 
		 << " already has " << ntbold << " time bins at row/pad " << r_old+1 <<  "/" << p_old+1 << endm;
#endif
	digitalSector->getTimeAdc(r_old+1,p_old+1,ADCs2,IDTs2);
	for (Int_t i = 0; i < __MaxNumberOfTimeBins__; i++) {
	  if (! ADCs2[i]) continue;
	  if ((IDTs[i] || IDTs2[i]) && ADCs[i] < ADCs2[i]) IDTs[i] = IDTs2[i];
	  ADCs[i] += ADCs2[i];
	}
      }
      digitalSector->putTimeAdc(r_old+1,p_old+1,ADCs,IDTs);
      memset(ADCs, 0, sizeof(ADCs));
      memset(IDTs, 0, sizeof(IDTs));
    }
    if (r_old != r || p_old != p) {
      r_old = r;
      p_old = p;
    }
    for (;iword != DaqDta()->end();++iword) {
      daq_adc_tb &daqadc = (*(daq_adc_tb *)*iword);
      Int_t tb   = daqadc.tb;
      Int_t adc  = daqadc.adc;
      ADCs[tb] = adc;
      some_data++ ;	// I don't know the bytecount but I'll return something...
    }
  } while (some_data);
  return Total_data;
}
//________________________________________________________________________________
Int_t StTpcHitMaker::RawTpcData(Int_t sector) {
  if (! fTpc) return 0;
  memset(ADCs, 0, sizeof(ADCs));
  memset(IDTs, 0, sizeof(IDTs));
  StTpcDigitalSector *digitalSector = 0;
  Int_t Total_data = 0;
  for (Int_t row = 1;  row <= NoRows; row++) {
      Int_t r = row - 1;
      if (! digitalSector) digitalSector = GetDigitalSector(sector);
      for (Int_t pad = 1; pad <= digitalSector->numberOfPadsAtRow(row); pad++) {
         Int_t p = pad - 1;
         memset(ADCs, 0, sizeof(ADCs));
         memset(IDTs, 0, sizeof(IDTs));
         Int_t ncounts = fTpc->counts[r][p];
         if (! ncounts) continue;
         for (Int_t i = 0; i < ncounts; i++) {
            Int_t tb = fTpc->timebin[r][p][i];
            ADCs[tb] = log8to10_table[fTpc->adc[r][p][i]]; 
            IDTs[tb] = 65535;
            Total_data++;
         }
         Int_t ntbold = digitalSector->numberOfTimeBins(row,pad);
         if (ntbold) {
#if 0
            LOG_INFO << "digitalSector " << sector 
                     << " already has " << ntbold << " at row/pad " << row <<  "/" << pad << endm;
#endif
         }
         digitalSector->putTimeAdc(row,pad,ADCs,IDTs);
      }
    }									
    if (Total_data) {
      LOG_INFO << "Read " << Total_data << " pixels from Sector " << sector << endm;
    }
    return Total_data;
}
//________________________________________________________________________________
#ifdef __MAKE_NTUPLE__
static TNtuple *tup = 0;
struct TpcHitPair_t {
  Float_t sec, row, 
    qK, padK, tbkK, padKmn, padKmx, tbkKmn, tbkKmx, IdTK, QAK,
    qL, padL, tbkL, padLmn, padLmx, tbkLmn, tbkLmx, IdTL, QAL,
    padOv, tbkOv;
};
static const Char_t *vTpcHitMRPair = "sec:row:"
  "qK:padK:tbkK:padKmn:padKmx:tbkKmn:tbkKmx:IdTK:QAK:"
  "qL:padL:tbkL:padLmn:padLmx:tbkLmn:tbkLmx:IdTL:QAL:"
  "padOv:tbkOv";
#endif
//________________________________________________________________________________
Bool_t TpcHitLess(const StTpcHit *lhs, const StTpcHit *rhs) {
  return (200*lhs->timeBucket() + lhs->pad()) < (200*rhs->timeBucket() + rhs->pad());
};
//________________________________________________________________________________
void StTpcHitMaker::AfterBurner(StTpcHitCollection *TpcHitCollection) {
  static Float_t padDiff = 2.5, timeBucketDiff = 5.0;
  static StTpcCoordinateTransform transform(gStTpcDb);
  static StTpcLocalSectorCoordinate local;
  static StTpcLocalCoordinate global;
  if (! TpcHitCollection) return;
#ifdef __MAKE_NTUPLE__
  if (! tup) {
    if (StChain::GetChain()->GetTFile()) {
      StChain::GetChain()->GetTFile()->cd();
      tup = new TNtuple("HitT","Cluster Pair Info",vTpcHitMRPair);
    }
  }
  TpcHitPair_t pairC;
#endif
  UInt_t numberOfSectors = TpcHitCollection->numberOfSectors();
  for (UInt_t sec = 1; sec <= numberOfSectors; sec++) {
    StTpcSectorHitCollection* sectorCollection = TpcHitCollection->sector(sec-1);
    if (sectorCollection) {
      UInt_t numberOfPadrows = sectorCollection->numberOfPadrows();
      for (UInt_t row = 1; row <= numberOfPadrows; row++) {
	StTpcPadrowHitCollection *rowCollection = TpcHitCollection->sector(sec-1)->padrow(row-1);
	if (rowCollection) {
	  UInt_t NoHits = rowCollection->hits().size();
	  if (NoHits < 2) continue;
	  sort(rowCollection->hits().begin(),
	       rowCollection->hits().end(),
	       TpcHitLess);
	  // Merge splitted clusters
	  Int_t merged = 0;
	  for (UInt_t k = 0; k < NoHits; k++) {
	    StTpcHit* kHit = TpcHitCollection->sector(sec-1)->padrow(row-1)->hits().at(k);
	    if (_debug) {cout << "k " << k; kHit->Print();}
	    if (kHit->flag())                          continue;
#ifdef __MAKE_NTUPLE__
	    pairC.sec    = sec;
	    pairC.row    = row;
	    pairC.qK     = kHit->charge();
	    pairC.padK   = kHit->pad();
	    pairC.tbkK   = kHit->timeBucket();
	    pairC.padKmn = kHit->minPad();
	    pairC.padKmx = kHit->maxPad();
	    pairC.tbkKmn = kHit->minTmbk();
	    pairC.tbkKmx = kHit->maxTmbk();
	    pairC.IdTK   = kHit->idTruth();
	    pairC.QAK    = kHit->qaTruth();
#endif
	    for (UInt_t l = 0; l < NoHits; l++) {
	      if (k == l) continue;
	      StTpcHit* lHit = TpcHitCollection->sector(sec-1)->padrow(row-1)->hits().at(l);
	      if (_debug) {cout << "l " << l; lHit->Print();}
	      if (lHit->flag()) continue;
	      // Are extends overlapped ?
	      Int_t padOverlap = TMath::Min(kHit->maxPad(),lHit->maxPad())
		-                TMath::Max(kHit->minPad(),lHit->minPad());
	      if (padOverlap < 0) continue;
	      Int_t tmbkOverlap = TMath::Min(kHit->maxTmbk(),lHit->maxTmbk()) 
		-                 TMath::Max(kHit->minTmbk(),lHit->minTmbk());
	      if (tmbkOverlap < 0) continue;
#ifdef __MAKE_NTUPLE__
	      if (tup) {
		pairC.qL     = lHit->charge();
		pairC.padL   = lHit->pad();
		pairC.tbkL   = lHit->timeBucket();
		pairC.padLmn = lHit->minPad();
		pairC.padLmx = lHit->maxPad();
		pairC.tbkLmn = lHit->minTmbk();
		pairC.tbkLmx = lHit->maxTmbk();
		pairC.IdTL   = lHit->idTruth();
		pairC.QAL    = lHit->qaTruth();
		pairC.padOv  = padOverlap;    
		pairC.tbkOv  = tmbkOverlap;
		tup->Fill(&pairC.sec);
	      }
#endif
	      // check hits near by
	      if (TMath::Abs(kHit->pad()        - lHit->pad())        > padDiff ||
		  TMath::Abs(kHit->timeBucket() - lHit->timeBucket()) > timeBucketDiff) continue;
#ifdef FCF_CHOPPED
	      UShort_t flag = lHit->flag() | FCF_CHOPPED; 
#else
	      UShort_t flag = lHit->flag() | 0x080;
#endif
	      lHit->setFlag(flag);
	      if (_debug) {
		cout << "mk" << k; kHit->Print();
		cout << "ml" << l; lHit->Print();
	      }
	      Float_t q          =  lHit->charge()                    + kHit->charge();	
	      Float_t adc        =  lHit->adc()                       + kHit->adc();
	      Float_t pad        = (lHit->charge()*lHit->pad()        + kHit->charge()*kHit->pad()       )/q;
	      Float_t timeBucket = (lHit->charge()*lHit->timeBucket() + kHit->charge()*kHit->timeBucket())/q;
	      Short_t minPad  = TMath::Min(lHit->minPad(),  kHit->minPad());
	      Short_t maxPad  = TMath::Max(lHit->maxPad(),  kHit->maxPad());
	      Short_t minTmbk = TMath::Min(lHit->minTmbk(), kHit->minTmbk());
	      Short_t maxTmbk = TMath::Max(lHit->maxTmbk(), kHit->maxTmbk());
	      Int_t IdT = lHit->idTruth();
	      Double_t QA = lHit->charge()*lHit->qaTruth();
	      if (IdT == kHit->idTruth()) {
		QA += kHit->charge()*kHit->qaTruth();
	      } else {
		if (lHit->charge()*lHit->qaTruth() < kHit->charge()*kHit->qaTruth()) {
		  QA = kHit->charge()*kHit->qaTruth();
		  IdT = kHit->idTruth();
		}
	      }
	      QA = QA/q;
	      kHit->setIdTruth(IdT, TMath::Nint(QA));
	      kHit->setCharge(q);
	      kHit->setExtends(pad,timeBucket,minPad,maxPad,minTmbk,maxTmbk);
	      kHit->setAdc(adc);
	      StTpcPadCoordinate padcoord(sec, row, pad, timeBucket);
	      transform(padcoord,local,kFALSE);
	      transform(local,global);
	      kHit->setPosition(global.position());
	      if (_debug) {
		cout << "m " << k; kHit->Print();
	      }
	      merged++;
	    }
	  }
#ifdef __CORRECT_S_SHAPE__
	  // Correct S - shape in pad direction
	  for (UInt_t k = 0; k < NoHits; k++) {
	    StTpcHit* kHit = TpcHitCollection->sector(sec-1)->padrow(row-1)->hits().at(k);
	    if (kHit->flag())                         continue;
	    Double_t pad        = kHit->pad();
	    Double_t timeBucket = kHit->timeBucket();
	    Int_t io = 1;
	    if (row > NoInnerPadRows) io = 2;
	    Int_t np = kHit->padsInHit();
	    pad += St_TpcPadCorrectionC::instance()->GetCorrection(pad,io,np,0);
	    StTpcPadCoordinate padcoord(sec, row, pad, timeBucket);
	    transform(padcoord,local,kFALSE);
	    transform(local,global);
	    kHit->setPosition(global.position());
	  }
#endif
	}
      }
    }
  }
  return;
};
//________________________________________________________________________________
StTpcHit* StTpcHitMaker::StTpcHitFlag(const StThreeVectorF& p,
             const StThreeVectorF& e,
             UInt_t hw, float q, UChar_t c,
             UShort_t idTruth, UShort_t quality,
             UShort_t id,
             Short_t mnpad, Short_t mxpad, Short_t mntmbk,
             Short_t mxtmbk, Float_t cl_x, Float_t cl_t, UShort_t adc,
             UShort_t flag) {
  // New hit
  StTpcHit* hit = new StTpcHit(p,e,hw,q,c,idTruth,quality,id,mnpad,mxpad,mntmbk,mxtmbk,cl_x,cl_t,adc);

  // Check for sanity
  if ( mntmbk<0 || mxtmbk<0 || mntmbk>32000 || mxtmbk>32000
    || mnpad <0 || mxpad <0 || mnpad >32000 || mxpad >32000
    || mxpad-mnpad > 100
    || (Float_t) mntmbk>cl_t || (Float_t) mxtmbk<cl_t
    || (Float_t) mnpad >cl_x || (Float_t) mxpad <cl_x
     ) flag |= FCF_SANITY;
  hit->setFlag(flag);
  return hit;
}
//________________________________________________________________________________
THnSparseF *StTpcHitMaker::CompressTHn(THnSparseF *hist, Double_t compress) { 
  if (! hist) return 0;
  Int_t nd = hist->GetNdimensions();
  Int_t *nbins = new  Int_t[nd];
  for (Int_t i = 0; i < nd; i++) nbins[i] = hist->GetAxis(i)->GetNbins();
  THnSparseF *hnew = new THnSparseF(hist->GetName(),hist->GetTitle(),nd, nbins, 0, 0);//, hist->GetChunkSize());
  hnew->CalculateErrors(kTRUE);
  delete [] nbins;
  for (Int_t i = 0; i < nd; i++) {
    TAxis *ax = hist->GetAxis(i);
    if (ax->IsVariableBinSize()) hnew->GetAxis(i)->Set(ax->GetNbins(), ax->GetXbins()->GetArray());
    else                         hnew->GetAxis(i)->Set(ax->GetNbins(), ax->GetXmin(), ax->GetXmax());
  }
  Int_t *bins = new Int_t[nd];
  Double_t *x = new Double_t[nd];
  Long64_t N = hist->GetNbins(); cout << hist->GetName() << " has " << N << " bins before compression." << endl;
  Double_t max = -1;
  for (Long64_t i = 0; i < N; ++i) {
    Double_t cont = hist->GetBinContent(i, bins);
    if (cont > max) max = cont;
  }
  for (Long64_t i = 0; i < N; ++i) {
    Double_t cont = hist->GetBinContent(i, bins);
    if (cont < max/compress) continue;
    //    Long64_t bin = hnew->GetBin(bins);
    for (Int_t d = 0; d < nd; ++d) {x[d] = hist->GetAxis(d)->GetBinCenter(bins[d]);}
    hnew->Fill(x,cont);
  }
  delete [] bins;
  delete [] x;
  cout << hnew->GetName() << " has " << hnew->GetNbins() << " bins after compression." << endl;
  return hnew;
}
