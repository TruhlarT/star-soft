TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 141108
  row.laserDriftVelocityEast	 =   5.57316; // +/- 2.56119e-05 cm/us East: Slope = 0.249459 +/- 0.00461966 DV = 5.57316 +/- 2.56119e-05
  row.laserDriftVelocityWest	 =   5.57456; // +/- 3.05989e-05 cm/us West: Slope = -0.00754179 +/- 0.00552868 DV = 5.57456 +/- 3.05989e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
