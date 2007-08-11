TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 167065
  row.laserDriftVelocityEast	 =   5.56808; // +/- 2.20995e-05 cm/us East: Slope = 1.15266 +/- 0.00397905 DV = 5.56808 +/- 2.20995e-05
  row.laserDriftVelocityWest	 =   5.57303; // +/- 2.94433e-05 cm/us West: Slope = 0.265589 +/- 0.00524188 DV = 5.57303 +/- 2.94433e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
