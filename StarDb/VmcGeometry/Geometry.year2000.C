#include "year2000.h"
TDataSet *CreateTable() {
  year2000();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager);
    geom->SetTitle("year2000");
  }
  return (TDataSet *) geom;
}
