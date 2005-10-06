#include "year_2b.h"
TDataSet *CreateTable() {
  year_2b();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("year_2b");
  }
  return (TDataSet *) geom;
}
