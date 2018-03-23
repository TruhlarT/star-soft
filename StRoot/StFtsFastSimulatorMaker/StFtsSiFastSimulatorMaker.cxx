#include "StFtsSiFastSimulatorMaker.h"
#include "St_base/StMessMgr.h"
#include "StEvent/StEvent.h"
#include "StEvent/StRnDHitCollection.h"
#include "StEvent/StRnDHit.h"
#include "tables/St_g2t_fts_hit_Table.h"
#include "TString.h"
#include "TGeoManager.h"
//_____________________________________________________________________________________
StFtsSiFastSimulatorMaker::StFtsSiFastSimulatorMaker( const char* name ) : StMaker(name) {

}
//_____________________________________________________________________________________
int StFtsSiFastSimulatorMaker::Init() {

  return StMaker::Init();
}
//_____________________________________________________________________________________
int StFtsSiFastSimulatorMaker::Make() {



  // Get the existing StEvent, or add one locally if it doesn't exist.
  StEvent* event = static_cast<StEvent*>(GetDataSet("StEvent"));
  if(!event) {        
    event = new StEvent;
    AddData(event);
    LOG_DEBUG << "Creating StEvent" << endm;
  } 

  // Get the RnD hit collection, and create if it doesn't already exist
  StRnDHitCollection* collection =  event->rndHitCollection();
  if ( 0 == collection ) {
    event -> setRnDHitCollection( collection = new StRnDHitCollection() );
    LOG_DEBUG << "Creating StRnDHitCollection for FTS" << endm;      
  }

  // Verify the existence of the geometry, and initialize if it is missing
  if ( 0==gGeoManager ) {
    GetDataBase( "VmcGeometry" );
  }

  // Read the g2t table
  St_g2t_fts_hit* hitTable = static_cast<St_g2t_fts_hit*>(GetDataSet("g2t_fts_hit"));
  if (!hitTable) {
    LOG_DEBUG << "g2t_fts_hit table is empty" << endm;
    return kStOK;  // Nothing to do
  }  // if

  const int nHits = hitTable->GetNRows();
  LOG_DEBUG << "g2t_fts_hit table has " << nHits << " hits" << endm;

  //
  // Loop over all hits and call FillSensor on each of them
  //
  for ( int i=0; i<nHits; i++ ) {
    
    FillSensor( collection, (g2t_fts_hit_st*)hitTable->At(i) );

  }

  return kStOK;
}
//_____________________________________________________________________________________
void StFtsSiFastSimulatorMaker::Clear(const Option_t* opts) {

}
//_____________________________________________________________________________________
int  StFtsSiFastSimulatorMaker::Finish() {
  return kStOK;
}
//_____________________________________________________________________________________
void StFtsSiFastSimulatorMaker::FillSensor( StRnDHitCollection* collection, g2t_fts_hit_st* hit ) {


  LOG_DEBUG << " Fill hit = " << hit << endm; 

  // Protect against null hits
  if ( 0==hit ) return;

  // Decode volume ID -- return if not the right subsystem --
  int volume_id = hit -> volume_id;
  LOG_DEBUG << "volume_id = " << volume_id << endl;

  int subsystem = volume_id / 10000;            if ( 1 != subsystem )     return;
  int plane     = (volume_id % 10000) / 1000;   if ( plane<1 || plane>3 ) return;
  int sensor    = (volume_id %  1000);




  // Set the current path to the struck sensor and obtain transformation matrix
  { 
    const char* plane_names[]  = { "FTSA", "FTSB", "FTSC" };
    const char* sensor_names[] = { "FSIA", "FSIB", "FSIC" };
    TString sensor_path = Form( "/HALL_1/CAVE_1/FTSM_1/%s_1/%s_%i", plane_names[plane-1], sensor_names[plane-1], sensor );
    gGeoManager->cd( sensor_path );
  }
  const TGeoHMatrix* transform = gGeoManager->GetCurrentMatrix();

  double xlocal[] = { hit->x[0], hit->x[1], hit->x[2] }; // good only to single precision
  double xglobal[] = { 0, 0, 0 };

  transform->LocalToMaster( xlocal, xglobal );


  // Print out the volume id, sensor, plane and local / global coordinates

  LOG_INFO<< Form( "[%i %i %i]: (%f, %f, %f) (%f, %f, %f)",
		     volume_id, sensor, plane, xlocal[0], xlocal[1], xlocal[2], xglobal[0], xglobal[1], xglobal[2] )
	    << endm;



  //
  // BEGIN Fast Simulation Here
  // 




  return;
 
}
//_____________________________________________________________________________________
