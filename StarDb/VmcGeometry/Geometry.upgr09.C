#include "upgr09.h"
TDataSet *CreateTable() {
  upgr09();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("upgr09");
  }
  return (TDataSet *) geom;
}
