TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6026019
  row.laserDriftVelocityEast	 =   5.55327; // +/- 3.83776e-05 cm/us All: East = 5.55257 +/- 7.90188e-05
  row.laserDriftVelocityWest	 =   5.55327; // +/- 3.83776e-05 cm/us All: West = 5.55349 +/- 4.39033e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.85814 +/- 0.00701126
  return (TDataSet *)tableSet;// West = 1.81622 +/- 0.00804201 East = 1.99094 +/- 0.0143142
};
