TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 142032
  row.laserDriftVelocityEast	 =   5.57433; // +/- 2.0911e-05 cm/us All: East = -0.037521 +/- 0.0054026
  row.laserDriftVelocityWest	 =   5.57433; // +/- 2.0911e-05 cm/us All: West = 0.0979981 +/- 0.00525544
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57433 +/- 2.0911e-05
  return (TDataSet *)tableSet;// West = 5.57398 +/- 2.91527e-05 East = 5.5747 +/- 3.00113e-05
};
