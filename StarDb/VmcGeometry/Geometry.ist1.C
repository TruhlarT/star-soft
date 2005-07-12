#include "yist1.h"
TDataSet *CreateTable() {
  yist1();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("yist1");
  }
  return (TDataSet *) geom;
}
