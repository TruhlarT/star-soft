TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 173019
  row.laserDriftVelocityEast	 =   5.56812; // +/- 2.9075e-05 cm/us East: Slope = 1.15197 +/- 0.00525607 DV = 5.56812 +/- 2.9075e-05
  row.laserDriftVelocityWest	 =   5.57208; // +/- 2.95934e-05 cm/us West: Slope = 0.439151 +/- 0.00530459 DV = 5.57208 +/- 2.95934e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
