TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6064038
  row.laserDriftVelocityEast	 =   5.53513; // +/- 4.45978e-05 cm/us All: East = 5.53353 +/- 8.74171e-05
  row.laserDriftVelocityWest	 =   5.53513; // +/- 4.45978e-05 cm/us All: West = 5.53569 +/- 5.18535e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.0311 +/- 0.0081929
  return (TDataSet *)tableSet;// West = 0.923377 +/- 0.00966076 East = 1.307 +/- 0.0154612
};
