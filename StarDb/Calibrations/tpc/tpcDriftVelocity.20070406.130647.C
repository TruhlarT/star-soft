TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 96032
  row.laserDriftVelocityEast	 =   5.57567; // +/- 2.0426e-05 cm/us East: Slope = -1.51182 +/- 0.00362145 DV = 5.57567 +/- 2.0426e-05
  row.laserDriftVelocityWest	 =   5.57643; // +/- 2.2213e-05 cm/us West: Slope = -1.64957 +/- 0.00393744 DV = 5.57643 +/- 2.2213e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
