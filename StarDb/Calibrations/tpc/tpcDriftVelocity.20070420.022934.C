TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 109108
  row.laserDriftVelocityEast	 =   5.57473; // +/- 1.79338e-05 cm/us All: East = -0.000575148 +/- 0.00431803
  row.laserDriftVelocityWest	 =   5.57473; // +/- 1.79338e-05 cm/us All: West = -0.0765677 +/- 0.00473296
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57473 +/- 1.79338e-05
  return (TDataSet *)tableSet;// West = 5.57496 +/- 2.66697e-05 East = 5.57454 +/- 2.42299e-05
};
