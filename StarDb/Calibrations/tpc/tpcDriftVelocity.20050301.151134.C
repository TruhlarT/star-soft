TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6060032
  row.laserDriftVelocityEast	 =   5.53748; // +/- 5.94766e-05 cm/us All: East = 5.53898 +/- 0.0001338
  row.laserDriftVelocityWest	 =   5.53748; // +/- 5.94766e-05 cm/us All: West = 5.5371 +/- 6.63972e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.29281 +/- 0.0110497
  return (TDataSet *)tableSet;// West = 1.34679 +/- 0.0121733 East = 1.04027 +/- 0.0263322
};
