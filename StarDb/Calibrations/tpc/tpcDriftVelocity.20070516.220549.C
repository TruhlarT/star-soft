TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 136056
  row.laserDriftVelocityEast	 =   5.57366; // +/- 1.41829e-05 cm/us East: Slope = 0.150998 +/- 0.00254493 DV = 5.57366 +/- 1.41829e-05
  row.laserDriftVelocityWest	 =   5.57563; // +/- 2.08017e-05 cm/us West: Slope = -0.198456 +/- 0.00374552 DV = 5.57563 +/- 2.08017e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
