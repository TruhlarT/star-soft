TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 127014
  row.laserDriftVelocityEast	 =   5.5756; // +/- 1.56023e-05 cm/us All: East = -0.185977 +/- 0.00308012
  row.laserDriftVelocityWest	 =   5.5756; // +/- 1.56023e-05 cm/us All: West = -0.229892 +/- 0.00652468
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5756 +/- 1.56023e-05
  return (TDataSet *)tableSet;// West = 5.57583 +/- 3.5812e-05 East = 5.57555 +/- 1.73338e-05
};
