TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 113064
  row.laserDriftVelocityEast	 =   5.5752; // +/- 1.72634e-05 cm/us East: Slope = -0.114166 +/- 0.00310452 DV = 5.5752 +/- 1.72634e-05
  row.laserDriftVelocityWest	 =   5.57673; // +/- 1.89411e-05 cm/us West: Slope = -0.395108 +/- 0.00341813 DV = 5.57673 +/- 1.89411e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
