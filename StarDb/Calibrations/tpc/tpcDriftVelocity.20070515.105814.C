TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 135033
  row.laserDriftVelocityEast	 =   5.57454; // +/- 3.05436e-05 cm/us All: East = -0.117471 +/- 0.00901293
  row.laserDriftVelocityWest	 =   5.57454; // +/- 3.05436e-05 cm/us All: West = 0.0266032 +/- 0.00679862
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57454 +/- 3.05436e-05
  return (TDataSet *)tableSet;// West = 5.57436 +/- 3.76989e-05 East = 5.57489 +/- 5.21086e-05
};
