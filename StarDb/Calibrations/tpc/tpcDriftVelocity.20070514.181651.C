TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 134038
  row.laserDriftVelocityEast	 =   5.5713; // +/- 2.31113e-05 cm/us East: Slope = 0.577257 +/- 0.00414485 DV = 5.5713 +/- 2.31113e-05
  row.laserDriftVelocityWest	 =   5.57258; // +/- 3.83494e-05 cm/us West: Slope = 0.354694 +/- 0.00684064 DV = 5.57258 +/- 3.83494e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
