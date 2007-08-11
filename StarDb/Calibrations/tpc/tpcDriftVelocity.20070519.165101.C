TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 139050
  row.laserDriftVelocityEast	 =   5.57302; // +/- 3.92068e-05 cm/us East: Slope = 0.262644 +/- 0.00718088 DV = 5.57302 +/- 3.92068e-05
  row.laserDriftVelocityWest	 =   5.57461; // +/- 3.821e-05 cm/us West: Slope = -0.0148078 +/- 0.00695881 DV = 5.57461 +/- 3.821e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
