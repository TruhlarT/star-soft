TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 145014
  row.laserDriftVelocityEast	 =   5.57131; // +/- -1 cm/us East: Slope = 0.0721979 +/- 1.41421 DV = 4.45921 +/- 1.41421
  row.laserDriftVelocityWest	 =   5.57416; // +/- 1.85284e-05 cm/us West: Slope = 0.0678758 +/- 0.00335067 DV = 5.57416 +/- 1.85284e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
