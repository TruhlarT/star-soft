TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 113078
  row.laserDriftVelocityEast	 =   5.57735; // +/- 2.03809e-05 cm/us All: East = -0.628996 +/- 0.00515894
  row.laserDriftVelocityWest	 =   5.57735; // +/- 2.03809e-05 cm/us All: West = -0.379415 +/- 0.0051599
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57735 +/- 2.03809e-05
  return (TDataSet *)tableSet;// West = 5.57665 +/- 2.88447e-05 East = 5.57805 +/- 2.88011e-05
};
