TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 107028
  row.laserDriftVelocityEast	 =   5.57605; // +/- 2.47413e-05 cm/us East: Slope = -0.273476 +/- 0.00434437 DV = 5.57605 +/- 2.47413e-05
  row.laserDriftVelocityWest	 =   5.5771; // +/- 2.79778e-05 cm/us West: Slope = -0.461973 +/- 0.00498099 DV = 5.5771 +/- 2.79778e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
