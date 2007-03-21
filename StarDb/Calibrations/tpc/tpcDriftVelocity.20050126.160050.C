TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6026062
  row.laserDriftVelocityEast	 =   5.55436; // +/- 0.000112118 cm/us All: East = 5.55627 +/- 0.000208371
  row.laserDriftVelocityWest	 =   5.55436; // +/- 0.000112118 cm/us All: West = 5.55358 +/- 0.000133014
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = -15.861 +/- 0.0202731
  return (TDataSet *)tableSet;// West = -15.7321 +/- 0.0239641 East = -16.1856 +/- 0.0380205
};
