TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6047024
  row.laserDriftVelocityEast	 =   5.52791; // +/- 3.53856e-05 cm/us All: East = 5.52759 +/- 0.000246293
  row.laserDriftVelocityWest	 =   5.52791; // +/- 3.53856e-05 cm/us All: West = 5.52792 +/- 3.57566e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.910201 +/- 0.00641004
  return (TDataSet *)tableSet;// West = 0.909125 +/- 0.00648251 East = 0.957512 +/- 0.0429865
};
