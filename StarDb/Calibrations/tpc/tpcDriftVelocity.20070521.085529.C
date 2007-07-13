TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 141028
  row.laserDriftVelocityEast	 =   5.575; // +/- 2.38404e-05 cm/us All: East = -0.0826119 +/- 0.00500563
  row.laserDriftVelocityWest	 =   5.575; // +/- 2.38404e-05 cm/us All: West = -0.0639077 +/- 0.00788213
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.575 +/- 2.38404e-05
  return (TDataSet *)tableSet;// West = 5.57486 +/- 4.33734e-05 East = 5.57505 +/- 2.85379e-05
};
