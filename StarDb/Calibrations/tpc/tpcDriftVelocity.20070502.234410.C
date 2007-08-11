TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 122080
  row.laserDriftVelocityEast	 =   5.5775; // +/- 3.36364e-05 cm/us East: Slope = -0.531181 +/- 0.00599665 DV = 5.5775 +/- 3.36364e-05
  row.laserDriftVelocityWest	 =   5.57903; // +/- 3.14525e-05 cm/us West: Slope = -0.808537 +/- 0.00565281 DV = 5.57903 +/- 3.14525e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
