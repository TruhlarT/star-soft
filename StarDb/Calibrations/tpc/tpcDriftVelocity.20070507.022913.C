TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 126095
  row.laserDriftVelocityEast	 =   5.57458; // +/- 1.72306e-05 cm/us East: Slope = -0.0150009 +/- 0.00305783 DV = 5.57458 +/- 1.72306e-05
  row.laserDriftVelocityWest	 =   5.57584; // +/- 2.27485e-05 cm/us West: Slope = -0.235593 +/- 0.00407977 DV = 5.57584 +/- 2.27485e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
