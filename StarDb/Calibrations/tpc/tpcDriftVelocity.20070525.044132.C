TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 145003
  row.laserDriftVelocityEast	 =   5.57377; // +/- 2.10144e-05 cm/us All: East = -0.0717956 +/- 0.112474
  row.laserDriftVelocityWest	 =   5.57377; // +/- 2.10144e-05 cm/us All: West = 0.135206 +/- 0.00376372
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57377 +/- 2.10144e-05
  return (TDataSet *)tableSet;// West = 5.57377 +/- 2.10274e-05 East = 5.57447 +/- 0.000597487
};
