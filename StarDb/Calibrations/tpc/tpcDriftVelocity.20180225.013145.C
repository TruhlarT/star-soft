TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 55055
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.53241; // +/- 1.72029e-05 cm/us All: East = 1.35539 +/- 0.00708153
  row.laserDriftVelocityWest	 =   5.53241; // +/- 1.72029e-05 cm/us All: West = 1.84097 +/- 0.00381088
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.53241 +/- 1.72029e-05
  return (TDataSet *)tableSet;// West = 5.53175 +/- 2.01639e-05 East = 5.53417 +/- 3.29771e-05
};
