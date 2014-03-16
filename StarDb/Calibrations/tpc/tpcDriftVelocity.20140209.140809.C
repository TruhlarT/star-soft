TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 40021
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50634; // +/- 3.72884e-05 cm/us All: East = 0.130956 +/- 0.0101838
  row.laserDriftVelocityWest	 =   5.50634; // +/- 3.72884e-05 cm/us All: West = 1.22923 +/- 0.0115911
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.50634 +/- 3.72884e-05
  return (TDataSet *)tableSet;// West = 5.50336 +/- 5.64635e-05 East = 5.50865 +/- 4.96573e-05
};
