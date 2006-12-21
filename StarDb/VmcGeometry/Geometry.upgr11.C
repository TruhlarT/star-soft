#include "upgr11.h"
TDataSet *CreateTable() {
  upgr11();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("upgr11");
  }
  return (TDataSet *) geom;
}
