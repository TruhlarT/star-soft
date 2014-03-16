TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 32021
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.49928; // +/- 3.01434e-05 cm/us All: East = 0.106526 +/- 0.0552499
  row.laserDriftVelocityWest	 =   5.49928; // +/- 3.01434e-05 cm/us All: West = 0.441364 +/- 0.00570395
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.49928 +/- 3.01434e-05
  return (TDataSet *)tableSet;// West = 5.49922 +/- 3.07971e-05 East = 5.50056 +/- 0.000147077
};
