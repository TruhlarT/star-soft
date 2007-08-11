TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 109018
  row.laserDriftVelocityEast	 =   5.5714; // +/- 1.34277e-05 cm/us East: Slope = 0.561917 +/- 0.00240564 DV = 5.5714 +/- 1.34277e-05
  row.laserDriftVelocityWest	 =   5.57543; // +/- 1.37908e-05 cm/us West: Slope = -0.162196 +/- 0.00247369 DV = 5.57543 +/- 1.37908e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
