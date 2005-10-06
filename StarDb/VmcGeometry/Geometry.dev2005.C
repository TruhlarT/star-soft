#include "dev2005.h"
TDataSet *CreateTable() {
  dev2005();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("dev2005");
  }
  return (TDataSet *) geom;
}
