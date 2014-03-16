TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 37074
  memset(&row, 0, tableSet->GetRowSize());
  row.laserDriftVelocityEast	 =   5.50838; // +/- 2.96915e-05 cm/us All: East = 0.186751 +/- 0.00645391
  row.laserDriftVelocityWest	 =   5.50838; // +/- 2.96915e-05 cm/us All: West = -0.192005 +/- 0.0102628
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.50838 +/- 2.96915e-05
  return (TDataSet *)tableSet;// West = 5.50988 +/- 5.5003e-05 East = 5.50777 +/- 3.52722e-05
};
