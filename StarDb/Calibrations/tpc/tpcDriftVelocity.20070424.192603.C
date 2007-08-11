TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 114079
  row.laserDriftVelocityEast	 =   5.57554; // +/- 1.55839e-05 cm/us East: Slope = -0.186101 +/- 0.00280032 DV = 5.57554 +/- 1.55839e-05
  row.laserDriftVelocityWest	 =   5.57755; // +/- 2.07616e-05 cm/us West: Slope = -0.539286 +/- 0.00374078 DV = 5.57755 +/- 2.07616e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
