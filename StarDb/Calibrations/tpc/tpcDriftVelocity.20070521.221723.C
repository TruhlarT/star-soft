TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 141078
  row.laserDriftVelocityEast	 =   5.57502; // +/- 2.13281e-05 cm/us All: East = -0.167632 +/- 0.00535575
  row.laserDriftVelocityWest	 =   5.57502; // +/- 2.13281e-05 cm/us All: West = -0.00131013 +/- 0.00547242
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57502 +/- 2.13281e-05
  return (TDataSet *)tableSet;// West = 5.57455 +/- 3.07739e-05 East = 5.57545 +/- 2.95861e-05
};
