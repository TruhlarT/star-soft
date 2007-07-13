TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 160012
  row.laserDriftVelocityEast	 =   5.57363; // +/- 2.71134e-05 cm/us All: East = 0.157148 +/- 0.0123332
  row.laserDriftVelocityWest	 =   5.57363; // +/- 2.71134e-05 cm/us All: West = 0.151883 +/- 0.00527527
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57363 +/- 2.71134e-05
  return (TDataSet *)tableSet;// West = 5.57364 +/- 2.94891e-05 East = 5.57359 +/- 6.89492e-05
};
