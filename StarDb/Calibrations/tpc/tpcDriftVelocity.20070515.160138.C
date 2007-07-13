TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 135069
  row.laserDriftVelocityEast	 =   5.57528; // +/- 1.83332e-05 cm/us All: East = -0.142751 +/- 0.00408095
  row.laserDriftVelocityWest	 =   5.57528; // +/- 1.83332e-05 cm/us All: West = -0.124212 +/- 0.00561484
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57528 +/- 1.83332e-05
  return (TDataSet *)tableSet;// West = 5.57522 +/- 3.13317e-05 East = 5.57531 +/- 2.26075e-05
};
