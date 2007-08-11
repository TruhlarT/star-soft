TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 174010
  row.laserDriftVelocityEast	 =   5.56893; // +/- 3.31309e-05 cm/us East: Slope = 0.999564 +/- 0.00588958 DV = 5.56893 +/- 3.31309e-05
  row.laserDriftVelocityWest	 =   5.57222; // +/- 2.99186e-05 cm/us West: Slope = 0.416366 +/- 0.00544634 DV = 5.57222 +/- 2.99186e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
