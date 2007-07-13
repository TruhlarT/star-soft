TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 162017
  row.laserDriftVelocityEast	 =   5.57313; // +/- 2.37988e-05 cm/us All: East = 0.259581 +/- 0.0125922
  row.laserDriftVelocityWest	 =   5.57313; // +/- 2.37988e-05 cm/us All: West = 0.246479 +/- 0.00451347
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57313 +/- 2.37988e-05
  return (TDataSet *)tableSet;// West = 5.57314 +/- 2.52929e-05 East = 5.57309 +/- 7.02844e-05
};
