TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 127049
  row.laserDriftVelocityEast	 =   5.57365; // +/- 2.11961e-05 cm/us East: Slope = 0.16232 +/- 0.0038108 DV = 5.57365 +/- 2.11961e-05
  row.laserDriftVelocityWest	 =   5.57592; // +/- 3.80834e-05 cm/us West: Slope = -0.250725 +/- 0.00687538 DV = 5.57592 +/- 3.80834e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
