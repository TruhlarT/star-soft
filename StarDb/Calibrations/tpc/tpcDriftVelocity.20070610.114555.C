TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 161038
  row.laserDriftVelocityEast	 =   5.57006; // +/- -1 cm/us East: Slope = 0.642981 +/- 1.41421 DV = 11.1456 +/- 1.41421
  row.laserDriftVelocityWest	 =   5.57332; // +/- 2.63973e-05 cm/us West: Slope = 0.217519 +/- 0.00468763 DV = 5.57332 +/- 2.63973e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
