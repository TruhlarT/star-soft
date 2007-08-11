TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 162017
  row.laserDriftVelocityEast	 =   5.56985; // +/- -1 cm/us East: Slope = 0.604172 +/- 0.012412 DV = 5.57114 +/- 6.8582e-05
  row.laserDriftVelocityWest	 =   5.57314; // +/- 2.52929e-05 cm/us West: Slope = 0.246479 +/- 0.00451347 DV = 5.57314 +/- 2.52929e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
