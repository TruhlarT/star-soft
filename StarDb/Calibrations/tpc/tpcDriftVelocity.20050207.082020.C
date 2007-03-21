TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6038010
  row.laserDriftVelocityEast	 =   5.53304; // +/- 4.07915e-05 cm/us All: East = 5.5329 +/- 9.47911e-05
  row.laserDriftVelocityWest	 =   5.53304; // +/- 4.07915e-05 cm/us All: West = 5.53307 +/- 4.51898e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 2.41668 +/- 0.00739556
  return (TDataSet *)tableSet;// West = 2.41083 +/- 0.00818003 East = 2.44288 +/- 0.0173068
};
