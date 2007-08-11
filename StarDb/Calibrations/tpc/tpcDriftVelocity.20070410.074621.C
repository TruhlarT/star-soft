TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 100027
  row.laserDriftVelocityEast	 =   5.57137; // +/- 1.71355e-05 cm/us East: Slope = 1.01988 +/- 0.00308889 DV = 5.57137 +/- 1.71355e-05
  row.laserDriftVelocityWest	 =   5.573; // +/- 1.93223e-05 cm/us West: Slope = 0.729225 +/- 0.00344647 DV = 5.573 +/- 1.93223e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
