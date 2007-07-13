TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 105040
  row.laserDriftVelocityEast	 =   5.58409; // +/- 1.50319e-05 cm/us All: East = -1.7873 +/- 0.00379572
  row.laserDriftVelocityWest	 =   5.58409; // +/- 1.50319e-05 cm/us All: West = -1.62328 +/- 0.00380817
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.58409 +/- 1.50319e-05
  return (TDataSet *)tableSet;// West = 5.5836 +/- 2.156e-05 East = 5.58455 +/- 2.09689e-05
};
