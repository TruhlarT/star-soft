TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 91098
  row.laserDriftVelocityEast	 =   5.58326; // +/- 1.70257e-05 cm/us All: East = -2.99242 +/- 0.00509772
  row.laserDriftVelocityWest	 =   5.58326; // +/- 1.70257e-05 cm/us All: West = -2.7989 +/- 0.00383308
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.58326 +/- 1.70257e-05
  return (TDataSet *)tableSet;// West = 5.58285 +/- 2.1507e-05 East = 5.58395 +/- 2.78656e-05
};
