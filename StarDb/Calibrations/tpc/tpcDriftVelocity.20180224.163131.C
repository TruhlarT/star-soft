TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 55025
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.53401; // +/- 2.91023e-05 cm/us All: East = 1.10445 +/- 0.0191721
  row.laserDriftVelocityWest	 =   5.53401; // +/- 2.91023e-05 cm/us All: West = 1.46677 +/- 0.00650637
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.53401 +/- 2.91023e-05
  return (TDataSet *)tableSet;// West = 5.53369 +/- 3.29136e-05 East = 5.53513 +/- 6.23032e-05
};
