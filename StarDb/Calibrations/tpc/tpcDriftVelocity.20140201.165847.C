TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 32031
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50118; // +/- 3.01069e-05 cm/us All: East = 0.22657 +/- 0.0137002
  row.laserDriftVelocityWest	 =   5.50118; // +/- 3.01069e-05 cm/us All: West = 0.173381 +/- 0.00624069
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.50118 +/- 3.01069e-05
  return (TDataSet *)tableSet;// West = 5.50124 +/- 3.3703e-05 East = 5.50094 +/- 6.69842e-05
};
