TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 120083
  row.laserDriftVelocityEast	 =   5.5797; // +/- 1.9054e-05 cm/us All: East = -1.04459 +/- 0.00472366
  row.laserDriftVelocityWest	 =   5.5797; // +/- 1.9054e-05 cm/us All: West = -0.794376 +/- 0.00501977
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5797 +/- 1.9054e-05
  return (TDataSet *)tableSet;// West = 5.57895 +/- 2.7549e-05 East = 5.58038 +/- 2.63817e-05
};
