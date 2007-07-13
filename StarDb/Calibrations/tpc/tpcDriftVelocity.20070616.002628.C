TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 166085
  row.laserDriftVelocityEast	 =   5.57199; // +/- 7.25162e-05 cm/us All: East = -17.464 +/- 0.0223773
  row.laserDriftVelocityWest	 =   5.57199; // +/- 7.25162e-05 cm/us All: West = -17.3523 +/- 0.0156728
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57199 +/- 7.25162e-05
  return (TDataSet *)tableSet;// West = 5.5718 +/- 8.74262e-05 East = 5.57242 +/- 0.000129824
};
