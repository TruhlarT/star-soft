#include "y2006.h"
TDataSet *CreateTable() {
  y2006();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("y2006");
  }
  return (TDataSet *) geom;
}
