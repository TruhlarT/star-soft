TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6072016
  row.laserDriftVelocityEast	 =   5.53222; // +/- 3.96528e-05 cm/us All: East = 5.53272 +/- 5.90226e-05
  row.laserDriftVelocityWest	 =   5.53222; // +/- 3.96528e-05 cm/us All: West = 5.5318 +/- 5.35333e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.3161 +/- 0.00710718
  return (TDataSet *)tableSet;// West = 0.394196 +/- 0.0096047 East = 0.221589 +/- 0.0105661
};
