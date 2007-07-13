TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 119077
  row.laserDriftVelocityEast	 =   5.57809; // +/- 1.67494e-05 cm/us All: East = -0.627965 +/- 0.00360861
  row.laserDriftVelocityWest	 =   5.57809; // +/- 1.67494e-05 cm/us All: West = -0.654137 +/- 0.00541109
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57809 +/- 1.67494e-05
  return (TDataSet *)tableSet;// West = 5.57821 +/- 3.00224e-05 East = 5.57803 +/- 2.01821e-05
};
