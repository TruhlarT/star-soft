TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 91097
  row.laserDriftVelocityEast	 =   5.58198; // +/- 2.86742e-05 cm/us East: Slope = -2.6434 +/- 0.00513995 DV = 5.58198 +/- 2.86742e-05
  row.laserDriftVelocityWest	 =   5.58287; // +/- 1.74376e-05 cm/us West: Slope = -2.80052 +/- 0.00311345 DV = 5.58287 +/- 1.74376e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
