TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 113119
  row.laserDriftVelocityEast	 =   5.57737; // +/- 1.94515e-05 cm/us All: East = -0.515005 +/- 0.00481568
  row.laserDriftVelocityWest	 =   5.57737; // +/- 1.94515e-05 cm/us All: West = -0.498748 +/- 0.00499343
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57737 +/- 1.94515e-05
  return (TDataSet *)tableSet;// West = 5.5773 +/- 2.7774e-05 East = 5.57742 +/- 2.72506e-05
};
