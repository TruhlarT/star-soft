TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 96119
  row.laserDriftVelocityEast	 =   5.57644; // +/- 1.82689e-05 cm/us All: East = -1.78137 +/- 0.0060249
  row.laserDriftVelocityWest	 =   5.57644; // +/- 1.82689e-05 cm/us All: West = -1.59425 +/- 0.00400085
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57644 +/- 1.82689e-05
  return (TDataSet *)tableSet;// West = 5.57612 +/- 2.18258e-05 East = 5.57719 +/- 3.33892e-05
};
