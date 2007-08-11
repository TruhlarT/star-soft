TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 104034
  row.laserDriftVelocityEast	 =   5.57811; // +/- 1.95254e-05 cm/us East: Slope = -0.643375 +/- 0.00348713 DV = 5.57811 +/- 1.95254e-05
  row.laserDriftVelocityWest	 =   5.58037; // +/- 2.2074e-05 cm/us West: Slope = -1.04636 +/- 0.00405539 DV = 5.58037 +/- 2.2074e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
