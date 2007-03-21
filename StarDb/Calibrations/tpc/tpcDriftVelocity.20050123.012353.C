TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6022091
  row.laserDriftVelocityEast	 =   5.55527; // +/- 6.73117e-05 cm/us All: East = 5.55549 +/- 0.000119244
  row.laserDriftVelocityWest	 =   5.55527; // +/- 6.73117e-05 cm/us All: West = 5.55517 +/- 8.15462e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.0624 +/- 0.0181903
  return (TDataSet *)tableSet;// West = 1.05536 +/- 0.0230876 East = 1.07394 +/- 0.0295381
};
