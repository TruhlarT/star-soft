TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 95139
  row.laserDriftVelocityEast	 =   5.57651; // +/- 2.01704e-05 cm/us East: Slope = -1.66307 +/- 0.00363405 DV = 5.57651 +/- 2.01704e-05
  row.laserDriftVelocityWest	 =   5.57755; // +/- 2.26363e-05 cm/us West: Slope = -1.8477 +/- 0.00406438 DV = 5.57755 +/- 2.26363e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
