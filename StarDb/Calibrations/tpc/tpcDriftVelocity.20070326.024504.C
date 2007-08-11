TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 84129
  row.laserDriftVelocityEast	 =   5.5615; // +/- 3.88675e-05 cm/us East: Slope = 1.02888 +/- 0.00702154 DV = 5.5615 +/- 3.88675e-05
  row.laserDriftVelocityWest	 =   5.5628; // +/- -1 cm/us West: Slope = 0.580337 +/- 0.0126466 DV = 5.56413 +/- 7.206e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
