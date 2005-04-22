#include "year2002.h"
TDataSet *CreateTable() {
  year2002();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager);
    geom->SetTitle("year2002");
  }
  return (TDataSet *) geom;
}
