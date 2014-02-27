TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 55009
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.89767; // +/- 0.000110554 cm/us All: East = 5.90087 +/- 0.000542103
  row.laserDriftVelocityWest	 =   5.89767; // +/- 0.000110554 cm/us All: West = 5.90087 +/- 0.000542103
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.89767 +/- 0.000110554
  return (TDataSet *)tableSet;// West = 5.89753 +/- 0.000112928 East = 5.90087 +/- 0.000542103
};
