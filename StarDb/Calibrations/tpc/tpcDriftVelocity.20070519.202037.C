TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 139066
  row.laserDriftVelocityEast	 =   5.57261; // +/- 2.13521e-05 cm/us East: Slope = 0.348264 +/- 0.00382061 DV = 5.57261 +/- 2.13521e-05
  row.laserDriftVelocityWest	 =   5.5751; // +/- 3.20739e-05 cm/us West: Slope = -0.10325 +/- 0.00572615 DV = 5.5751 +/- 3.20739e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
