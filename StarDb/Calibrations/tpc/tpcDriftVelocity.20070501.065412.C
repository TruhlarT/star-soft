TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 121013
  row.laserDriftVelocityEast	 =   5.57728; // +/- 1.90265e-05 cm/us East: Slope = -0.494537 +/- 0.00342109 DV = 5.57728 +/- 1.90265e-05
  row.laserDriftVelocityWest	 =   5.5789; // +/- 2.19457e-05 cm/us West: Slope = -0.781911 +/- 0.00393322 DV = 5.5789 +/- 2.19457e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
