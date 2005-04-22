#include "y2003x.h"
TDataSet *CreateTable() {
  y2003x();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager);
    geom->SetTitle("y2003x");
  }
  return (TDataSet *) geom;
}
