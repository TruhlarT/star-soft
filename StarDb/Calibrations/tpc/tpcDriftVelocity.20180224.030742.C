TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 54086
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5364; // +/- 1.74724e-05 cm/us All: East = 0.773494 +/- 0.00686665
  row.laserDriftVelocityWest	 =   5.5364; // +/- 1.74724e-05 cm/us All: West = 1.06284 +/- 0.00379673
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5364 +/- 1.74724e-05
  return (TDataSet *)tableSet;// West = 5.53608 +/- 2.03926e-05 East = 5.53729 +/- 3.38839e-05
};
