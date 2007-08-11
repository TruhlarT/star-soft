TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 104079
  row.laserDriftVelocityEast	 =   5.58003; // +/- 1.84877e-05 cm/us East: Slope = -0.975951 +/- 0.0033311 DV = 5.58003 +/- 1.84877e-05
  row.laserDriftVelocityWest	 =   5.58237; // +/- 1.72619e-05 cm/us West: Slope = -1.40425 +/- 0.00308613 DV = 5.58237 +/- 1.72619e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
