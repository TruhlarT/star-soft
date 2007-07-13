TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 136094
  row.laserDriftVelocityEast	 =   5.57532; // +/- 1.91027e-05 cm/us All: East = -0.121471 +/- 0.00383493
  row.laserDriftVelocityWest	 =   5.57532; // +/- 1.91027e-05 cm/us All: West = -0.233665 +/- 0.00760823
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57532 +/- 1.91027e-05
  return (TDataSet *)tableSet;// West = 5.57581 +/- 4.24982e-05 East = 5.57519 +/- 2.13848e-05
};
