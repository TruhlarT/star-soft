TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 119028
  row.laserDriftVelocityEast	 =   5.57837; // +/- 2.28098e-05 cm/us All: East = -0.698663 +/- 0.00500974
  row.laserDriftVelocityWest	 =   5.57837; // +/- 2.28098e-05 cm/us All: West = -0.649566 +/- 0.00675878
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57837 +/- 2.28098e-05
  return (TDataSet *)tableSet;// West = 5.57814 +/- 3.78229e-05 East = 5.5785 +/- 2.85948e-05
};
