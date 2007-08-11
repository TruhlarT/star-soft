TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 96119
  row.laserDriftVelocityEast	 =   5.57517; // +/- 3.37379e-05 cm/us East: Slope = -1.42662 +/- 0.00599074 DV = 5.57517 +/- 3.37379e-05
  row.laserDriftVelocityWest	 =   5.57613; // +/- 2.19615e-05 cm/us West: Slope = -1.59493 +/- 0.00397822 DV = 5.57613 +/- 2.19615e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
