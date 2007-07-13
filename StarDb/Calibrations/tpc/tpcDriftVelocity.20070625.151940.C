TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 176047
  row.laserDriftVelocityEast	 =   5.57132; // +/- 2.43514e-05 cm/us All: East = 0.764638 +/- 0.00624235
  row.laserDriftVelocityWest	 =   5.57132; // +/- 2.43514e-05 cm/us All: West = 0.417312 +/- 0.00586239
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57132 +/- 2.43514e-05
  return (TDataSet *)tableSet;// West = 5.57222 +/- 3.33789e-05 East = 5.5703 +/- 3.56049e-05
};
