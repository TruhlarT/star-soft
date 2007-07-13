TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 98006
  row.laserDriftVelocityEast	 =   5.57453; // +/- 3.86271e-05 cm/us All: East = -1.3158 +/- 0.00683167
  row.laserDriftVelocityWest	 =   5.57453; // +/- 3.86271e-05 cm/us All: West = 0 +/- 0
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57453 +/- 3.86271e-05
  return (TDataSet *)tableSet;// West = 0 +/- 0 East = 5.57453 +/- 3.86271e-05
};
