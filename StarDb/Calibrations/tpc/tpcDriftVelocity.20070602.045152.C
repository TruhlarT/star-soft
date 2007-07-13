TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 153003
  row.laserDriftVelocityEast	 =   5.57275; // +/- 2.33476e-05 cm/us All: East = 0.22049 +/- 23.7892
  row.laserDriftVelocityWest	 =   5.57275; // +/- 2.33476e-05 cm/us All: West = 0.315749 +/- 0.00419503
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57275 +/- 2.33476e-05
  return (TDataSet *)tableSet;// West = 5.57275 +/- 2.33476e-05 East = 5.57332 +/- 0.131802
};
