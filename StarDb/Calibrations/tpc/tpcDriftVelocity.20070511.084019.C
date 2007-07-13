TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 131023
  row.laserDriftVelocityEast	 =   5.56068; // +/- 2.79219e-05 cm/us All: East = 2.52898 +/- 0.0058038
  row.laserDriftVelocityWest	 =   5.56068; // +/- 2.79219e-05 cm/us All: West = 2.37489 +/- 0.010182
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.56068 +/- 2.79219e-05
  return (TDataSet *)tableSet;// West = 5.56132 +/- 5.5626e-05 East = 5.56046 +/- 3.22837e-05
};
