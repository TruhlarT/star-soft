TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 96032
  row.laserDriftVelocityEast	 =   5.57709; // +/- 1.49396e-05 cm/us All: East = -1.87206 +/- 0.00362266
  row.laserDriftVelocityWest	 =   5.57709; // +/- 1.49396e-05 cm/us All: West = -1.64883 +/- 0.0039767
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57709 +/- 1.49396e-05
  return (TDataSet *)tableSet;// West = 5.57644 +/- 2.18078e-05 East = 5.57765 +/- 2.05077e-05
};
