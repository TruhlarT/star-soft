TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 65012
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.5156; // +/- 4.06902e-05 cm/us All: East = -0.411202 +/- 0.00689045
  row.laserDriftVelocityWest	 =   5.5156; // +/- 4.06902e-05 cm/us All: West = 0.13147 +/- 0.0801196
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5156 +/- 4.06902e-05
  return (TDataSet *)tableSet;// West = 5.51254 +/- 0.000120513 East = 5.516 +/- 4.32288e-05
};
