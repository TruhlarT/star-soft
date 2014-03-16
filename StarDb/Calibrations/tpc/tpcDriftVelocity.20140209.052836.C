TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 40002
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50682; // +/- 3.96146e-05 cm/us All: East = 0.232714 +/- 0.0118837
  row.laserDriftVelocityWest	 =   5.50682; // +/- 3.96146e-05 cm/us All: West = 0.696436 +/- 0.0119046
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.50682 +/- 3.96146e-05
  return (TDataSet *)tableSet;// West = 5.50527 +/- 5.9023e-05 East = 5.50808 +/- 5.34394e-05
};
