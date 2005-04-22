#include "y2004x.h"
TDataSet *CreateTable() {
  y2004x();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager);
    geom->SetTitle("y2004x");
  }
  return (TDataSet *) geom;
}
