TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 68041
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51877; // +/- 2.85923e-05 cm/us All: East = -0.567376 +/- 0.0679731
  row.laserDriftVelocityWest	 =   5.51877; // +/- 2.85923e-05 cm/us All: West = -0.915816 +/- 0.00548773
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.51877 +/- 2.85923e-05
  return (TDataSet *)tableSet;// West = 5.51882 +/- 2.88961e-05 East = 5.51643 +/- 0.000197712
};
