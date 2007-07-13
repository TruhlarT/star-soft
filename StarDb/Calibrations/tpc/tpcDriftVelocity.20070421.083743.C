TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 111029
  row.laserDriftVelocityEast	 =   5.57466; // +/- 1.77274e-05 cm/us All: East = -0.0112701 +/- 0.00437897
  row.laserDriftVelocityWest	 =   5.57466; // +/- 1.77274e-05 cm/us All: West = -0.0467353 +/- 0.00464129
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57466 +/- 1.77274e-05
  return (TDataSet *)tableSet;// West = 5.57478 +/- 2.59726e-05 East = 5.57456 +/- 2.42559e-05
};
