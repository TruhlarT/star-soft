#include "upgr07.h"
TDataSet *CreateTable() {
  upgr07();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("upgr07");
  }
  return (TDataSet *) geom;
}
