TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6022047
  row.laserDriftVelocityEast	 =   5.55532; // +/- 7.79514e-05 cm/us All: East = 5.55555 +/- 0.000135559
  row.laserDriftVelocityWest	 =   5.55532; // +/- 7.79514e-05 cm/us All: West = 5.55521 +/- 9.52801e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.30247 +/- 0.0137592
  return (TDataSet *)tableSet;// West = 1.3373 +/- 0.0164632 East = 1.22179 +/- 0.0250578
};
