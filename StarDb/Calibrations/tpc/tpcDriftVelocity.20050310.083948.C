TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6069011
  row.laserDriftVelocityEast	 =   5.53228; // +/- 4.90597e-05 cm/us All: East = 5.53214 +/- 8.7567e-05
  row.laserDriftVelocityWest	 =   5.53228; // +/- 4.90597e-05 cm/us All: West = 5.53235 +/- 5.92278e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.686348 +/- 0.00887377
  return (TDataSet *)tableSet;// West = 0.67349 +/- 0.0106863 East = 0.714906 +/- 0.0159261
};
