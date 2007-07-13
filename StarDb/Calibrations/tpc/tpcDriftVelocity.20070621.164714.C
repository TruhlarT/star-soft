TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 172085
  row.laserDriftVelocityEast	 =   5.57148; // +/- 2.36743e-05 cm/us All: East = 0.755313 +/- 0.0395466
  row.laserDriftVelocityWest	 =   5.57148; // +/- 2.36743e-05 cm/us All: West = 0.54486 +/- 0.00425331
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57148 +/- 2.36743e-05
  return (TDataSet *)tableSet;// West = 5.57149 +/- 2.37769e-05 East = 5.57028 +/- 0.000255085
};
