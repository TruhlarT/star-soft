#include "y2005x.h"
TDataSet *CreateTable() {
  y2005x();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager);
    geom->SetTitle("y2005x");
  }
  return (TDataSet *) geom;
}
