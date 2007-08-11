TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 147051
  row.laserDriftVelocityEast	 =   5.57054; // +/- -1 cm/us East: Slope = 0.822582 +/- 2.85853 DV = 5.56998 +/- 0.0163425
  row.laserDriftVelocityWest	 =   5.57345; // +/- 1.96987e-05 cm/us West: Slope = 0.193936 +/- 0.00349181 DV = 5.57345 +/- 1.96987e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
