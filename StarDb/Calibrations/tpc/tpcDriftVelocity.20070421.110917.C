TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 111046
  row.laserDriftVelocityEast	 =   5.57469; // +/- 1.732e-05 cm/us All: East = -0.0779283 +/- 0.00423536
  row.laserDriftVelocityWest	 =   5.57469; // +/- 1.732e-05 cm/us All: West = 0.0185129 +/- 0.00441514
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57469 +/- 1.732e-05
  return (TDataSet *)tableSet;// West = 5.57444 +/- 2.53187e-05 East = 5.57492 +/- 2.37452e-05
};
