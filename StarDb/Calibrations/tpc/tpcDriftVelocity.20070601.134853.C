TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 152011
  row.laserDriftVelocityEast	 =   5.57275; // +/- 2.44488e-05 cm/us All: East = 0.660742 +/- 7.77419
  row.laserDriftVelocityWest	 =   5.57275; // +/- 2.44488e-05 cm/us All: West = 0.325485 +/- 0.00437762
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57275 +/- 2.44488e-05
  return (TDataSet *)tableSet;// West = 5.57275 +/- 2.44489e-05 East = 5.57183 +/- 0.0524036
};
