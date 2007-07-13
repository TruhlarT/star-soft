TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 122023
  row.laserDriftVelocityEast	 =   5.57998; // +/- 1.79195e-05 cm/us All: East = -0.958838 +/- 0.00415465
  row.laserDriftVelocityWest	 =   5.57998; // +/- 1.79195e-05 cm/us All: West = -1.00553 +/- 0.00509298
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57998 +/- 1.79195e-05
  return (TDataSet *)tableSet;// West = 5.58014 +/- 2.80073e-05 East = 5.57986 +/- 2.33167e-05
};
