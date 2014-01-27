/*!
 * \class StPxlDbMaker
 * \author J. Bouchet, M. Lomnitz, May 2013
 * \Initial Revision.
 */
/***************************************************************************
 *
 * $Id: StPxlDbMaker.cxx,v 1.9 2014/01/27 02:37:10 qiuh Exp $
 *
 * Author: J. Bouchet, M. Lomnitz, May 2013
 ***************************************************************************
 *
 * Description:
 * Read DB and prepare information on pxl geometry and sensor/row/column status
 * More information at
 * https://www.star.bnl.gov/protected/heavy/qiuh/HFT/software/PXL_software.pdf
 *
 ***************************************************************************
 *
 * $Log: StPxlDbMaker.cxx,v $
 * Revision 1.9  2014/01/27 02:37:10  qiuh
 * *** empty log message ***
 *
 *
 **************************************************************************/

#include "StPxlDbMaker.h"
#include "StPxlDb.h"
#include "StMessMgr.h"
#include "tables/St_Survey_Table.h"
#include "St_db_Maker/St_db_Maker.h"
#include "tables/St_pxlSensorStatus_Table.h"
#include "tables/St_pxlRowColumnStatus_Table.h"
#include "tables/St_pxlControl_Table.h"
#include "tables/St_pxlSensorTps_Table.h"

ClassImp(StPxlDbMaker)
//_____________________________________________________________________________
StPxlDbMaker::StPxlDbMaker(const char *name) :
   StMaker(name)
{
   mPxlDb = 0;
}
//_____________________________________________________________________________
Int_t StPxlDbMaker::InitRun(Int_t runNumber)
{
   if (!mPxlDb) mPxlDb = new StPxlDb();

   // set geoHMatrices
   St_Survey *idsOnTpc          = (St_Survey *) GetDataBase("Geometry/pxl/idsOnTpc");
   if (! idsOnTpc)          {LOG_WARN << "idsOnTpc has not been found"  << endm; return kStErr;}

   St_Survey *pstOnIds          = (St_Survey *) GetDataBase("Geometry/pxl/pstOnIds");
   if (! pstOnIds)          {LOG_WARN << "pstOnIds has not been found"  << endm; return kStErr;}

   St_Survey *pxlOnPst          = (St_Survey *) GetDataBase("Geometry/pxl/pxlOnPst");
   if (! pxlOnPst)          {LOG_WARN << "pxlOnPst has not been found"  << endm; return kStErr;}

   St_Survey *pxlHalfOnPxl         = (St_Survey *) GetDataBase("Geometry/pxl/pxlHalfOnPxl");
   if (! pxlHalfOnPxl)         {LOG_WARN << "pxlHalfOnPxl has not been found"  << endm; return kStErr;}

   St_Survey *pxlSectorOnHalf     = (St_Survey *) GetDataBase("Geometry/pxl/pxlSectorOnHalf");
   if (! pxlSectorOnHalf)     {LOG_WARN << "pxlSectorOnHalf has not been found"  << endm; return kStErr;}

   St_Survey *pxlLadderOnSector  = (St_Survey *) GetDataBase("Geometry/pxl/pxlLadderOnSector");
   if (! pxlLadderOnSector)  {LOG_WARN << "pxladderOnSector has not been found"  << endm; return kStErr;}

   St_Survey *pxlSensorOnLadder  = (St_Survey *) GetDataBase("Geometry/pxl/pxlSensorOnLadder");
   if (! pxlSensorOnLadder)  {LOG_WARN << "pxlSensorOnLadder has not been found"  << endm; return kStErr;}

   Survey_st *tables[7] = {idsOnTpc->GetTable(), pstOnIds->GetTable(), pxlOnPst->GetTable(), pxlHalfOnPxl->GetTable(),
                           pxlSectorOnHalf->GetTable(), pxlLadderOnSector->GetTable(), pxlSensorOnLadder->GetTable()
                          };

   mPxlDb->setGeoHMatrices(tables);

   // set status tables
   St_pxlSensorStatus *sensorStatus = (St_pxlSensorStatus *)GetDataBase("Calibrations/pxl/pxlSensorStatus");
   if (sensorStatus) mPxlDb->setSensorStatus(sensorStatus->GetTable());
   else {LOG_WARN << " no pxl sensor status table " << endm; return kStErr;}

   St_pxlRowColumnStatus *rowColumnStatus = (St_pxlRowColumnStatus *)GetDataBase("Calibrations/pxl/pxlRowColumnStatus");
   if (rowColumnStatus) mPxlDb->setRowColumnStatus(rowColumnStatus->GetTable());
   else {LOG_WARN << " no pxl row column status table " << endm; return kStErr;}

   // set pxlControl
   St_pxlControl *pxlControl = (St_pxlControl *)GetDataBase("Geometry/pxl/pxlControl");
   if (pxlControl) {
      mPxlDb->setPxlControl(pxlControl->GetTable());
   }
   else {
      LOG_WARN << "InitRun : No access to pxlControl table, abort PXL reconstruction" << endm;
      return kStErr;
   }

   // create and set thin plate functions
   TDataSet *dbTps = 0;
   dbTps = GetDataBase("Geometry/pxl/pxlSensorTps");
   if (!dbTps) {
      LOG_WARN << "no tps table found in db, or malformed local db config " << endm;
      return kStErr;
   }

   St_pxlSensorTps *datasetTps = 0;
   datasetTps = (St_pxlSensorTps *) dbTps->Find("pxlSensorTps");
   if (datasetTps) {
      mPxlDb->setThinPlateSpline(datasetTps->GetTable());
   }
   else {
      LOG_WARN << "ERROR: dataset does not contain tps table" << endm;
      return kStErr;
   }

   // finally write the data
   ToWhiteBoard("pxlDb", mPxlDb);

   return kStOK;
}
