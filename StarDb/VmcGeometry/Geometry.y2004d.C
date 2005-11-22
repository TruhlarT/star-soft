#include "y2004d.h"
TDataSet *CreateTable() {
  y2004d();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("y2004d");
  }
  return (TDataSet *) geom;
}
