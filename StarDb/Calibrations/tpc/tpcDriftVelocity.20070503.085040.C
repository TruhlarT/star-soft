TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 123010
  row.laserDriftVelocityEast	 =   5.57682; // +/- 1.90905e-05 cm/us East: Slope = -0.40368 +/- 0.00343822 DV = 5.57682 +/- 1.90905e-05
  row.laserDriftVelocityWest	 =   5.57812; // +/- 2.08456e-05 cm/us West: Slope = -0.643813 +/- 0.00374302 DV = 5.57812 +/- 2.08456e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
