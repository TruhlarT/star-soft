TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 109095
  row.laserDriftVelocityEast	 =   5.57213; // +/- 1.68858e-05 cm/us East: Slope = 0.427976 +/- 0.00304202 DV = 5.57213 +/- 1.68858e-05
  row.laserDriftVelocityWest	 =   5.57509; // +/- 1.73087e-05 cm/us West: Slope = -0.100291 +/- 0.00311283 DV = 5.57509 +/- 1.73087e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
