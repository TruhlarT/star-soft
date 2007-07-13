TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 146015
  row.laserDriftVelocityEast	 =   5.57429; // +/- 1.60998e-05 cm/us All: East = 0.237961 +/- 1.41421
  row.laserDriftVelocityWest	 =   5.57429; // +/- 1.60998e-05 cm/us All: West = 0.0396393 +/- 0.00288113
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57429 +/- 1.60998e-05
  return (TDataSet *)tableSet;// West = 5.57429 +/- 1.60998e-05 East = 11.1478 +/- 1.41421
};
