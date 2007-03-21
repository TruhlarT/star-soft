TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6015048
  row.laserDriftVelocityEast	 =   5.53351; // +/- 8.75927e-05 cm/us All: East = 5.53494 +/- 0.000210209
  row.laserDriftVelocityWest	 =   5.53351; // +/- 8.75927e-05 cm/us All: West = 5.53321 +/- 9.63566e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.212985 +/- 0.0190763
  return (TDataSet *)tableSet;// West = 0.295541 +/- 0.0216465 East = -0.0740509 +/- 0.0403628
};
