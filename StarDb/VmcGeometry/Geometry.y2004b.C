#include "y2004b.h"
TDataSet *CreateTable() {
  y2004b();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager);
    geom->SetTitle("y2004b");
  }
  return (TDataSet *) geom;
}
