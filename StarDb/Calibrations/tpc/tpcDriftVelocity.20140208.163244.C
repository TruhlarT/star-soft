TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 39166
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50576; // +/- 4.69538e-05 cm/us All: East = 0.170778 +/- 0.0213623
  row.laserDriftVelocityWest	 =   5.50576; // +/- 4.69538e-05 cm/us All: West = 0.419772 +/- 0.0116838
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.50576 +/- 4.69538e-05
  return (TDataSet *)tableSet;// West = 5.50549 +/- 5.50587e-05 East = 5.50649 +/- 8.99072e-05
};
