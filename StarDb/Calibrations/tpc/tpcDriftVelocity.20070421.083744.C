TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 111029
  row.laserDriftVelocityEast	 =   5.57279; // +/- 1.69847e-05 cm/us East: Slope = 0.310563 +/- 0.00303921 DV = 5.57279 +/- 1.69847e-05
  row.laserDriftVelocityWest	 =   5.57461; // +/- 1.82482e-05 cm/us West: Slope = -0.0137826 +/- 0.00326673 DV = 5.57461 +/- 1.82482e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
