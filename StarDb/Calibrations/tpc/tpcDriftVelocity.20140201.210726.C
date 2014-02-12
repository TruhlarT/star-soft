TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 32049
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50237; // +/- 0.000576187 cm/us All: East = 0.561629 +/- 2.8876
  row.laserDriftVelocityWest	 =   5.50237; // +/- 0.000576187 cm/us All: West = 0.793519 +/- 0.933577
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.50237 +/- 0.000576187
  return (TDataSet *)tableSet;// West = 5.50241 +/- 0.000582152 East = 5.49998 +/- 0.00403547
};
