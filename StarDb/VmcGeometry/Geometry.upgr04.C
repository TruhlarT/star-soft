#include "upgr04.h"
TDataSet *CreateTable() {
  upgr04();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("upgr04");
  }
  return (TDataSet *) geom;
}
