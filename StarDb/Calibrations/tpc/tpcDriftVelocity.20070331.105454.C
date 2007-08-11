TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 90018
  row.laserDriftVelocityEast	 =   5.58186; // +/- 2.21704e-05 cm/us East: Slope = -2.61296 +/- 0.00387487 DV = 5.58186 +/- 2.21704e-05
  row.laserDriftVelocityWest	 =   5.58347; // +/- 2.69632e-05 cm/us West: Slope = -2.9086 +/- 0.00480747 DV = 5.58347 +/- 2.69632e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
