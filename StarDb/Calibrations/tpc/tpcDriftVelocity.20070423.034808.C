TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 112085
  row.laserDriftVelocityEast	 =   5.57594; // +/- 1.78192e-05 cm/us All: East = -0.237858 +/- 0.00365178
  row.laserDriftVelocityWest	 =   5.57594; // +/- 1.78192e-05 cm/us All: West = -0.319306 +/- 0.00650662
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57594 +/- 1.78192e-05
  return (TDataSet *)tableSet;// West = 5.57626 +/- 3.59663e-05 East = 5.57584 +/- 2.0514e-05
};
