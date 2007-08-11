TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 104053
  row.laserDriftVelocityEast	 =   5.57985; // +/- 1.67573e-05 cm/us East: Slope = -0.946681 +/- 0.00301635 DV = 5.57985 +/- 1.67573e-05
  row.laserDriftVelocityWest	 =   5.5813; // +/- 1.70712e-05 cm/us West: Slope = -1.21391 +/- 0.00304716 DV = 5.5813 +/- 1.70712e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
