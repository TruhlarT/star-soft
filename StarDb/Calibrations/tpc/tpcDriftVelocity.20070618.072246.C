TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 169018
  row.laserDriftVelocityEast	 =   5.57129; // +/- 2.07805e-05 cm/us All: East = 0.765368 +/- 0.00475173
  row.laserDriftVelocityWest	 =   5.57129; // +/- 2.07805e-05 cm/us All: West = 0.301866 +/- 0.006043
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57129 +/- 2.07805e-05
  return (TDataSet *)tableSet;// West = 5.57289 +/- 3.34812e-05 East = 5.57028 +/- 2.65032e-05
};
