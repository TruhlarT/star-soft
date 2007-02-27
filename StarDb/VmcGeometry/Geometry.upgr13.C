#include "upgr13.h"
TDataSet *CreateTable() {
  upgr13();
  TObjectSet *geom = 0;
  if (gGeoManager) {
    geom = new TObjectSet("Geometry",gGeoManager,kFALSE);
    geom->SetTitle("upgr13");
  }
  return (TDataSet *) geom;
}
