TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 122094
  row.laserDriftVelocityEast	 =   5.57762; // +/- 2.06316e-05 cm/us East: Slope = -0.556122 +/- 0.00372681 DV = 5.57762 +/- 2.06316e-05
  row.laserDriftVelocityWest	 =   5.57874; // +/- 2.77554e-05 cm/us West: Slope = -0.752392 +/- 0.00490176 DV = 5.57874 +/- 2.77554e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
