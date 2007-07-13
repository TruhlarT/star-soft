TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 145065
  row.laserDriftVelocityEast	 =   5.57495; // +/- 1.56843e-05 cm/us All: East = -0.530805 +/- 0.352217
  row.laserDriftVelocityWest	 =   5.57495; // +/- 1.56843e-05 cm/us All: West = -0.0785416 +/- 0.00276691
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57495 +/- 1.56843e-05
  return (TDataSet *)tableSet;// West = 5.57495 +/- 1.56847e-05 East = 5.57755 +/- 0.00218326
};
