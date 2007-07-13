TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 131009
  row.laserDriftVelocityEast	 =   5.55975; // +/- 1.76206e-05 cm/us All: East = 2.63771 +/- 0.00388927
  row.laserDriftVelocityWest	 =   5.55975; // +/- 1.76206e-05 cm/us All: West = 2.70147 +/- 0.00555801
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.55975 +/- 1.76206e-05
  return (TDataSet *)tableSet;// West = 5.55949 +/- 3.06253e-05 East = 5.55987 +/- 2.15438e-05
};
