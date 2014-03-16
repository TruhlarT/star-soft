TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 51016
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50404; // +/- 3.2373e-05 cm/us All: East = 0.279633 +/- 0.0150765
  row.laserDriftVelocityWest	 =   5.50404; // +/- 3.2373e-05 cm/us All: West = -0.219965 +/- 0.00683224
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.50404 +/- 3.2373e-05
  return (TDataSet *)tableSet;// West = 5.50449 +/- 3.51958e-05 East = 5.50157 +/- 8.25019e-05
};
