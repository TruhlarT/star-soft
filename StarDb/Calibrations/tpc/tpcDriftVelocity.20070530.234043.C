TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 150055
  row.laserDriftVelocityEast	 =   5.57298; // +/- 2.20843e-05 cm/us All: East = 0 +/- 0
  row.laserDriftVelocityWest	 =   5.57298; // +/- 2.20843e-05 cm/us All: West = 0.277283 +/- 0.00397437
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57298 +/- 2.20843e-05
  return (TDataSet *)tableSet;// West = 5.57298 +/- 2.20843e-05 East = 0 +/- 0
};
