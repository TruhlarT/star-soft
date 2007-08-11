TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 138070
  row.laserDriftVelocityEast	 =   5.5728; // +/- 2.61895e-05 cm/us East: Slope = 0.306413 +/- 0.00468159 DV = 5.5728 +/- 2.61895e-05
  row.laserDriftVelocityWest	 =   5.57408; // +/- 3.40491e-05 cm/us West: Slope = 0.0832474 +/- 0.00621408 DV = 5.57408 +/- 3.40491e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
