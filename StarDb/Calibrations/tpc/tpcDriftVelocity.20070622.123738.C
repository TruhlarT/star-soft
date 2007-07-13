TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 173028
  row.laserDriftVelocityEast	 =   5.57116; // +/- 2.00094e-05 cm/us All: East = 0.762471 +/- 0.00501541
  row.laserDriftVelocityWest	 =   5.57116; // +/- 2.00094e-05 cm/us All: West = 0.430674 +/- 0.00519271
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57116 +/- 2.00094e-05
  return (TDataSet *)tableSet;// West = 5.57213 +/- 2.89298e-05 East = 5.57027 +/- 2.7705e-05
};
