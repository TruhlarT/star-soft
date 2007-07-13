TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 109095
  row.laserDriftVelocityEast	 =   5.57396; // +/- 1.44173e-05 cm/us All: East = 0.279336 +/- 0.00344113
  row.laserDriftVelocityWest	 =   5.57396; // +/- 1.44173e-05 cm/us All: West = -0.121411 +/- 0.00397245
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57396 +/- 1.44173e-05
  return (TDataSet *)tableSet;// West = 5.57517 +/- 2.18292e-05 East = 5.57302 +/- 1.92009e-05
};
