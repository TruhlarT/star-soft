TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 127049
  row.laserDriftVelocityEast	 =   5.57568; // +/- 1.86188e-05 cm/us All: East = -0.194258 +/- 0.00384172
  row.laserDriftVelocityWest	 =   5.57568; // +/- 1.86188e-05 cm/us All: West = -0.253045 +/- 0.00675112
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57568 +/- 1.86188e-05
  return (TDataSet *)tableSet;// West = 5.57594 +/- 3.85874e-05 East = 5.5756 +/- 2.12569e-05
};
