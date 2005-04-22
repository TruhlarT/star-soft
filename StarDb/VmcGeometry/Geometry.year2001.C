#include "year2001.h"
TDataSet *CreateTable() {
  year2001();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager);
    geom->SetTitle("year2001");
  }
  return (TDataSet *) geom;
}
