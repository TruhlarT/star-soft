TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 38006
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5082; // +/- 3.96363e-05 cm/us All: East = 0.249443 +/- 0.0109478
  row.laserDriftVelocityWest	 =   5.5082; // +/- 3.96363e-05 cm/us All: West = -0.300504 +/- 0.0101698
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5082 +/- 3.96363e-05
  return (TDataSet *)tableSet;// West = 5.50979 +/- 5.39145e-05 East = 5.50633 +/- 5.84708e-05
};
