TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 144017
  row.laserDriftVelocityEast	 =   5.57384; // +/- 1.85607e-05 cm/us All: East = -0.202281 +/- 0.172676
  row.laserDriftVelocityWest	 =   5.57384; // +/- 1.85607e-05 cm/us All: West = 0.125824 +/- 0.00332364
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57384 +/- 1.85607e-05
  return (TDataSet *)tableSet;// West = 5.57384 +/- 1.85646e-05 East = 5.57668 +/- 0.00089972
};
