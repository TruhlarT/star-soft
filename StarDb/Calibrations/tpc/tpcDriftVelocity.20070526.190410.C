TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 146061
  row.laserDriftVelocityEast	 =   5.57119; // +/- -1 cm/us East: Slope = -0.0545469 +/- 1.61183 DV = 5.57424 +/- 0.00536496
  row.laserDriftVelocityWest	 =   5.57407; // +/- 1.17315e-05 cm/us West: Slope = 0.083415 +/- 0.00211168 DV = 5.57407 +/- 1.17315e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
