#include "y2007.h"
TDataSet *CreateTable() {
  y2007();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("y2007");
  }
  return (TDataSet *) geom;
}
