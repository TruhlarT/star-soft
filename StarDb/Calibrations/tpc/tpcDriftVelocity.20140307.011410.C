TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 65056
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51913; // +/- 2.36877e-05 cm/us All: East = -0.722686 +/- 0.0118453
  row.laserDriftVelocityWest	 =   5.51913; // +/- 2.36877e-05 cm/us All: West = -1.07354 +/- 0.00499644
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.51913 +/- 2.36877e-05
  return (TDataSet *)tableSet;// West = 5.51943 +/- 2.66216e-05 East = 5.51797 +/- 5.19047e-05
};
