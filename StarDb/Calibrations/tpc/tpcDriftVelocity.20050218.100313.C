TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6049035
  row.laserDriftVelocityEast	 =   5.52971; // +/- 4.52805e-05 cm/us All: East = 5.52958 +/- 9.27201e-05
  row.laserDriftVelocityWest	 =   5.52971; // +/- 4.52805e-05 cm/us All: West = 5.52975 +/- 5.18889e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.18346 +/- 0.00818439
  return (TDataSet *)tableSet;// West = 1.17797 +/- 0.00934493 East = 1.20156 +/- 0.0169571
};
