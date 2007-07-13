TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 171010
  row.laserDriftVelocityEast	 =   5.56931; // +/- 1.73281e-05 cm/us All: East = 1.02661 +/- 0.00371177
  row.laserDriftVelocityWest	 =   5.56931; // +/- 1.73281e-05 cm/us All: West = 0.721228 +/- 0.00566076
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.56931 +/- 1.73281e-05
  return (TDataSet *)tableSet;// West = 5.5705 +/- 3.17246e-05 East = 5.5688 +/- 2.06866e-05
};
