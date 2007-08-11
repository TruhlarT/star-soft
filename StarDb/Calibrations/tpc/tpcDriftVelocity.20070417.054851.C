TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 107005
  row.laserDriftVelocityEast	 =   5.57707; // +/- 2.8553e-05 cm/us East: Slope = -0.458353 +/- 0.00509018 DV = 5.57707 +/- 2.8553e-05
  row.laserDriftVelocityWest	 =   5.57811; // +/- 2.65514e-05 cm/us West: Slope = -0.637061 +/- 0.00475747 DV = 5.57811 +/- 2.65514e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
