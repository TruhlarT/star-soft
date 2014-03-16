TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 60045
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.51454; // +/- 3.67168e-05 cm/us All: East = 0.564527 +/- 0.0402144
  row.laserDriftVelocityWest	 =   5.51454; // +/- 3.67168e-05 cm/us All: West = -0.394786 +/- 0.00850287
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.51454 +/- 3.67168e-05
  return (TDataSet *)tableSet;// West = 5.51573 +/- 4.26089e-05 East = 5.51112 +/- 7.23645e-05
};
