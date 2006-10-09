#include "y2005e.h"
TDataSet *CreateTable() {
  y2005e();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("y2005e");
  }
  return (TDataSet *) geom;
}
