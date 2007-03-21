TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6036015
  row.laserDriftVelocityEast	 =   5.53788; // +/- 4.18971e-05 cm/us All: East = 5.53782 +/- 9.3177e-05
  row.laserDriftVelocityWest	 =   5.53788; // +/- 4.18971e-05 cm/us All: West = 5.5379 +/- 4.69064e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 2.13114 +/- 0.00784189
  return (TDataSet *)tableSet;// West = 2.125 +/- 0.00876245 East = 2.15583 +/- 0.0175755
};
