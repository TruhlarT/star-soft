#include "ist1.h"
TDataSet *CreateTable() {
  ist1();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("ist1");
  }
  return (TDataSet *) geom;
}
