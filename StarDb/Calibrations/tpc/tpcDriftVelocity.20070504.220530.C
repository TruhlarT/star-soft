TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 124088
  row.laserDriftVelocityEast	 =   5.57639; // +/- 1.35659e-05 cm/us East: Slope = -0.334874 +/- 0.00242421 DV = 5.57639 +/- 1.35659e-05
  row.laserDriftVelocityWest	 =   5.57909; // +/- 2.40068e-05 cm/us West: Slope = -0.817929 +/- 0.00429744 DV = 5.57909 +/- 2.40068e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
