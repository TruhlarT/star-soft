TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 47098
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.49665; // +/- 4.56089e-05 cm/us All: East = 0.359528 +/- 0.0116019
  row.laserDriftVelocityWest	 =   5.49665; // +/- 4.56089e-05 cm/us All: West = 0.518285 +/- 0.0328584
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.49665 +/- 4.56089e-05
  return (TDataSet *)tableSet;// West = 5.49619 +/- 9.14346e-05 East = 5.4968 +/- 5.26231e-05
};
