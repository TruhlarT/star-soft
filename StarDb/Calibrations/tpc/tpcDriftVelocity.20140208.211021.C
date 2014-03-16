TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 39177
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50559; // +/- 4.58685e-05 cm/us All: East = 0.0472181 +/- 0.0178807
  row.laserDriftVelocityWest	 =   5.50559; // +/- 4.58685e-05 cm/us All: West = 0.431577 +/- 0.0113985
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.50559 +/- 4.58685e-05
  return (TDataSet *)tableSet;// West = 5.50518 +/- 5.44598e-05 East = 5.50659 +/- 8.5084e-05
};
