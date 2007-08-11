TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 144017
  row.laserDriftVelocityEast	 =   5.57105; // +/- -1 cm/us East: Slope = 0.102338 +/- 0.145967 DV = 5.57404 +/- 0.000877603
  row.laserDriftVelocityWest	 =   5.57389; // +/- 1.28274e-05 cm/us West: Slope = 0.115863 +/- 0.00230482 DV = 5.57389 +/- 1.28274e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
