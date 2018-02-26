TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 54028
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.53782; // +/- 9.78536e-05 cm/us All: East = -999 +/- 999
  row.laserDriftVelocityWest	 =   5.53782; // +/- 9.78536e-05 cm/us All: West = 0.708153 +/- 0.0667806
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.53782 +/- 9.78536e-05
  return (TDataSet *)tableSet;// West = 5.53782 +/- 9.78536e-05 East = -999 +/- 999
};
