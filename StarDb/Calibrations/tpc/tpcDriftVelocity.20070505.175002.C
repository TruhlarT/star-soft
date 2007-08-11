TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 125081
  row.laserDriftVelocityEast	 =   5.57675; // +/- 2.43894e-05 cm/us East: Slope = -0.403788 +/- 0.00438588 DV = 5.57675 +/- 2.43894e-05
  row.laserDriftVelocityWest	 =   5.5791; // +/- 2.64709e-05 cm/us West: Slope = -0.819249 +/- 0.00476234 DV = 5.5791 +/- 2.64709e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
