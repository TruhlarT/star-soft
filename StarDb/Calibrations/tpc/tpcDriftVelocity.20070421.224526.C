TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 111089
  row.laserDriftVelocityEast	 =   5.57338; // +/- 1.15107e-05 cm/us East: Slope = 0.205799 +/- 0.00206362 DV = 5.57338 +/- 1.15107e-05
  row.laserDriftVelocityWest	 =   5.57563; // +/- 1.24494e-05 cm/us West: Slope = -0.197575 +/- 0.00222744 DV = 5.57563 +/- 1.24494e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
