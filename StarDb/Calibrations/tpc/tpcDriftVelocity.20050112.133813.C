TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6012033
  row.laserDriftVelocityEast	 =   5.51618; // +/- 9.09293e-05 cm/us All: East = 5.51755 +/- 0.000121496
  row.laserDriftVelocityWest	 =   5.51618; // +/- 9.09293e-05 cm/us All: West = 5.51443 +/- 0.000137101
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = -16.4652 +/- 0.016262
  return (TDataSet *)tableSet;// West = -16.1542 +/- 0.0244948 East = -16.7104 +/- 0.0217458
};
