TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 104053
  row.laserDriftVelocityEast	 =   5.58068; // +/- 1.40929e-05 cm/us All: East = -1.04536 +/- 0.00324309
  row.laserDriftVelocityWest	 =   5.58068; // +/- 1.40929e-05 cm/us All: West = -1.18975 +/- 0.00405029
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.58068 +/- 1.40929e-05
  return (TDataSet *)tableSet;// West = 5.58117 +/- 2.26003e-05 East = 5.58037 +/- 1.8027e-05
};
