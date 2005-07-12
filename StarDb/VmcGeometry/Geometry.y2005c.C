#include "y2005c.h"
TDataSet *CreateTable() {
  y2005c();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("y2005c");
  }
  return (TDataSet *) geom;
}
