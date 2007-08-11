TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 106002
  row.laserDriftVelocityEast	 =   5.5801; // +/- 2.71471e-05 cm/us East: Slope = -1.00578 +/- 0.00486537 DV = 5.5801 +/- 2.71471e-05
  row.laserDriftVelocityWest	 =   5.58139; // +/- 1.82819e-05 cm/us West: Slope = -1.2282 +/- 0.00329309 DV = 5.58139 +/- 1.82819e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
