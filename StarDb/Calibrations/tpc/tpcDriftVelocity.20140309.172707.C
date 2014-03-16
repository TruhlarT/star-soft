TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 68027
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51806; // +/- 2.56788e-05 cm/us All: East = -0.498872 +/- 0.0111131
  row.laserDriftVelocityWest	 =   5.51806; // +/- 2.56788e-05 cm/us All: West = -0.865783 +/- 0.00547495
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.51806 +/- 2.56788e-05
  return (TDataSet *)tableSet;// West = 5.51845 +/- 2.87828e-05 East = 5.51655 +/- 5.6847e-05
};
