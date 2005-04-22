#include "y2005b.h"
TDataSet *CreateTable() {
  y2005b();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager);
    geom->SetTitle("y2005b");
  }
  return (TDataSet *) geom;
}
