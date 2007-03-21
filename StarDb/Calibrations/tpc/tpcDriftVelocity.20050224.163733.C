TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6055029
  row.laserDriftVelocityEast	 =   5.53269; // +/- 0.000101132 cm/us All: East = 5.5361 +/- 0.000284292
  row.laserDriftVelocityWest	 =   5.53269; // +/- 0.000101132 cm/us All: West = 5.5322 +/- 0.00010821
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.20259 +/- 0.018241
  return (TDataSet *)tableSet;// West = 1.29556 +/- 0.0195112 East = 0.557422 +/- 0.0513966
};
