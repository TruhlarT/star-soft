TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 161050
  row.laserDriftVelocityEast	 =   5.57348; // +/- 2.78362e-05 cm/us All: East = 0.287348 +/- 0.0139177
  row.laserDriftVelocityWest	 =   5.57348; // +/- 2.78362e-05 cm/us All: West = 0.173478 +/- 0.00540121
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57348 +/- 2.78362e-05
  return (TDataSet *)tableSet;// West = 5.57355 +/- 2.97996e-05 East = 5.57299 +/- 7.79774e-05
};
