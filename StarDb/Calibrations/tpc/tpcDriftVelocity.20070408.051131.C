TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 98006
  row.laserDriftVelocityEast	 =   5.57254; // +/- 3.78209e-05 cm/us East: Slope = -0.956366 +/- 0.00690475 DV = 5.57254 +/- 3.78209e-05
  row.laserDriftVelocityWest	 =   5.57418; // +/- -1 cm/us West: Slope = 0 +/- 0 DV = 0 +/- 0
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
