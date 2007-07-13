TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 110137
  row.laserDriftVelocityEast	 =   5.57504; // +/- 1.8397e-05 cm/us All: East = -0.170701 +/- 0.00536767
  row.laserDriftVelocityWest	 =   5.57504; // +/- 1.8397e-05 cm/us All: West = -0.0505072 +/- 0.00414616
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57504 +/- 1.8397e-05
  return (TDataSet *)tableSet;// West = 5.5748 +/- 2.3167e-05 East = 5.57546 +/- 3.02688e-05
};
