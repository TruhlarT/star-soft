TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 124003
  row.laserDriftVelocityEast	 =   5.57615; // +/- 1.98677e-05 cm/us East: Slope = -0.2888 +/- 0.00358899 DV = 5.57615 +/- 1.98677e-05
  row.laserDriftVelocityWest	 =   5.57903; // +/- 3.62637e-05 cm/us West: Slope = -0.80951 +/- 0.00632975 DV = 5.57903 +/- 3.62637e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
