TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 105072
  row.laserDriftVelocityEast	 =   5.58101; // +/- 2.65274e-05 cm/us East: Slope = -1.16014 +/- 0.00469576 DV = 5.58101 +/- 2.65274e-05
  row.laserDriftVelocityWest	 =   5.58301; // +/- 1.89793e-05 cm/us West: Slope = -1.52006 +/- 0.00339472 DV = 5.58301 +/- 1.89793e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
