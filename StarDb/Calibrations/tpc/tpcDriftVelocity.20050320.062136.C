TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6079006
  row.laserDriftVelocityEast	 =   5.52902; // +/- 5.0743e-05 cm/us All: East = 5.52924 +/- 8.01372e-05
  row.laserDriftVelocityWest	 =   5.52902; // +/- 5.0743e-05 cm/us All: West = 5.52887 +/- 6.55605e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.596032 +/- 0.00911503
  return (TDataSet *)tableSet;// West = 0.639295 +/- 0.0119665 East = 0.536237 +/- 0.0140683
};
