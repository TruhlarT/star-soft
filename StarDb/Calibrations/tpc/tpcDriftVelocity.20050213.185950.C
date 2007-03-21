TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6044052
  row.laserDriftVelocityEast	 =   5.52902; // +/- 9.41547e-05 cm/us All: East = 5.52765 +/- 0.000316058
  row.laserDriftVelocityWest	 =   5.52902; // +/- 9.41547e-05 cm/us All: West = 5.52915 +/- 9.8633e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.877988 +/- 0.018388
  return (TDataSet *)tableSet;// West = 0.853009 +/- 0.0192338 East = 1.14342 +/- 0.0626983
};
