#include "complete.h"
TDataSet *CreateTable() {
  complete();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("complete");
  }
  return (TDataSet *) geom;
}
