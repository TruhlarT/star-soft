TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 135069
  row.laserDriftVelocityEast	 =   5.57334; // +/- 2.27948e-05 cm/us East: Slope = 0.205486 +/- 0.00408543 DV = 5.57334 +/- 2.27948e-05
  row.laserDriftVelocityWest	 =   5.57522; // +/- 3.10029e-05 cm/us West: Slope = -0.125052 +/- 0.00562349 DV = 5.57522 +/- 3.10029e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
