TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 138070
  row.laserDriftVelocityEast	 =   5.57453; // +/- 2.08705e-05 cm/us All: East = -0.0462753 +/- 0.00464831
  row.laserDriftVelocityWest	 =   5.57453; // +/- 2.08705e-05 cm/us All: West = 0.0794402 +/- 0.0061662
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57453 +/- 2.08705e-05
  return (TDataSet *)tableSet;// West = 5.57408 +/- 3.47485e-05 East = 5.57478 +/- 2.61032e-05
};
