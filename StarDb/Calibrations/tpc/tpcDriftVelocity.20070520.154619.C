TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 140041
  row.laserDriftVelocityEast	 =   5.57344; // +/- 2.1676e-05 cm/us East: Slope = 0.195315 +/- 0.00391381 DV = 5.57344 +/- 2.1676e-05
  row.laserDriftVelocityWest	 =   5.5751; // +/- 3.12645e-05 cm/us West: Slope = -0.0997519 +/- 0.00566051 DV = 5.5751 +/- 3.12645e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
