TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6018008
  row.laserDriftVelocityEast	 =   5.54382; // +/- 3.62466e-05 cm/us All: East = 5.54382 +/- 3.62466e-05
  row.laserDriftVelocityWest	 =   5.54382; // +/- 3.62466e-05 cm/us All: West = 1.70551 +/- 1.41421
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.237233 +/- 0.0113929
  return (TDataSet *)tableSet;// West = 0.0941211 +/- 1.41421 East = 0.237233 +/- 0.0113929
};
