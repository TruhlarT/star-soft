// $Id: StEventMaker.cxx,v 1.2 1999/05/05 22:38:00 fisyak Exp $
// $Log: StEventMaker.cxx,v $
// Revision 1.2  1999/05/05 22:38:00  fisyak
// Add gulfd for magnetic field
//
// Revision 1.1  1999/05/04 22:40:35  fisyak
// Initial revision of persistent StEventMaker
//
// Revision 1.12  1999/05/03 01:39:22  fisyak
// Remove tables from DST, add access to different makers
//
// Revision 1.11  1999/05/01 01:49:15  fisyak
// Add StRootEvent fill
//
// Revision 1.10  1999/05/01 00:57:03  fisyak
// Change Clear function to defualt
//
// Revision 1.19  1999/03/30 15:47:30  wenaus
// update to new maker scheme
//
// Revision 1.18  1999/03/19 17:53:20  wenaus
// don't fill empty CTB,MWC bins
//
// Revision 1.17  1999/03/19 17:35:33  wenaus
// incorporate tolerance of missing start, stop vertex from Joakim Nystrand
//
// Revision 1.16  1999/03/19 17:23:12  wenaus
// Load trigger detectors
//
// Revision 1.15  1999/03/01 01:24:08  genevb
// Assign primary vertex, get start and stop vertices right for tracks
//
// Revision 1.14  1999/02/25 22:36:30  wenaus
// corrected FTPC hit IDs
//
// Revision 1.13  1999/02/25 17:08:54  wenaus
// temporary suppression of unknown ID messages
//
// Revision 1.12  1999/02/24 23:13:45  wenaus
// gentler EOF message
//
// Revision 1.11  1999/02/24 18:30:30  wenaus
// dst_tof elimination; changes for ROOT
//
//
// Revision 1.10  1999/02/24 12:51:38  ullrich
// Modified calculation of helix parameters of global tracks.
// New argument passed to StGlobalTrack constructor.
//
// Revision 1.9  1999/02/24 01:56:13  genevb
// Add Xi vertices
//
// Revision 1.8  1999/02/22 20:52:18  wenaus
// clean up delete handling
//
// Revision 1.7  1999/02/22 20:26:24  genevb
// Temporary fix of vertex indexing
//
// Revision 1.6  1999/02/21 20:33:05  genevb
// Improve StV0Vertex code
//
// Revision 1.5  1999/02/12 02:00:06  wenaus
// load tracks using new constructor
//
// Revision 1.4  1999/02/10 23:15:19  wenaus
// multi-file processing changes; leak fixes
//
// Revision 1.3  1999/02/10 15:33:25  wenaus
// Speed up vtx->trk ref loading. Tested on Solaris, Linux
//
// Revision 1.2  1999/02/05 17:51:54  wenaus
// Vertex loading via index() method
//
// Revision 1.1  1999/01/30 23:06:37  wenaus
// Maker to read from tables or Objy into StEvent
//
//
///////////////////////////////////////////////////////////////////////////////
//
// StEventReaderMaker
//
// Description: 
//
// Environment:
//  Software developed for the STAR Detector at Brookhaven National Laboratory
//
// Author List: 
//  Torre Wenaus, BNL
//
// History:
//
///////////////////////////////////////////////////////////////////////////////
// $Id: StEventMaker.cxx,v 1.2 1999/05/05 22:38:00 fisyak Exp $
// $Log: StEventMaker.cxx,v $
// Revision 1.2  1999/05/05 22:38:00  fisyak
// Add gulfd for magnetic field
//
// Revision 1.1  1999/05/04 22:40:35  fisyak
// Initial revision of persistent StEventMaker
//
// Revision 1.12  1999/05/03 01:39:22  fisyak
// Remove tables from DST, add access to different makers
//
// Revision 1.11  1999/05/01 01:49:15  fisyak
// Add StRootEvent fill
//
// Revision 1.10  1999/05/01 00:57:03  fisyak
// Change Clear function to defualt
//
// Revision 1.9  1999/03/11 03:12:17  perev
// new schema
//
// Revision 1.8  1999/02/26 02:31:55  fisyak
// Replace emc hits by emc raw tables
//
// Revision 1.7  1999/02/23 02:09:02  fisyak
// Add emc hits to dst
//
// Revision 1.6  1999/02/20 18:49:16  fisyak
// Add event/run information
//
// Revision 1.5  1999/02/19 17:37:42  fisyak
// Add RICH hits to dst
//
// Revision 1.4  1999/02/19 17:35:47  fisyak
// Add RICH hits to dst
//
// Revision 1.2  1999/01/20 23:58:03  fisyak
// Tree 2 GetTree
//
// Revision 1.1  1999/01/02 19:09:22  fisyak
// Add Clones
//
// Revision 1.7  1998/10/31 00:25:45  fisyak
// Makers take care about branches
//
// Revision 1.6  1998/10/06 18:00:29  perev
// cleanup
//
// Revision 1.5  1998/10/02 13:46:08  fine
// DataSet->DataSetIter
//
// Revision 1.4  1998/08/14 15:25:58  fisyak
// add options
//
// Revision 1.3  1998/08/10 02:32:07  fisyak
// Clean up
//
// Revision 1.2  1998/07/20 15:08:15  fisyak
// Add tcl and tpt
//
//////////////////////////////////////////////////////////////////////////
//                                                                      //
// StEventMaker class for Makers                                        //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

 * no dst dataset is available.
#include "StEventMaker.h"
 *
 * Revision 2.24  2000/05/24 15:48:15  ullrich
 * Instance of StEvent now also created if no DST dataset
 * is available.
#include "StRun.h"
#include "StEvent.h"
#include "StGlobalTrack.h"
#include "StDedx.h"
#include "StTpcHit.h"
#include "StFtpcHit.h"
#include "StSvtHit.h"
#include "StHit.h"
#include "StVertex.h"
#include "StV0Vertex.h"
#include "StXiVertex.h"

static const char rcsid[] = "$Id: StEventMaker.cxx,v 1.2 1999/05/05 22:38:00 fisyak Exp $";
#include "StEventManager.h"
StEventManager MakerEventManager;
 * Revision 2.23  2000/05/22 21:53:41  ullrich
const long detid_tpc = 1;
const long detid_svt = 2;
const long detid_ftpcWest = 4;
const long detid_ftpcEast = 5;

ooStatus status;

// For local use
dst_run_header_st dummy_hdr;
dst_event_header_st dstEventHeader;
dst_event_summary_st dstEventSummary;
dst_monitor_hard_st dstMonitorHard;
dst_monitor_soft_st dstMonitorSoft;
gen_header_st genHeader;
particle_st particle;
dst_TriggerDetectors_st dstTriggerDetectors;
long i;
//#include "fortranc.h"
//#define gufld_ F77_NAME(gufld,GUFLD)
//R__EXTERN  void type_of_call gufld_(Float_t *x, Float_t *b);
// Option to suppress loading of StEvent, for debugging & leak checking
#define gufld   gufld_
//#define gufld   GUFLD
extern "C" {void gufld(Float_t *, Float_t *);}
Bool_t doLoad = kTRUE;
#include "StTrack.h"

 * zero length. Added for primary and global tracks.
#include "St_ObjectSet.h"
  //_____________________________________________________________________________
  StEventMaker::StEventMaker(const char *name):StMaker(name){
  setEventManager(&MakerEventManager);
  currentRun = 0;
  currentEvent = 0;
    doPrintEventInfo  = kTRUE;  // TMP, set to fFALSE later
//_____________________________________________________________________________
StEventMaker::~StEventMaker(){
 *
 * Revision 2.7  1999/11/17 14:10:27  ullrich
//_____________________________________________________________________________
Int_t StEventMaker::Init(){
  // Create Histograms    
  return StMaker::Init();
    doPrintRunInfo    = kTRUE;  // TMP 
//_____________________________________________________________________________
Int_t StEventMaker::Make(){
  dst_run_header_st& dstRunHeader = dummy_hdr;
  St_DataSet *global = GetInputDS("dst");
  if (! global) return kStErr;
  theEventManager->ResetDstIter(global);
  status = theEventManager->readRunHeader(dstRunHeader);
  if (status) {
    cout << "StEventReaderMaker: Run header: ID " << dstRunHeader.run_id << endl;
    /* run summary not used
       dst_run_summary_st dummy_sum;
       dst_run_summary_st& dstRunSummary = dummy_sum;
       status = theEventManager->readRunSummary(dstRunSummary);
       if (status) {
       cout << "StEventReaderMaker: Run summary found" << endl;
       // Create transient run header
       currentRun = new StRun(dstRunHeader, dstRunSummary);
       } else {
       currentRun = new StRun(dstRunHeader);
       }
    */
    if (doLoad) {
      if (currentRun) delete currentRun;
      currentRun = new StRun(dstRunHeader);
      AddConst(currentRun);
    }
 * Revised to build new StEvent version
    // Since this is a run header record, there is no event data
    // so we're finished
    //    currentEvent = 0;
    //    theEventManager->closeEvent();
    return kStOK;
  }
  
  cout << "StEventReaderMaker: Reading Event" << endl;
  theEventManager->readHeader(dstEventHeader);
  status = theEventManager->readTable(dstEventSummary);
  // Create transient event header
  if (doLoad) {
    currentEvent = new StEvent(currentRun,
                               dstEventHeader,
                               dstEventSummary);
    AddData(currentEvent);
  }
  
  status = theEventManager->readTable(dstMonitorHard);
  if (status) {
    cout << "StEventReaderMaker: Found dstMonitorHard" << endl;
  }
  status = theEventManager->readTable(dstMonitorSoft);
  if (status) {
    cout << "StEventReaderMaker: Found dstMonitorSoft" << endl;
  }
  
  // Read and load trigger detector data
  St_DataSet *trg = GetInputDS("trg");
  if (!trg) trg = GetInputDS("dst");
  if (trg) {
    theEventManager->ResetDstIter(trg);
    status = theEventManager->readTable(dstTriggerDetectors);
    if (status) {
      cout << "StEventReaderMaker: Loading triggerDetectors" << endl;
      StTriggerDetectorCollection *trgDets =
	currentEvent->triggerDetectorCollection();
      // Load CTB data
      StCtbCounter* ctb;
      for (i=0; i<240; i++) {
	if (dstTriggerDetectors.nCtb[i] > 0) {
	  ctb = new StCtbCounter( i, 
				  dstTriggerDetectors.nCtb[i],
				  dstTriggerDetectors.timeCtb[i]);
	  trgDets->ctbCounters().push_back(ctb);
	}
      }
      // Load MWC data
      StMwcSector* mwc;
      for (i=0; i<96; i++) {
	if (dstTriggerDetectors.nMwc[i] > 0) {
	  mwc = new StMwcSector( i, dstTriggerDetectors.nMwc[i]);
	  trgDets->mwcSectors().push_back(mwc);
	}
      }
      // Load VPD data
      StVpdCounter* vpd;
      for (i=0; i<48; i++) {
	// No filling code exists, so no criteria to ignore empty bins
	vpd = new StVpdCounter( i,
				dstTriggerDetectors.adcVPD[i],
				dstTriggerDetectors.timeVPD[i]);
	trgDets->vpdCounters().push_back(vpd);
      }
      trgDets->vpdSummary().setVertexZ(dstTriggerDetectors.vertexZ);
      trgDets->vpdSummary().setMinimumTime(east,dstTriggerDetectors.TimeEastVpd);
      trgDets->vpdSummary().setMinimumTime(west,dstTriggerDetectors.TimeWestVpd);
      // Load ZDC data
      StZdcSegment* zdc;
      for (i=0; i<6; i++) {
	// No filling code exists, so no criteria to ignore empty bins
	zdc = new StZdcSegment( i,
				dstTriggerDetectors.adcZDC[i],
				dstTriggerDetectors.tdcZDC[i]);
	trgDets->zdcSegments().push_back(zdc);
      }
      trgDets->zdcSummary().setAdcSum(dstTriggerDetectors.adcZDCsum);
      trgDets->zdcSummary().setAdcSum(east,dstTriggerDetectors.adcZDCEast);
      trgDets->zdcSummary().setAdcSum(west,dstTriggerDetectors.adcZDCWest);
    }
  } // end of Trigger part
  St_DataSet *geant = GetInputDS("geant");
  if (!geant) geant = GetInputDS("dst");
  if (geant) {
    theEventManager->ResetDstIter(geant);
    status = theEventManager->readTable(particle);
    if (status) {
      /*
	// load genHeader table from particle
	genHeader.bimp = particle.phep[0];
	genHeader.phi = particle.phep[1];
	genHeader.genid = particle.phep[2];
	genHeader.ecms = particle.phep[3];
	int aWest = int(particle.phep[4]);
	int aEast = (particle.phep[4]-aWest)*1000;
	genHeader.awest = aWest;
	genHeader.aeast = aEast;
	genHeader.run = particle.vhep[0];
	genHeader.event = particle.vhep[1];
	genHeader.date = particle.vhep[2];
	genHeader.time = particle.vhep[3];
	objyEventManager->loadTable(&genHeader);
      */
        return kStWarn;
  }
  if (global) {
    theEventManager->ResetDstIter(global);
    // Load and create tracks, vertices etc. and add to collections
    long nDedx, nPoint, nTrack, nTrackAux, nVertex, nV0Vertex, nXiVertex;
    long nTofTrk, nTofEvt;
    
    // *** BEGIN VERTEX BUILDING ***
    // build a vector of vertex addresses to use in lieu of an index
    // during vertex->track pointer loading. Assumes (requires!) that
    // vertices are ordered
    
    // First, find the total number of vertices
    StVertexCollection vtxPtr("MyVertices");
    int indexCount = 0;                    // count vertices added to collection
    int vertexMatchIndex[20000];
    dst_vertex_st* dstVertex = theEventManager->returnTable_dst_vertex(nVertex);
    for (i=0; i<nVertex; i++) vertexMatchIndex[i]=-1;
    
    // Second, deal with xi's
    dst_xi_vertex_st* dstXiVertex = theEventManager->returnTable_dst_xi_vertex(nXiVertex);
    if (nXiVertex > nVertex)
      cout << "StEventReaderMaker: Warning - more Xi's than vertices" << endl;
    if (dstXiVertex) {
      cout << "StEventReaderMaker: " << nXiVertex << " dst_xi_vertex" << endl;
      // Add Xi vertices to vertex collection
      if (doLoad) {
	StVertex* vtx = NULL;
	long vertex_id;
	for (i=0; i<nXiVertex; i++) {
	  vertex_id = dstXiVertex[i].id_xi;
	  vertexMatchIndex[vertex_id-1] = indexCount;
	  vtx = (StVertex*) new StXiVertex(&(dstXiVertex[i]), &(dstVertex[vertex_id]) );
	  // Add associated v0's during v0 loop
	  vtx->setIndex(indexCount++);
	  currentEvent->vertexCollection()->push_back(vtx);
	  vtxPtr.push_back(vtx);
	}
      }
        StXiVertex *xi = new StXiVertex(dstVertices[id], dstXiVertices[i]);
    
    // Third, deal with v0's
    dst_v0_vertex_st* dstV0Vertex = theEventManager->returnTable_dst_v0_vertex(nV0Vertex);
    if (nV0Vertex > nVertex)
      cout << "StEventReaderMaker: Warning - more V0's than vertices" << endl;
    if (dstV0Vertex) {
      cout << "StEventReaderMaker: " << nV0Vertex << " dst_v0_vertex" << endl;
      // Add V0 vertices to vertex collection
      if (doLoad) {
	StVertex* vtx = NULL;
	long vertex_id;
	long xi_index = 0;
	for (i=0; i<nV0Vertex; i++) {
	  vertex_id = dstV0Vertex[i].id_vertex;
	  vertexMatchIndex[vertex_id-1] = indexCount;
	  vtx = (StVertex*) new StV0Vertex(&(dstV0Vertex[i]), &(dstVertex[vertex_id]) );
	  vtx->setIndex(indexCount++);
	  currentEvent->vertexCollection()->push_back(vtx);
	  vtxPtr.push_back(vtx);
	  // Add associated v0's to xi's
	  //  - take advantage of ordered xi/v0 tables
	  //  - take advantage of xi's being added to vtxPtr first
	  if (dstXiVertex) {
	    while ((xi_index<nXiVertex) &&
		   (dstXiVertex[xi_index].id_v0 == dstV0Vertex[i].id) )
	      ((StXiVertex*) (vtxPtr[xi_index++]))->setV0Vertex((StV0Vertex*) vtx);
	  }
	}
      }
    }    
    
    // Last for the vertices, add any un-accounted-for vertices (primary)
    if (dstVertex) {
      cout << "StEventReaderMaker: " << nVertex << " dst_vertex" << endl;
      // Build vertex collection
      if (doLoad) {
	StVertex* vtx = NULL;
	for (i=0; i<nVertex; i++) {
	  if (vertexMatchIndex[i]<0) {
	    vertexMatchIndex[i] = indexCount;
	    vtx = new StVertex(&(dstVertex[i]) );
	    vtx->setIndex((ULong_t)indexCount++);
	    currentEvent->vertexCollection()->push_back(vtx);
	    vtxPtr.push_back(vtx);
	  }
	}
	if (vtx) currentEvent->setPrimaryVertex(vtx); // Last vertex is primary?
      }
    }
    // *** END VERTEX BUILDING ***
    
    dst_track_st* dstTrack = theEventManager->returnTable_dst_track(nTrack);
    if (dstTrack) {
      cout << "StEventReaderMaker: " << nTrack << " dst_track" << endl;
      if (doLoad) {
	StGlobalTrack* trk = NULL;
	for (i=0; i<nTrack; i++) {
	  // Extract fit params: curv, dip, phase, origin
	  dst_track_st& tktbl = dstTrack[i];
	  // $$$ get field from somewhere!
	  Float_t x[3] = {0,0,0};
	  Float_t b[3];
	  gufld(x,b);
	  double B     = b[2]*kilogauss;
	  //
	  //   Derive the helix parameter from the variables
	  //   stored in the table.
	  //
	  double dip   = atan(tktbl.tanl);
	  int    h     = (B*tktbl.icharge > 0 ? -1 : 1);  // -sign(q*B)
	  double phase = tktbl.psi*degree-h*pi/2;
	  double pt    = (1./tktbl.invpt)*GeV;
	  double curvature = fabs(c_light*nanosecond/meter*tktbl.icharge*B/tesla)/(pt/GeV); // in meter^-1	
	  StThreeVectorF origin(tktbl.x0, tktbl.y0, tktbl.z0);  // in centimeter
	  
	  //   Create the track, pass the helix parameter (note h)
	  trk = new StGlobalTrack(&(dstTrack[i]),
				  curvature/meter,
				  dip*radian,
				  phase*radian,
				  origin*centimeter,
				  h);
	  currentEvent->trackCollection()->push_back(trk);
	  // add the track to vertex
	  unsigned long idStartVertex = dstTrack[i].id_start_vertex;
	  unsigned long idStopVertex = dstTrack[i].id_stop_vertex;
	  // For now, if start or stop vertex id is zero, assume it is the primary
	  //  vertex, even though the primary vertex should not be a stop vertex
	  StVertex* startVertex = 0;
	  StVertex* stopVertex = 0;
	  if (idStartVertex == 0) {
	    startVertex = currentEvent->primaryVertex();
	  } else {
	    if ( idStartVertex > 0 && idStartVertex <= vtxPtr.size() ) {
	      startVertex = vtxPtr[vertexMatchIndex[--idStartVertex]];
	    } else {
	      cout << "StEventReaderMaker: WARNING: idStartVertex " << idStartVertex <<
		" either null or larger than vertex list " << vtxPtr.size() << endl;
	    }
	  }
	  if (idStopVertex == 0) {
	    stopVertex  = currentEvent->primaryVertex();
	  } else {
	    if ( idStopVertex > 0 && idStopVertex <= vtxPtr.size() ) {
	      stopVertex  = vtxPtr[vertexMatchIndex[--idStopVertex]];
	    } else {
	      cout << "StEventReaderMaker: WARNING: idStopVertex " << idStopVertex <<
		" either null or larger than vertex list " << vtxPtr.size() << endl;
	    }
	  }
	  // Load the appropriate vertex info using the vertex pointer vector
	  if ( startVertex ) {
	    trk->setStartVertex(startVertex);
	    startVertex->daughters().push_back(trk); // Add track to start vtx daughters
	  }
	  if ( stopVertex ) {
	    trk->setStopVertex(stopVertex);
	    stopVertex->setParent(trk); // Set track as stop vtx
	  }
	}
      }
    }  
    
    dst_track_aux_st* dstTrackAux = theEventManager->returnTable_dst_track_aux(nTrackAux);
    if (dstTrackAux) {
      cout << "StEventReaderMaker: " << nTrackAux << " dst_track_aux" << endl;
      // Add auxiliary info to tracks
      if (doLoad) {
	StGlobalTrack* theTrack;
	StTrackCollection* theTrackCollection = currentEvent->trackCollection();
	long itrk;
	for (i=0; i<nTrackAux; i++) {
	  dst_track_aux_st* theTrackAux = &dstTrackAux[i];
	  itrk = theTrackAux->id_track-1;
	  // theTrack = (*theTrackCollection)[itrk]; // id_track isn't filled, apparently
	  theTrack = (*theTrackCollection)[i]; // Less safe, but with no ID, what else can we do
	  // Load auxiliary info into track
	  if (theTrack) {
	    // $$$ where to put resids. They aren't loaded at present either.
	    //        = dstTrackAux[i].residuals[0];
	    //        = dstTrackAux[i].residuals[1];
	    theTrack->fitTraits().covariantMatrix()(1,2) = 
	      dstTrackAux[i].covar_off_diag[0];
	    theTrack->fitTraits().covariantMatrix()(2,1) = 
	      dstTrackAux[i].covar_off_diag[0];
	    theTrack->fitTraits().covariantMatrix()(1,3) = 
	      dstTrackAux[i].covar_off_diag[1];
	    theTrack->fitTraits().covariantMatrix()(3,1) = 
	      dstTrackAux[i].covar_off_diag[1];
	    theTrack->fitTraits().covariantMatrix()(2,3) = 
	      dstTrackAux[i].covar_off_diag[2];
	    theTrack->fitTraits().covariantMatrix()(3,2) = 
	      dstTrackAux[i].covar_off_diag[2];
	    theTrack->fitTraits().covariantMatrix()(1,4) = 
	      dstTrackAux[i].covar_off_diag[3];
	    theTrack->fitTraits().covariantMatrix()(4,1) = 
	      dstTrackAux[i].covar_off_diag[3];
	    theTrack->fitTraits().covariantMatrix()(2,4) = 
	      dstTrackAux[i].covar_off_diag[4];
	    theTrack->fitTraits().covariantMatrix()(4,2) = 
	      dstTrackAux[i].covar_off_diag[4];
	    theTrack->fitTraits().covariantMatrix()(3,4) = 
	      dstTrackAux[i].covar_off_diag[5];
	    theTrack->fitTraits().covariantMatrix()(4,3) = 
	      dstTrackAux[i].covar_off_diag[5];
	    theTrack->fitTraits().covariantMatrix()(5,1) = 
	      dstTrackAux[i].covar_off_diag[6];
	    theTrack->fitTraits().covariantMatrix()(1,5) = 
	      dstTrackAux[i].covar_off_diag[6];
	    theTrack->fitTraits().covariantMatrix()(5,2) = 
	      dstTrackAux[i].covar_off_diag[7];
	    theTrack->fitTraits().covariantMatrix()(2,5) = 
	      dstTrackAux[i].covar_off_diag[7];
	    theTrack->fitTraits().covariantMatrix()(5,3) = 
	      dstTrackAux[i].covar_off_diag[8];
	    theTrack->fitTraits().covariantMatrix()(3,5) = 
	      dstTrackAux[i].covar_off_diag[8];
	    theTrack->fitTraits().covariantMatrix()(5,4) = 
	      dstTrackAux[i].covar_off_diag[9];
	    theTrack->fitTraits().covariantMatrix()(4,5) = 
	      dstTrackAux[i].covar_off_diag[9];
	  } else {
	    cout << "StEventReaderMaker: ERROR: Track find failed for ID " << itrk << endl;
	  }
	}
      }
    }    
    
    dst_dedx_st* dstDedx = theEventManager->returnTable_dst_dedx(nDedx);
    if (dstDedx) {
      cout << "StEventReaderMaker: " << nDedx << " dst_dedx" << endl;
      // Add dedx info to tracks
      if (doLoad) {
	StDedx* dedx = NULL;
	long itrk, idet;
	StGlobalTrack* theTrack;
	StTrackCollection* theTrackCollection = currentEvent->trackCollection();
	for (i=0; i<nDedx; i++) {
	  dst_dedx_st* theDedx = &dstDedx[i];
	  dedx = new StDedx(theDedx);
	  dedx->setNumberOfPointsUsed(theDedx->ndedx);
	  dedx->setMean(theDedx->dedx[0]);
	  dedx->setVariance(theDedx->dedx[1]);
	  dedx->setStatus(theDedx->iflag);
	  itrk = theDedx->id_track-1;
	  theTrack = (*theTrackCollection)[itrk];
	  if (theTrack) {
	    idet = theDedx->det_id;
	    if (idet == detid_tpc) {
	      theTrack->setTpcDedx(dedx);
	    } else if (idet == detid_ftpcWest || idet == detid_ftpcEast) {
	      theTrack->setFtpcDedx(dedx);
	    } else if (idet == detid_svt) {
	      theTrack->setSvtDedx(dedx);
	    } else {
	      cout << "StEventReaderMaker: ERROR: Dedx: Det ID " << idet << 
		" not recognized" << endl;
	      delete dedx;
	      dedx=0;
	    }
	  } else {
	    cout << "StEventReaderMaker: ERROR: Track find failed for ID " << itrk << endl;
	  }
	}
      }
    }    
    
    dst_tof_evt_st* dstTofEvt = theEventManager->returnTable_dst_tof_evt(nTofEvt);
    if (dstTofEvt) {
      if (doLoad) {
      }
    }    
    
    dst_tof_trk_st* dstTofTrk = theEventManager->returnTable_dst_tof_trk(nTofTrk);
    if (dstTofTrk) {
      cout << "StEventReaderMaker: " << nTofTrk << " dst_tof_trk" << endl;
      if (doLoad) {
      }
    }    
    
    dst_point_st* dstPoint = theEventManager->returnTable_dst_point(nPoint);
    dst_point_st* thePoint = NULL;  
    if (dstPoint) {
      cout << "StEventReaderMaker: " << nPoint << " dst_point" << endl;
      if (doLoad) {
	StTpcHit* tpcHit = NULL;
	StFtpcHit* ftpcHit = NULL;
	StSvtHit* svtHit = NULL;
	long idet;
	for (i=0; i<nPoint; i++) {
	  thePoint = &(dstPoint[i]);
	  long itrk = thePoint->id_track-1;
	  StTrackCollection* theTrackCollection = currentEvent->trackCollection();
	  StGlobalTrack* theTrack = (*theTrackCollection)[itrk];
	  if (! theTrack) {
	    cout << "StEventReaderMaker: ERROR: Track find failed for ID " << itrk << endl;
	  } else {
	    // Handle point depending on what detector it comes from
	    idet = thePoint->hw_position%16;
	    if (idet == detid_tpc) {
	      tpcHit = new StTpcHit(thePoint);
	      currentEvent->tpcHitCollection()->push_back(tpcHit);
	      theTrack->addTpcHit(tpcHit);
	    }
	    else if (idet == detid_svt) {
	      svtHit = new StSvtHit(thePoint);
	      currentEvent->svtHitCollection()->push_back(svtHit);
	      theTrack->addSvtHit(svtHit);
	    }
	    else if (idet == detid_ftpcWest || idet == detid_ftpcEast ) {
	      ftpcHit = new StFtpcHit(thePoint);
	      currentEvent->ftpcHitCollection()->push_back(ftpcHit);
	      theTrack->addFtpcHit(ftpcHit);
	    }
	    else {
	      cout << "StEventReaderMaker: ERROR: Detector ID " << idet << " not known" << endl;
	    }
	  }
	}
      }
    }    
  }
  // theEventManager->closeEvent();
  return kStOK;
}


void StEventMaker::setEventManager(StEventManager* mgr)
{
  theEventManager = mgr;
                    id = dstPoints[i].id_track;
//_____________________________________________________________________________
void StEventMaker::PrintInfo(){
  printf("**************************************************************\n");
  printf("* $Id: StEventMaker.cxx,v 1.2 1999/05/05 22:38:00 fisyak Exp $\n");
  printf("**************************************************************\n");
  if (Debug()) StMaker::PrintInfo();
}
                ftpcHitColl->addHit(ftpcHit);
                id = dstPoints[i].id_track;
                if (id < vecGlobalTracks.size() && vecGlobalTracks[id])
                    vecGlobalTracks[id]->detectorInfo()->addHit(ftpcHit);
                else if (id < vecPrimaryTracks.size() && vecPrimaryTracks[id])
                    vecPrimaryTracks[id]->detectorInfo()->addHit(ftpcHit);
        nhits = tpcColl->numberOfHits();
        cout << "# of hits in collection = " << nhits << endl;
        gotOneHit = kFALSE;
	for (k=0; !gotOneHit && k<svtColl->numberOfLayers(); k++)
	    for (j=0; !gotOneHit && j<svtColl->layer(k)->numberOfLadders(); j++)
		for (i=0; !gotOneHit && i<svtColl->layer(k)->ladder(j)->numberOfWafers(); i++)
		    if (svtColl->layer(k)->ladder(j)->wafer(i)->hits().size()) {
	gotOneHit = kFALSE;
	for (k=0; !gotOneHit && k<svtColl->numberOfBarrels(); k++)
	track->geometry()->Dump();
		    if (svtColl->barrel(k)->ladder(j)->wafer(i)->hits().size()) {
			svtColl->barrel(k)->ladder(j)->wafer(i)->hits()[0]->Dump();
	track->detectorInfo()->Dump();
    if (svtColl) {
        nhits = svtColl->numberOfHits();
	track->node()->Dump();
	cout << "collection size = " << richPixels->size() << endl;
	richPixels->Dump();
	
	if (richPixels->size()) {
	    cout << "---------------------------------------------------------" << endl;
	    cout << "StRichPixel (generated from first word in collection)    " << endl;
	    cout << "---------------------------------------------------------" << endl;
	    richPixels->pixel(0).Dump();
	}	
    }    
        if (richPixels->size()) {
            cout << "---------------------------------------------------------" << endl;

    //
    //   Info from some tables for comparisons.
    //   Only tables with varying # of rows are listed.
    //
    cout << "*********************************************************" << endl;
    cout << "*                   Table Information                   *" << endl;
	 << ") at " << (void*) track                                    << endl;
    cout << "globtrk:    ";
	track->Dump();
    cout << "tpt:        ";
	
	cout << "---> StTrack -> StGeometry ("<< track->geometry()->GetName()
	     << ") at " << (void*) (track->geometry()) << endl;
	if (track->geometry()) track->geometry()->Dump();

	cout << "---> StTrack -> StDetectorInfo at "
	     << (void*) (track->detectorInfo()) << endl;
	if (track->detectorInfo()) track->detectorInfo()->Dump();

	cout << "---> StTrack -> StTrackNode at "
	     << (void*) (track->node()) << endl;
	if (track->node()) track->node()->Dump();

	cout << "---> StTrack -> StPidTraits ("
	     << (track->pidTraits().size() ? 1 : 0 ) << " of "
	     <<  track->pidTraits().size() << " entries shown)" << endl;
	if (track->pidTraits().size()) track->pidTraits()[0]->Dump();

void
StEventMaker::printTrackInfo(StTrack* track)
{
    cout << "---------------------------------------------------------" << endl;
    cout << "StTrack (" << (track ? track->GetName() : "n/a")
         << ") at " << (void*) track                                    << endl;
    cout << "---------------------------------------------------------" << endl;
    if (track) {
        track->Dump();
        cout << "covariantMatrix():" << track->fitTraits().covariantMatrix() << endl;
        
        cout << "---> StTrack -> StGeometry ("<< track->geometry()->GetName()
             << ") at " << (void*) (track->geometry()) << endl;
        if (track->geometry()) track->geometry()->Dump();

        cout << "---> StTrack -> StDetectorInfo at "
             << (void*) (track->detectorInfo()) << endl;
        if (track->detectorInfo()) track->detectorInfo()->Dump();

        cout << "---> StTrack -> StTrackNode at "
             << (void*) (track->node()) << endl;
        if (track->node()) track->node()->Dump();

        cout << "---> StTrack -> StPidTraits ("
             << (track->pidTraits().size() ? 1 : 0 ) << " of "
             <<  track->pidTraits().size() << " entries shown)" << endl;
        if (track->pidTraits().size()) track->pidTraits()[0]->Dump();
    }
}

