TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6065019
  row.laserDriftVelocityEast	 =   5.53557; // +/- 3.28866e-05 cm/us All: East = 5.53551 +/- 6.39178e-05
  row.laserDriftVelocityWest	 =   5.53557; // +/- 3.28866e-05 cm/us All: West = 5.53559 +/- 3.83525e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.11423 +/- 0.00602065
  return (TDataSet *)tableSet;// West = 1.11176 +/- 0.00704032 East = 1.12097 +/- 0.011615
};
