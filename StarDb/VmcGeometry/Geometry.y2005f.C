#include "y2005f.h"
TDataSet *CreateTable() {
  y2005f();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("y2005f");
  }
  return (TDataSet *) geom;
}
