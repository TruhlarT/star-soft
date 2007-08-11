TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 169052
  row.laserDriftVelocityEast	 =   5.5679; // +/- 2.99682e-05 cm/us East: Slope = 1.19368 +/- 0.00537771 DV = 5.5679 +/- 2.99682e-05
  row.laserDriftVelocityWest	 =   5.57195; // +/- 3.04215e-05 cm/us West: Slope = 0.463291 +/- 0.00542093 DV = 5.57195 +/- 3.04215e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
