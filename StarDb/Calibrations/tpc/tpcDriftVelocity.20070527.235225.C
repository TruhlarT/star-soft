TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 147093
  row.laserDriftVelocityEast	 =   5.57173; // +/- -1 cm/us East: Slope = 0.357256 +/- 0.054789 DV = 5.57247 +/- 0.000311123
  row.laserDriftVelocityWest	 =   5.57465; // +/- 1.43276e-05 cm/us West: Slope = -0.0224287 +/- 0.002577 DV = 5.57465 +/- 1.43276e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
