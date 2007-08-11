TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 163074
  row.laserDriftVelocityEast	 =   5.5685; // +/- -1 cm/us East: Slope = 0.386428 +/- 1.41421 DV = 3.34255 +/- 1.41421
  row.laserDriftVelocityWest	 =   5.57183; // +/- 3.07566e-05 cm/us West: Slope = 0.481851 +/- 0.00549669 DV = 5.57183 +/- 3.07566e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
