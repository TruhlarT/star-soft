TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 124088
  row.laserDriftVelocityEast	 =   5.57852; // +/- 1.47243e-05 cm/us All: East = -0.686028 +/- 0.00291875
  row.laserDriftVelocityWest	 =   5.57852; // +/- 1.47243e-05 cm/us All: West = -0.830224 +/- 0.00590954
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57852 +/- 1.47243e-05
  return (TDataSet *)tableSet;// West = 5.57913 +/- 3.21597e-05 East = 5.57836 +/- 1.65621e-05
};
