#include "upgr10.h"
TDataSet *CreateTable() {
  upgr10();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("upgr10");
  }
  return (TDataSet *) geom;
}
