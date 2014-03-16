TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 68047
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5189; // +/- 2.79663e-05 cm/us All: East = -0.673848 +/- 0.0592806
  row.laserDriftVelocityWest	 =   5.5189; // +/- 2.79663e-05 cm/us All: West = -0.953438 +/- 0.00543685
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5189 +/- 2.79663e-05
  return (TDataSet *)tableSet;// West = 5.51895 +/- 2.83243e-05 East = 5.51697 +/- 0.000176445
};
