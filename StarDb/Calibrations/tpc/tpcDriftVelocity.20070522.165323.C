TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 142024
  row.laserDriftVelocityEast	 =   5.57158; // +/- 1.24361e-05 cm/us East: Slope = 0.526891 +/- 0.00221642 DV = 5.57158 +/- 1.24361e-05
  row.laserDriftVelocityWest	 =   5.57424; // +/- 1.62563e-05 cm/us West: Slope = 0.051136 +/- 0.00289871 DV = 5.57424 +/- 1.62563e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
