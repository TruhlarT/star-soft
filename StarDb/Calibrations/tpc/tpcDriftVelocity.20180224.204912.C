TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 55042
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.53302; // +/- 1.89786e-05 cm/us All: East = 1.24462 +/- 0.00798096
  row.laserDriftVelocityWest	 =   5.53302; // +/- 1.89786e-05 cm/us All: West = 1.6851 +/- 0.00414374
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.53302 +/- 1.89786e-05
  return (TDataSet *)tableSet;// West = 5.53248 +/- 2.15038e-05 East = 5.5349 +/- 4.03651e-05
};
