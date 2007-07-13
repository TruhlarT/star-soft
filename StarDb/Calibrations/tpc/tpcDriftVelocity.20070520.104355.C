TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 140023
  row.laserDriftVelocityEast	 =   5.57528; // +/- 2.35377e-05 cm/us All: East = -0.165389 +/- 0.00473439
  row.laserDriftVelocityWest	 =   5.57528; // +/- 2.35377e-05 cm/us All: West = -0.0735509 +/- 0.00873548
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57528 +/- 2.35377e-05
  return (TDataSet *)tableSet;// West = 5.5749 +/- 5.00767e-05 East = 5.57539 +/- 2.66671e-05
};
