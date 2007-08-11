TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 177019
  row.laserDriftVelocityEast	 =   5.56721; // +/- 3.47736e-05 cm/us East: Slope = 1.31457 +/- 0.00625139 DV = 5.56721 +/- 3.47736e-05
  row.laserDriftVelocityWest	 =   5.57064; // +/- 3.13751e-05 cm/us West: Slope = 0.693334 +/- 0.00566824 DV = 5.57064 +/- 3.13751e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
