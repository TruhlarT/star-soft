TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 174090
  row.laserDriftVelocityEast	 =   5.5696; // +/- 3.17393e-05 cm/us East: Slope = 0.887722 +/- 0.0058532 DV = 5.5696 +/- 3.17393e-05
  row.laserDriftVelocityWest	 =   5.57298; // +/- 3.00797e-05 cm/us West: Slope = 0.277362 +/- 0.00543585 DV = 5.57298 +/- 3.00797e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
