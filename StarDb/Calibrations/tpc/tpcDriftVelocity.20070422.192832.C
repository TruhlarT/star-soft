TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 112050
  row.laserDriftVelocityEast	 =   5.57542; // +/- 1.55693e-05 cm/us All: East = -0.171179 +/- 0.00338866
  row.laserDriftVelocityWest	 =   5.57542; // +/- 1.55693e-05 cm/us All: West = -0.134339 +/- 0.00501108
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57542 +/- 1.55693e-05
  return (TDataSet *)tableSet;// West = 5.57528 +/- 2.78879e-05 East = 5.57548 +/- 1.87661e-05
};
