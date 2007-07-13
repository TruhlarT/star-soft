TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 172055
  row.laserDriftVelocityEast	 =   5.57049; // +/- 3.08359e-05 cm/us All: East = 0.986567 +/- 0.00858259
  row.laserDriftVelocityWest	 =   5.57049; // +/- 3.08359e-05 cm/us All: West = 0.54251 +/- 0.00713261
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57049 +/- 3.08359e-05
  return (TDataSet *)tableSet;// West = 5.57151 +/- 4.00782e-05 East = 5.56902 +/- 4.82736e-05
};
