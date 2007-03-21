TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6035110
  row.laserDriftVelocityEast	 =   5.53933; // +/- 0.000474204 cm/us All: East = 5.5387 +/- 0.00112033
  row.laserDriftVelocityWest	 =   5.53933; // +/- 0.000474204 cm/us All: West = 5.53947 +/- 0.000523402
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 2.48983 +/- 0.19117
  return (TDataSet *)tableSet;// West = 2.58689 +/- 0.207839 East = 1.95653 +/- 0.487188
};
