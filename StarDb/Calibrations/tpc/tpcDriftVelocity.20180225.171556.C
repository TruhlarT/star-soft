TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 56035
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.54134; // +/- 1.26201e-05 cm/us All: East = -0.138696 +/- 0.00412591
  row.laserDriftVelocityWest	 =   5.54134; // +/- 1.26201e-05 cm/us All: West = 0.254324 +/- 0.00289683
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.54134 +/- 1.26201e-05
  return (TDataSet *)tableSet;// West = 5.54055 +/- 1.56984e-05 East = 5.5428 +/- 2.12192e-05
};
