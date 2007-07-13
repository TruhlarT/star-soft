TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 139027
  row.laserDriftVelocityEast	 =   5.57457; // +/- 1.94785e-05 cm/us All: East = -0.0091448 +/- 0.00424923
  row.laserDriftVelocityWest	 =   5.57457; // +/- 1.94785e-05 cm/us All: West = 0.0102569 +/- 0.00615648
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57457 +/- 1.94785e-05
  return (TDataSet *)tableSet;// West = 5.57447 +/- 3.45757e-05 East = 5.57461 +/- 2.35756e-05
};
