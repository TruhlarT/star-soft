#include "y2004y.h"
TDataSet *CreateTable() {
  y2004y();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("y2004y");
  }
  return (TDataSet *) geom;
}
