TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 105072
  row.laserDriftVelocityEast	 =   5.583; // +/- 1.54523e-05 cm/us All: East = -1.51581 +/- 0.00468131
  row.laserDriftVelocityWest	 =   5.583; // +/- 1.54523e-05 cm/us All: West = -1.52005 +/- 0.00338099
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.583 +/- 1.54523e-05
  return (TDataSet *)tableSet;// West = 5.58302 +/- 1.90753e-05 East = 5.58298 +/- 2.6354e-05
};
