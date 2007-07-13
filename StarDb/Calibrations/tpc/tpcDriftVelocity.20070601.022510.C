TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 151074
  row.laserDriftVelocityEast	 =   5.57234; // +/- 2.37281e-05 cm/us All: East = 1.03355 +/- 1.08056
  row.laserDriftVelocityWest	 =   5.57234; // +/- 2.37281e-05 cm/us All: West = 0.393306 +/- 0.00424194
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57234 +/- 2.37281e-05
  return (TDataSet *)tableSet;// West = 5.57234 +/- 2.37282e-05 East = 5.56975 +/- 0.00702005
};
