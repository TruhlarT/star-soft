//
//
//////////////////////////////////////////////////////////////////////////
//                                                                      //
// StTpcDb                                                            //
//                                                                      //
// This class implements to offline interface to the STAR database      //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#ifndef ClassStTpcDb
#define ClassStTpcDb

#ifndef __CINT__
#include "fortranc.h"
#define numberOfPadsAtRow_ F77_NAME(numberofpadsatrow,NUMBEROFPADSATROW)
extern "C" {
int type_of_call numberOfPadsAtRow_(int *row);
}
#endif
#include "StMessMgr.h"
#include "StMaker.h"
#include "StDbTableI.h"
#include "StDbDataSet.h"
#include "StRTpcPadPlane.h"
#include "StRTpcWirePlane.h"
#include "StRTpcDimensions.h"
#include "StRTpcElectronics.h"
#include "StRTpcGain.h"
#include "StRTpcT0.h"
#include "StRTpcSlowControlSim.h"
class StMaker;


class StTpcDb {
 private:
 StMaker* mk;
 StTpcPadPlaneI* PadPlane;
 StTpcWirePlaneI* WirePlane;
 StTpcDimensionsI* dimensions;
 StTpcSlowControlSimI* slowControlSim;
 StTpcElectronicsI* electronics;
 StTpcGainI* gain[24];
 StTpcT0I* t0[24];
 St_DataSet* tpc_geometry;
 St_DataSet* tpc_calibrations;
 St_DataSet* tpc_conditions;

 protected:
 
 public:
   StTpcDb(StDbDataSet* input);
   ~StTpcDb();
   StTpcPadPlaneI* PadPlaneGeometry();
   StTpcWirePlaneI* WirePlaneGeometry();
   StTpcDimensionsI* Dimensions();
   StTpcSlowControlSimI* SlowControlSim();
   StTpcElectronicsI* Electronics();
   StTpcGainI* Gain(int sector);
   StTpcT0I* T0(int sector);

#ifdef __ROOT__
   ClassDef(StTpcDb,0)
#endif
};

// Global pointers:
R__EXTERN StTpcDb* gStTpcDb;

#endif









