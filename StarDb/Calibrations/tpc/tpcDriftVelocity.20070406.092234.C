TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 96023
  row.laserDriftVelocityEast	 =   5.5754; // +/- 1.70516e-05 cm/us East: Slope = -1.46426 +/- 0.00303339 DV = 5.5754 +/- 1.70516e-05
  row.laserDriftVelocityWest	 =   5.57676; // +/- 2.14625e-05 cm/us West: Slope = -1.71073 +/- 0.00391545 DV = 5.57676 +/- 2.14625e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
