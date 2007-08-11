TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 127014
  row.laserDriftVelocityEast	 =   5.57358; // +/- 1.73761e-05 cm/us East: Slope = 0.170847 +/- 0.00308788 DV = 5.57358 +/- 1.73761e-05
  row.laserDriftVelocityWest	 =   5.57582; // +/- 3.54403e-05 cm/us West: Slope = -0.230353 +/- 0.0065718 DV = 5.57582 +/- 3.54403e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
