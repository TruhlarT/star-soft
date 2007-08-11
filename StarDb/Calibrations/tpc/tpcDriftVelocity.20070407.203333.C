TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 97093
  row.laserDriftVelocityEast	 =   5.5746; // +/- 2.45786e-05 cm/us East: Slope = -1.31862 +/- 0.00435525 DV = 5.5746 +/- 2.45786e-05
  row.laserDriftVelocityWest	 =   5.57498; // +/- 2.64319e-05 cm/us West: Slope = -1.39059 +/- 0.00472314 DV = 5.57498 +/- 2.64319e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
