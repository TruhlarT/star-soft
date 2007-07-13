TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 159077
  row.laserDriftVelocityEast	 =   5.57406; // +/- 1.90208e-05 cm/us All: East = 0.260804 +/- 0.00577135
  row.laserDriftVelocityWest	 =   5.57406; // +/- 1.90208e-05 cm/us All: West = -0.0125646 +/- 0.00423314
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57406 +/- 1.90208e-05
  return (TDataSet *)tableSet;// West = 5.57461 +/- 2.36006e-05 East = 5.57304 +/- 3.21304e-05
};
