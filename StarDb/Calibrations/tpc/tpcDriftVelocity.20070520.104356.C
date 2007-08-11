TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 140023
  row.laserDriftVelocityEast	 =   5.57354; // +/- 2.42097e-05 cm/us East: Slope = 0.189229 +/- 0.00432219 DV = 5.57354 +/- 2.42097e-05
  row.laserDriftVelocityWest	 =   5.57497; // +/- 3.19283e-05 cm/us West: Slope = -0.0826644 +/- 0.00576355 DV = 5.57497 +/- 3.19283e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
