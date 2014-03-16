TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 39118
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50469; // +/- 4.52536e-05 cm/us All: East = 0.172836 +/- 0.0224893
  row.laserDriftVelocityWest	 =   5.50469; // +/- 4.52536e-05 cm/us All: West = -0.73882 +/- 0.0105186
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.50469 +/- 4.52536e-05
  return (TDataSet *)tableSet;// West = 5.50407 +/- 5.12918e-05 East = 5.50687 +/- 9.61352e-05
};
