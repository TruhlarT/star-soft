TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6064055
  row.laserDriftVelocityEast	 =   5.53589; // +/- 5.74952e-05 cm/us All: East = 5.53576 +/- 0.000114166
  row.laserDriftVelocityWest	 =   5.53589; // +/- 5.74952e-05 cm/us All: West = 5.53594 +/- 6.65507e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.936674 +/- 0.0103518
  return (TDataSet *)tableSet;// West = 0.923061 +/- 0.0120875 East = 0.974126 +/- 0.0200498
};
