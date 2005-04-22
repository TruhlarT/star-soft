#include "y2004.h"
TDataSet *CreateTable() {
  y2004();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager);
    geom->SetTitle("y2004");
  }
  return (TDataSet *) geom;
}
