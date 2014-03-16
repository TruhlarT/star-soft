TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 69051
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51984; // +/- 2.74877e-05 cm/us All: East = -0.783389 +/- 0.0125707
  row.laserDriftVelocityWest	 =   5.51984; // +/- 2.74877e-05 cm/us All: West = -1.17985 +/- 0.00589849
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.51984 +/- 2.74877e-05
  return (TDataSet *)tableSet;// West = 5.52016 +/- 3.02336e-05 East = 5.51829 +/- 6.60111e-05
};
