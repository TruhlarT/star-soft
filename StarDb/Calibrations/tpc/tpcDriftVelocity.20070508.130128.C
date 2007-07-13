TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 128040
  row.laserDriftVelocityEast	 =   5.57553; // +/- 1.48296e-05 cm/us All: East = -0.154732 +/- 0.0029113
  row.laserDriftVelocityWest	 =   5.57553; // +/- 1.48296e-05 cm/us All: West = -0.301447 +/- 0.00627871
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57553 +/- 1.48296e-05
  return (TDataSet *)tableSet;// West = 5.5762 +/- 3.51189e-05 East = 5.57539 +/- 1.63597e-05
};
