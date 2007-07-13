TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 92105
  row.laserDriftVelocityEast	 =   5.58367; // +/- 1.72197e-05 cm/us All: East = -3.10736 +/- 0.0050814
  row.laserDriftVelocityWest	 =   5.58367; // +/- 1.72197e-05 cm/us All: West = -2.84772 +/- 0.00382292
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.58367 +/- 1.72197e-05
  return (TDataSet *)tableSet;// West = 5.58313 +/- 2.16135e-05 East = 5.58461 +/- 2.84922e-05
};
