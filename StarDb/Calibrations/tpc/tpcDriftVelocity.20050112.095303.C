TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6012016
  row.laserDriftVelocityEast	 =   5.5132; // +/- 5.7535e-05 cm/us All: East = 5.51328 +/- 0.00010068
  row.laserDriftVelocityWest	 =   5.5132; // +/- 5.7535e-05 cm/us All: West = 5.51317 +/- 7.01111e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = -0.537412 +/- 0.0105353
  return (TDataSet *)tableSet;// West = -0.531809 +/- 0.0128899 East = -0.548685 +/- 0.0182849
};
