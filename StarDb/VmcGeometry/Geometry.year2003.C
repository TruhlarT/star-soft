#include "year2003.h"
TDataSet *CreateTable() {
  year2003();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager);
    geom->SetTitle("year2003");
  }
  return (TDataSet *) geom;
}
