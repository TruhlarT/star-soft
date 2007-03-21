TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6014101
  row.laserDriftVelocityEast	 =   5.53022; // +/- 2.61807e-05 cm/us All: East = 5.52994 +/- 5.24515e-05
  row.laserDriftVelocityWest	 =   5.53022; // +/- 2.61807e-05 cm/us All: West = 5.53032 +/- 3.02136e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.788714 +/- 0.00689132
  return (TDataSet *)tableSet;// West = 0.76022 +/- 0.00849717 East = 0.843473 +/- 0.0117795
};
