#include "upgr06.h"
TDataSet *CreateTable() {
  upgr06();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("upgr06");
  }
  return (TDataSet *) geom;
}
