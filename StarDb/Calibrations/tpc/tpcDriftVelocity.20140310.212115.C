TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 69039
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.52012; // +/- 2.91919e-05 cm/us All: East = -0.901363 +/- 0.486016
  row.laserDriftVelocityWest	 =   5.52012; // +/- 2.91919e-05 cm/us All: West = -1.16188 +/- 0.00564782
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.52012 +/- 2.91919e-05
  return (TDataSet *)tableSet;// West = 5.52012 +/- 2.92737e-05 East = 5.51895 +/- 0.000390795
};
