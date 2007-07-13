TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 112021
  row.laserDriftVelocityEast	 =   5.57511; // +/- 1.57035e-05 cm/us All: East = -0.120799 +/- 0.00334851
  row.laserDriftVelocityWest	 =   5.57511; // +/- 1.57035e-05 cm/us All: West = -0.0896129 +/- 0.00504223
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57511 +/- 1.57035e-05
  return (TDataSet *)tableSet;// West = 5.57501 +/- 2.78884e-05 East = 5.57515 +/- 1.90022e-05
};
