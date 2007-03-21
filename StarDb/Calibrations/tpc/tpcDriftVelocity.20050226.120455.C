TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6057044
  row.laserDriftVelocityEast	 =   5.53361; // +/- 0.000428631 cm/us All: East = 2.30583 +/- 1.41421
  row.laserDriftVelocityWest	 =   5.53361; // +/- 0.000428631 cm/us All: West = 5.53361 +/- 0.000428631
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.35228 +/- 0.0830498
  return (TDataSet *)tableSet;// West = 1.35228 +/- 0.0830498 East = 0.541502 +/- 1.41421
};
