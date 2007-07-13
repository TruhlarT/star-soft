TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 106002
  row.laserDriftVelocityEast	 =   5.58161; // +/- 1.51148e-05 cm/us All: East = -1.36877 +/- 0.00486434
  row.laserDriftVelocityWest	 =   5.58161; // +/- 1.51148e-05 cm/us All: West = -1.2273 +/- 0.00327503
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.58161 +/- 1.51148e-05
  return (TDataSet *)tableSet;// West = 5.58138 +/- 1.82372e-05 East = 5.58213 +/- 2.70116e-05
};
