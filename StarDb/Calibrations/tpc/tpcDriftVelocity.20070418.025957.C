TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 107082
  row.laserDriftVelocityEast	 =   5.5756; // +/- 1.29632e-05 cm/us All: East = -0.0906747 +/- 0.00277142
  row.laserDriftVelocityWest	 =   5.5756; // +/- 1.29632e-05 cm/us All: West = -0.42611 +/- 0.00424503
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5756 +/- 1.29632e-05
  return (TDataSet *)tableSet;// West = 5.5769 +/- 2.35696e-05 East = 5.57503 +/- 1.55217e-05
};
