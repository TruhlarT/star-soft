#include "y2003c.h"
TDataSet *CreateTable() {
  y2003c();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("y2003c");
  }
  return (TDataSet *) geom;
}
