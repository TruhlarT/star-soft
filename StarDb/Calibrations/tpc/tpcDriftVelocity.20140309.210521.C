TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 68035
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5186; // +/- 3.02635e-05 cm/us All: East = -0.756303 +/- 0.0214138
  row.laserDriftVelocityWest	 =   5.5186; // +/- 3.02635e-05 cm/us All: West = -0.831687 +/- 0.00589633
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5186 +/- 3.02635e-05
  return (TDataSet *)tableSet;// West = 5.51837 +/- 3.09012e-05 East = 5.52419 +/- 0.000149738
};
