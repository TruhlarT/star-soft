TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 66082
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51963; // +/- 2.64436e-05 cm/us All: East = -0.989865 +/- 0.0115029
  row.laserDriftVelocityWest	 =   5.51963; // +/- 2.64436e-05 cm/us All: West = -1.08385 +/- 0.00568418
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.51963 +/- 2.64436e-05
  return (TDataSet *)tableSet;// West = 5.5197 +/- 2.9921e-05 East = 5.51936 +/- 5.65159e-05
};
