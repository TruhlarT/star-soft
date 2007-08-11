TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 112021
  row.laserDriftVelocityEast	 =   5.57344; // +/- 1.4102e-05 cm/us East: Slope = 0.193161 +/- 0.00252524 DV = 5.57344 +/- 1.4102e-05
  row.laserDriftVelocityWest	 =   5.57506; // +/- 1.95477e-05 cm/us West: Slope = -0.0945243 +/- 0.00348243 DV = 5.57506 +/- 1.95477e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
