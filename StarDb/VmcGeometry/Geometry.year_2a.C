#include "year_2a.h"
TDataSet *CreateTable() {
  year_2a();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("year_2a");
  }
  return (TDataSet *) geom;
}
