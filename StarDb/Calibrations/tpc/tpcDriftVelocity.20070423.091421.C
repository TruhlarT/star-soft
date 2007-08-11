TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 113026
  row.laserDriftVelocityEast	 =   5.5747; // +/- 1.9471e-05 cm/us East: Slope = -0.0307866 +/- 0.00347638 DV = 5.5747 +/- 1.9471e-05
  row.laserDriftVelocityWest	 =   5.57639; // +/- 1.98991e-05 cm/us West: Slope = -0.333266 +/- 0.00357078 DV = 5.57639 +/- 1.98991e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
