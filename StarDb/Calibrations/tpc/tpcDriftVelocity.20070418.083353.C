TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 108016
  row.laserDriftVelocityEast	 =   5.57569; // +/- 1.50674e-05 cm/us All: East = -0.101367 +/- 0.00351445
  row.laserDriftVelocityWest	 =   5.57569; // +/- 1.50674e-05 cm/us All: West = -0.363824 +/- 0.0042023
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57569 +/- 1.50674e-05
  return (TDataSet *)tableSet;// West = 5.57656 +/- 2.35317e-05 East = 5.5751 +/- 1.96159e-05
};
