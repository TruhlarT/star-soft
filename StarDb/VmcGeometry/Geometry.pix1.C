#include "pix1.h"
TDataSet *CreateTable() {
  pix1();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("pix1");
  }
  return (TDataSet *) geom;
}
