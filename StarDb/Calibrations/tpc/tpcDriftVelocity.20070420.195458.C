TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 110111
  row.laserDriftVelocityEast	 =   5.57534; // +/- 1.92072e-05 cm/us All: East = -0.298567 +/- 0.00612882
  row.laserDriftVelocityWest	 =   5.57534; // +/- 1.92072e-05 cm/us All: West = -0.0772107 +/- 0.00414892
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57534 +/- 1.92072e-05
  return (TDataSet *)tableSet;// West = 5.57495 +/- 2.3049e-05 East = 5.5762 +/- 3.47458e-05
};
