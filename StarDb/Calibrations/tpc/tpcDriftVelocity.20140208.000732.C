TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 38073
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50966; // +/- 4.29308e-05 cm/us All: East = 0.0705383 +/- 0.0170696
  row.laserDriftVelocityWest	 =   5.50966; // +/- 4.29308e-05 cm/us All: West = 0.74588 +/- 0.0101143
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.50966 +/- 4.29308e-05
  return (TDataSet *)tableSet;// West = 5.50885 +/- 4.96544e-05 East = 5.51208 +/- 8.54388e-05
};
