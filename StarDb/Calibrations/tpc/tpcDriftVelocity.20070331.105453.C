TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 90018
  row.laserDriftVelocityEast	 =   5.58367; // +/- 1.70647e-05 cm/us All: East = -2.97453 +/- 0.00395372
  row.laserDriftVelocityWest	 =   5.58367; // +/- 1.70647e-05 cm/us All: West = -2.90933 +/- 0.00471436
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.58367 +/- 1.70647e-05
  return (TDataSet *)tableSet;// West = 5.58347 +/- 2.66816e-05 East = 5.58381 +/- 2.21984e-05
};
