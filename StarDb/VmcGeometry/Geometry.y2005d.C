#include "y2005d.h"
TDataSet *CreateTable() {
  y2005d();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("y2005d");
  }
  return (TDataSet *) geom;
}
