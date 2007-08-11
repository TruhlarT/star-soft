TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 139093
  row.laserDriftVelocityEast	 =   5.57312; // +/- 3.40871e-05 cm/us East: Slope = 0.2453 +/- 0.00618978 DV = 5.57312 +/- 3.40871e-05
  row.laserDriftVelocityWest	 =   5.57584; // +/- -1 cm/us West: Slope = -0.0251549 +/- 0.00779181 DV = 5.57467 +/- 4.35567e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
