TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 174090
  row.laserDriftVelocityEast	 =   5.5723; // +/- 2.19474e-05 cm/us All: East = 0.526451 +/- 0.00574947
  row.laserDriftVelocityWest	 =   5.5723; // +/- 2.19474e-05 cm/us All: West = 0.277362 +/- 0.00543585
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5723 +/- 2.19474e-05
  return (TDataSet *)tableSet;// West = 5.57298 +/- 3.00797e-05 East = 5.57153 +/- 3.20948e-05
};
