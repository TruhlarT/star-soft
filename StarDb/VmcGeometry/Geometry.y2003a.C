#include "y2003a.h"
TDataSet *CreateTable() {
  y2003a();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("y2003a");
  }
  return (TDataSet *) geom;
}
