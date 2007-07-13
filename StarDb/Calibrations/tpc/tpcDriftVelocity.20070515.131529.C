TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 135051
  row.laserDriftVelocityEast	 =   5.5747; // +/- 2.16234e-05 cm/us All: East = -0.00750152 +/- 0.00431007
  row.laserDriftVelocityWest	 =   5.5747; // +/- 2.16234e-05 cm/us All: West = -0.143879 +/- 0.00841528
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5747 +/- 2.16234e-05
  return (TDataSet *)tableSet;// West = 5.57527 +/- 4.7464e-05 East = 5.57455 +/- 2.42906e-05
};
