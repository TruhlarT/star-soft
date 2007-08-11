TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 107058
  row.laserDriftVelocityEast	 =   5.57424; // +/- 1.91805e-05 cm/us East: Slope = 0.0529216 +/- 0.00337051 DV = 5.57424 +/- 1.91805e-05
  row.laserDriftVelocityWest	 =   5.57713; // +/- 2.985e-05 cm/us West: Slope = -0.467125 +/- 0.00534157 DV = 5.57713 +/- 2.985e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
