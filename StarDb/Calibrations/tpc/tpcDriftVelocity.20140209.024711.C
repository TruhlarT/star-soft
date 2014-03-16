TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 39197
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50896; // +/- 3.82002e-05 cm/us All: East = 0.0640987 +/- 0.0110509
  row.laserDriftVelocityWest	 =   5.50896; // +/- 3.82002e-05 cm/us All: West = 0.812691 +/- 0.00671606
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.50896 +/- 3.82002e-05
  return (TDataSet *)tableSet;// West = 5.50827 +/- 5.8134e-05 East = 5.50948 +/- 5.0677e-05
};
