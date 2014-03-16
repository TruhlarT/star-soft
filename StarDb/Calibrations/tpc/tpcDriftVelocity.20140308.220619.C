TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 67037
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51591; // +/- 2.32681e-05 cm/us All: East = 0.13897 +/- 0.0113191
  row.laserDriftVelocityWest	 =   5.51591; // +/- 2.32681e-05 cm/us All: West = -0.503216 +/- 0.00479398
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.51591 +/- 2.32681e-05
  return (TDataSet *)tableSet;// West = 5.51646 +/- 2.55244e-05 East = 5.51319 +/- 5.6604e-05
};
