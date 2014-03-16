TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 54031
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51092; // +/- 3.4633e-05 cm/us All: East = 0.260558 +/- 0.0128112
  row.laserDriftVelocityWest	 =   5.51092; // +/- 3.4633e-05 cm/us All: West = -0.220954 +/- 0.00835153
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.51092 +/- 3.4633e-05
  return (TDataSet *)tableSet;// West = 5.51162 +/- 4.11383e-05 East = 5.5092 +/- 6.41726e-05
};
