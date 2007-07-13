TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 113043
  row.laserDriftVelocityEast	 =   5.57651; // +/- 1.89316e-05 cm/us All: East = -0.392882 +/- 0.00484345
  row.laserDriftVelocityWest	 =   5.57651; // +/- 1.89316e-05 cm/us All: West = -0.324396 +/- 0.0047815
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57651 +/- 1.89316e-05
  return (TDataSet *)tableSet;// West = 5.57632 +/- 2.66951e-05 East = 5.5767 +/- 2.68523e-05
};
