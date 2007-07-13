TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 169028
  row.laserDriftVelocityEast	 =   5.5704; // +/- 2.18591e-05 cm/us All: East = 0.886402 +/- 0.00469693
  row.laserDriftVelocityWest	 =   5.5704; // +/- 2.18591e-05 cm/us All: West = 0.379603 +/- 0.00737063
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5704 +/- 2.18591e-05
  return (TDataSet *)tableSet;// West = 5.57243 +/- 4.08573e-05 East = 5.56958 +/- 2.58735e-05
};
