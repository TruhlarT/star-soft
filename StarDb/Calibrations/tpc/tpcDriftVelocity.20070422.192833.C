TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 112050
  row.laserDriftVelocityEast	 =   5.57353; // +/- 1.87815e-05 cm/us East: Slope = 0.180358 +/- 0.00341419 DV = 5.57353 +/- 1.87815e-05
  row.laserDriftVelocityWest	 =   5.57527; // +/- 2.78305e-05 cm/us West: Slope = -0.133371 +/- 0.00498743 DV = 5.57527 +/- 2.78305e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
