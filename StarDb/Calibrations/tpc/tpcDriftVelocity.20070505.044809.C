TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 125011
  row.laserDriftVelocityEast	 =   5.5787; // +/- 1.57791e-05 cm/us All: East = -0.771998 +/- 0.00330133
  row.laserDriftVelocityWest	 =   5.5787; // +/- 1.57791e-05 cm/us All: West = -0.67561 +/- 0.0055475
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5787 +/- 1.57791e-05
  return (TDataSet *)tableSet;// West = 5.57832 +/- 3.04587e-05 East = 5.57884 +/- 1.84475e-05
};
