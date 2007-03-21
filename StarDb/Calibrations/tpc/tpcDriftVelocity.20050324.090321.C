TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6083016
  row.laserDriftVelocityEast	 =   5.52539; // +/- 4.36322e-05 cm/us All: East = 5.5247 +/- 6.63508e-05
  row.laserDriftVelocityWest	 =   5.52539; // +/- 4.36322e-05 cm/us All: West = 5.52591 +/- 5.79161e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.448167 +/- 0.00794508
  return (TDataSet *)tableSet;// West = 0.343154 +/- 0.0106429 East = 0.580357 +/- 0.0119409
};
