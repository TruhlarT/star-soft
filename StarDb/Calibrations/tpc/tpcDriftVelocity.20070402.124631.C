TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 92034
  row.laserDriftVelocityEast	 =   5.58382; // +/- 1.47107e-05 cm/us All: East = -3.00897 +/- 0.00351272
  row.laserDriftVelocityWest	 =   5.58382; // +/- 1.47107e-05 cm/us All: West = -2.91997 +/- 0.00392407
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.58382 +/- 1.47107e-05
  return (TDataSet *)tableSet;// West = 5.58353 +/- 2.19216e-05 East = 5.58406 +/- 1.98416e-05
};
