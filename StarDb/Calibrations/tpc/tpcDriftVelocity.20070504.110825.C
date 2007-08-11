TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 124026
  row.laserDriftVelocityEast	 =   5.57624; // +/- 1.72137e-05 cm/us East: Slope = -0.306013 +/- 0.00309595 DV = 5.57624 +/- 1.72137e-05
  row.laserDriftVelocityWest	 =   5.57841; // +/- 3.63252e-05 cm/us West: Slope = -0.696944 +/- 0.00644946 DV = 5.57841 +/- 3.63252e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
