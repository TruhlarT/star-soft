#include "upgr05.h"
TDataSet *CreateTable() {
  upgr05();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("upgr05");
  }
  return (TDataSet *) geom;
}
