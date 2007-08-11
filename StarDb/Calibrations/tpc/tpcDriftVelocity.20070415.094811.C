TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 105024
  row.laserDriftVelocityEast	 =   5.58111; // +/- 2.13686e-05 cm/us East: Slope = -1.17674 +/- 0.00379577 DV = 5.58111 +/- 2.13686e-05
  row.laserDriftVelocityWest	 =   5.58329; // +/- 2.21497e-05 cm/us West: Slope = -1.5691 +/- 0.00398015 DV = 5.58329 +/- 2.21497e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
