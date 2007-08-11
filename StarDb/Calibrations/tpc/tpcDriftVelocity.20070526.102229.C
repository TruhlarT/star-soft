TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 146028
  row.laserDriftVelocityEast	 =   5.57118; // +/- -1 cm/us East: Slope = 0.122648 +/- 1.41421 DV = 4.45895 +/- 1.41421
  row.laserDriftVelocityWest	 =   5.57406; // +/- 1.55157e-05 cm/us West: Slope = 0.0862282 +/- 0.00273386 DV = 5.57406 +/- 1.55157e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
