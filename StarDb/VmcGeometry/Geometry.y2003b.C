#include "y2003b.h"
TDataSet *CreateTable() {
  y2003b();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("y2003b");
  }
  return (TDataSet *) geom;
}
