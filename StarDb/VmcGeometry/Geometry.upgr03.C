#include "upgr03.h"
TDataSet *CreateTable() {
  upgr03();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("upgr03");
  }
  return (TDataSet *) geom;
}
