TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 102110
  row.laserDriftVelocityEast	 =   5.57298; // +/- 7.28965e-06 cm/us East: Slope = 0.27561 +/- 0.00131268 DV = 5.57298 +/- 7.28965e-06
  row.laserDriftVelocityWest	 =   5.57526; // +/- 9.56883e-06 cm/us West: Slope = -0.131365 +/- 0.00171385 DV = 5.57526 +/- 9.56883e-06
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
