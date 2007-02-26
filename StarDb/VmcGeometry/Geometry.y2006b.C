#include "y2006b.h"
TDataSet *CreateTable() {
  y2006b();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("y2006b");
  }
  return (TDataSet *) geom;
}
