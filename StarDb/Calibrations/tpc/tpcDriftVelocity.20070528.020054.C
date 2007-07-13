TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 147102
  row.laserDriftVelocityEast	 =   5.57429; // +/- 1.82054e-05 cm/us All: East = 0 +/- 0
  row.laserDriftVelocityWest	 =   5.57429; // +/- 1.82054e-05 cm/us All: West = 0.0501766 +/- 0.00328184
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57429 +/- 1.82054e-05
  return (TDataSet *)tableSet;// West = 5.57429 +/- 1.82054e-05 East = 0 +/- 0
};
