TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 118081
  row.laserDriftVelocityEast	 =   5.57593; // +/- 1.72867e-05 cm/us East: Slope = -0.251589 +/- 0.00311682 DV = 5.57593 +/- 1.72867e-05
  row.laserDriftVelocityWest	 =   5.57787; // +/- 1.88547e-05 cm/us West: Slope = -0.59852 +/- 0.00335573 DV = 5.57787 +/- 1.88547e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
