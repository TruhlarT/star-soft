TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 138002
  row.laserDriftVelocityEast	 =   5.57271; // +/- 2.02593e-05 cm/us East: Slope = 0.3245 +/- 0.00362266 DV = 5.57271 +/- 2.02593e-05
  row.laserDriftVelocityWest	 =   5.57475; // +/- 3.67064e-05 cm/us West: Slope = -0.0375429 +/- 0.00657412 DV = 5.57475 +/- 3.67064e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
