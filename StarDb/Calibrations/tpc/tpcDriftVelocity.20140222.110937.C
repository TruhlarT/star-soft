TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 53015
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50609; // +/- 3.08211e-05 cm/us All: East = 0.204365 +/- 0.0138566
  row.laserDriftVelocityWest	 =   5.50609; // +/- 3.08211e-05 cm/us All: West = -0.154207 +/- 0.006537
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.50609 +/- 3.08211e-05
  return (TDataSet *)tableSet;// West = 5.50651 +/- 3.42827e-05 East = 5.50432 +/- 7.0386e-05
};
