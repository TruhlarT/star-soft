#include "upgr02.h"
TDataSet *CreateTable() {
  upgr02();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("upgr02");
  }
  return (TDataSet *) geom;
}
