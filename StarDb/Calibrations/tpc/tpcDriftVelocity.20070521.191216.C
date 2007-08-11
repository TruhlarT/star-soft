TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 141066
  row.laserDriftVelocityEast	 =   5.57222; // +/- 2.27717e-05 cm/us East: Slope = 0.411457 +/- 0.00409718 DV = 5.57222 +/- 2.27717e-05
  row.laserDriftVelocityWest	 =   5.57523; // +/- 3.89397e-05 cm/us West: Slope = -0.126073 +/- 0.00702647 DV = 5.57523 +/- 3.89397e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
