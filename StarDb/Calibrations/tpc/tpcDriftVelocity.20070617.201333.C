TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 168081
  row.laserDriftVelocityEast	 =   5.56824; // +/- 1.97234e-05 cm/us East: Slope = 1.12763 +/- 0.00354721 DV = 5.56824 +/- 1.97234e-05
  row.laserDriftVelocityWest	 =   5.57236; // +/- 2.27606e-05 cm/us West: Slope = 0.389197 +/- 0.00409042 DV = 5.57236 +/- 2.27606e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
