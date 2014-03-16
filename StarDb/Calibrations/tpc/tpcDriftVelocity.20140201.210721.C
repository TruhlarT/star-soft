TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 32049
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5006; // +/- 2.78722e-05 cm/us All: East = -0.0665418 +/- 0.0163008
  row.laserDriftVelocityWest	 =   5.5006; // +/- 2.78722e-05 cm/us All: West = 0.251671 +/- 0.00540062
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5006 +/- 2.78722e-05
  return (TDataSet *)tableSet;// West = 5.5004 +/- 2.98361e-05 East = 5.50193 +/- 7.81135e-05
};
