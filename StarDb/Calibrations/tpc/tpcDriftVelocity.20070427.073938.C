TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 117020
  row.laserDriftVelocityEast	 =   5.5752; // +/- 1.87489e-05 cm/us East: Slope = -0.121875 +/- 0.00332734 DV = 5.5752 +/- 1.87489e-05
  row.laserDriftVelocityWest	 =   5.57712; // +/- 1.96023e-05 cm/us West: Slope = -0.463472 +/- 0.00353079 DV = 5.57712 +/- 1.96023e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
