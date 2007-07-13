TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 126002
  row.laserDriftVelocityEast	 =   5.57873; // +/- 1.94931e-05 cm/us All: East = -0.763595 +/- 0.00435351
  row.laserDriftVelocityWest	 =   5.57873; // +/- 1.94931e-05 cm/us All: West = -0.723252 +/- 0.00562455
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57873 +/- 1.94931e-05
  return (TDataSet *)tableSet;// West = 5.57855 +/- 3.15359e-05 East = 5.57883 +/- 2.47978e-05
};
