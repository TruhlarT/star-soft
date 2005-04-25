#include "y2004c.h"
TDataSet *CreateTable() {
  y2004c();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("y2004c");
  }
  return (TDataSet *) geom;
}
