#include "upgr01.h"
TDataSet *CreateTable() {
  upgr01();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("upgr01");
  }
  return (TDataSet *) geom;
}
