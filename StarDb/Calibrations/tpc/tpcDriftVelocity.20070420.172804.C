TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 110096
  row.laserDriftVelocityEast	 =   5.57485; // +/- 1.67437e-05 cm/us All: East = -0.0958561 +/- 0.00440679
  row.laserDriftVelocityWest	 =   5.57485; // +/- 1.67437e-05 cm/us All: West = -0.0224496 +/- 0.004183
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57485 +/- 1.67437e-05
  return (TDataSet *)tableSet;// West = 5.57466 +/- 2.3359e-05 East = 5.57505 +/- 2.4013e-05
};
