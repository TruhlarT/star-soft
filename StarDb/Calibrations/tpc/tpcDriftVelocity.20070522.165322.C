TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 142024
  row.laserDriftVelocityEast	 =   5.57377; // +/- 1.49558e-05 cm/us All: East = 0.166425 +/- 0.00315139
  row.laserDriftVelocityWest	 =   5.57377; // +/- 1.49558e-05 cm/us All: West = 0.0544544 +/- 0.00515462
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57377 +/- 1.49558e-05
  return (TDataSet *)tableSet;// West = 5.57424 +/- 2.82985e-05 East = 5.57359 +/- 1.76173e-05
};
