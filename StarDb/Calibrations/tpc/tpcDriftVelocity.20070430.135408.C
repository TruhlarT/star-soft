TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 120049
  row.laserDriftVelocityEast	 =   5.57928; // +/- 1.48074e-05 cm/us All: East = -0.873122 +/- 0.00288252
  row.laserDriftVelocityWest	 =   5.57928; // +/- 1.48074e-05 cm/us All: West = -0.733473 +/- 0.00675331
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57928 +/- 1.48074e-05
  return (TDataSet *)tableSet;// West = 5.57862 +/- 3.78937e-05 East = 5.5794 +/- 1.60863e-05
};
