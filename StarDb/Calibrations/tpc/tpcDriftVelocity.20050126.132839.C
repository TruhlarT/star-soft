TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6026047
  row.laserDriftVelocityEast	 =   5.55412; // +/- 0.000158417 cm/us All: East = 5.55412 +/- 0.000158417
  row.laserDriftVelocityWest	 =   5.55412; // +/- 0.000158417 cm/us All: West = 1.70867 +/- 1.41421
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 2.08144 +/- 0.0302279
  return (TDataSet *)tableSet;// West = 0.660283 +/- 1.41421 East = 2.08144 +/- 0.0302279
};
