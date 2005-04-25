#include "y2004a.h"
TDataSet *CreateTable() {
  y2004a();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("y2004a");
  }
  return (TDataSet *) geom;
}
