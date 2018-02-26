TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 56001
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.53437; // +/- 1.69418e-05 cm/us All: East = 1.04485 +/- 0.00670459
  row.laserDriftVelocityWest	 =   5.53437; // +/- 1.69418e-05 cm/us All: West = 1.47413 +/- 0.00361985
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.53437 +/- 1.69418e-05
  return (TDataSet *)tableSet;// West = 5.53377 +/- 1.98752e-05 East = 5.53597 +/- 3.24014e-05
};
