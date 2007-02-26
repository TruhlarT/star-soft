#include "y2006a.h"
TDataSet *CreateTable() {
  y2006a();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("y2006a");
  }
  return (TDataSet *) geom;
}
