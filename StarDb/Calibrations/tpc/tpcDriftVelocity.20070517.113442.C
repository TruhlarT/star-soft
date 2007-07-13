TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 137025
  row.laserDriftVelocityEast	 =   5.57493; // +/- 1.73849e-05 cm/us All: East = -0.0977969 +/- 0.00366542
  row.laserDriftVelocityWest	 =   5.57493; // +/- 1.73849e-05 cm/us All: West = -0.0310598 +/- 0.00606956
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57493 +/- 1.73849e-05
  return (TDataSet *)tableSet;// West = 5.5747 +/- 3.3256e-05 East = 5.57502 +/- 2.03933e-05
};
