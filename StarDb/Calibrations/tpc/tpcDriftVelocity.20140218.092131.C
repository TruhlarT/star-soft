TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 49015
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5021; // +/- 2.31457e-05 cm/us All: East = 0.23632 +/- 0.00909948
  row.laserDriftVelocityWest	 =   5.5021; // +/- 2.31457e-05 cm/us All: West = 0.247824 +/- 0.00490581
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5021 +/- 2.31457e-05
  return (TDataSet *)tableSet;// West = 5.50189 +/- 2.60809e-05 East = 5.50289 +/- 5.02198e-05
};
