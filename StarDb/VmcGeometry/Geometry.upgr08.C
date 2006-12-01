#include "upgr08.h"
TDataSet *CreateTable() {
  upgr08();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("upgr08");
  }
  return (TDataSet *) geom;
}
