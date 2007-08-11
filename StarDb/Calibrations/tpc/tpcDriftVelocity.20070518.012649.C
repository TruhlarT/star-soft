TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 137073
  row.laserDriftVelocityEast	 =   5.57276; // +/- 1.53849e-05 cm/us East: Slope = 0.316708 +/- 0.00276354 DV = 5.57276 +/- 1.53849e-05
  row.laserDriftVelocityWest	 =   5.5745; // +/- 2.23917e-05 cm/us West: Slope = 0.00614414 +/- 0.0040087 DV = 5.5745 +/- 2.23917e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
