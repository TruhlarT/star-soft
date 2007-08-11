TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 158168
  row.laserDriftVelocityEast	 =   5.57029; // +/- -1 cm/us East: Slope = 0.503545 +/- 1.41421 DV = 11.1463 +/- 1.41421
  row.laserDriftVelocityWest	 =   5.57349; // +/- 2.38007e-05 cm/us West: Slope = 0.182822 +/- 0.0042354 DV = 5.57349 +/- 2.38007e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
