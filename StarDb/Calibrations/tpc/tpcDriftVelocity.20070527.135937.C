TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 147051
  row.laserDriftVelocityEast	 =   5.57346; // +/- 1.9664e-05 cm/us All: East = 0.46511 +/- 2.87017
  row.laserDriftVelocityWest	 =   5.57346; // +/- 1.9664e-05 cm/us All: West = 0.192042 +/- 0.00352035
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57346 +/- 1.9664e-05
  return (TDataSet *)tableSet;// West = 5.57346 +/- 1.9664e-05 East = 5.57198 +/- 0.0122822
};
