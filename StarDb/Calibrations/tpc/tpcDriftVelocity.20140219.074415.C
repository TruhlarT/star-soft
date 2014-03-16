TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 50002
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50279; // +/- 2.61186e-05 cm/us All: East = 0.23164 +/- 0.00932371
  row.laserDriftVelocityWest	 =   5.50279; // +/- 2.61186e-05 cm/us All: West = -0.144296 +/- 0.00545647
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.50279 +/- 2.61186e-05
  return (TDataSet *)tableSet;// West = 5.50315 +/- 2.9654e-05 East = 5.50151 +/- 5.51568e-05
};
