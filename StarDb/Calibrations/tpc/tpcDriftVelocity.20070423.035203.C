TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 112086
  row.laserDriftVelocityEast	 =   5.5761; // +/- 1.26333e-05 cm/us All: East = -0.283705 +/- 0.00235059
  row.laserDriftVelocityWest	 =   5.5761; // +/- 1.26333e-05 cm/us All: West = -0.313885 +/- 0.00794292
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5761 +/- 1.26333e-05
  return (TDataSet *)tableSet;// West = 5.57633 +/- 4.5702e-05 East = 5.57609 +/- 1.31455e-05
};
