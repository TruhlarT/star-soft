TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 135001
  row.laserDriftVelocityEast	 =   5.57436; // +/- 1.83903e-05 cm/us All: East = -0.0321611 +/- 0.00409798
  row.laserDriftVelocityWest	 =   5.57436; // +/- 1.83903e-05 cm/us All: West = 0.145194 +/- 0.00566634
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57436 +/- 1.83903e-05
  return (TDataSet *)tableSet;// West = 5.57373 +/- 3.14494e-05 East = 5.57469 +/- 2.26704e-05
};
