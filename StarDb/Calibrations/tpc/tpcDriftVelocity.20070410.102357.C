TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 100073
  row.laserDriftVelocityEast	 =   5.57375; // +/- 1.61691e-05 cm/us All: East = 0.51337 +/- 0.00353563
  row.laserDriftVelocityWest	 =   5.57375; // +/- 1.61691e-05 cm/us All: West = 0.740309 +/- 0.00506644
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57375 +/- 1.61691e-05
  return (TDataSet *)tableSet;// West = 5.57291 +/- 2.81171e-05 East = 5.57417 +/- 1.9764e-05
};
