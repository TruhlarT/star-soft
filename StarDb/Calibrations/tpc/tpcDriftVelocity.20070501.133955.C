TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 121038
  row.laserDriftVelocityEast	 =   5.577; // +/- 2.14086e-05 cm/us East: Slope = -0.441199 +/- 0.00382913 DV = 5.577 +/- 2.14086e-05
  row.laserDriftVelocityWest	 =   5.57896; // +/- 3.26296e-05 cm/us West: Slope = -0.791795 +/- 0.00581577 DV = 5.57896 +/- 3.26296e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
