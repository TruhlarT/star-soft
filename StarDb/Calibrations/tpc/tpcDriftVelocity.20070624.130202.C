TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 175023
  row.laserDriftVelocityEast	 =   5.57187; // +/- 2.24875e-05 cm/us All: East = 0.609075 +/- 0.00540746
  row.laserDriftVelocityWest	 =   5.57187; // +/- 2.24875e-05 cm/us All: West = 0.305529 +/- 0.00618134
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57187 +/- 2.24875e-05
  return (TDataSet *)tableSet;// West = 5.57282 +/- 3.39438e-05 East = 5.57112 +/- 3.00207e-05
};
