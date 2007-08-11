TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 106107
  row.laserDriftVelocityEast	 =   5.57716; // +/- 1.85473e-05 cm/us East: Slope = -0.485214 +/- 0.003316 DV = 5.57716 +/- 1.85473e-05
  row.laserDriftVelocityWest	 =   5.57857; // +/- 2.49164e-05 cm/us West: Slope = -0.728359 +/- 0.00444103 DV = 5.57857 +/- 2.49164e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
