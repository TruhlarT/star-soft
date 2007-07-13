TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 112066
  row.laserDriftVelocityEast	 =   5.57602; // +/- 1.7705e-05 cm/us All: East = -0.333283 +/- 0.0049
  row.laserDriftVelocityWest	 =   5.57602; // +/- 1.7705e-05 cm/us All: West = -0.222939 +/- 0.00409813
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57602 +/- 1.7705e-05
  return (TDataSet *)tableSet;// West = 5.57577 +/- 2.32097e-05 East = 5.57637 +/- 2.73817e-05
};
