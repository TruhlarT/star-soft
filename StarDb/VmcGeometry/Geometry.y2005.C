#include "y2005.h"
TDataSet *CreateTable() {
  y2005();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("y2005");
  }
  return (TDataSet *) geom;
}
