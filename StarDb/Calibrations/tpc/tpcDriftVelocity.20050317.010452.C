TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6075129
  row.laserDriftVelocityEast	 =   5.52944; // +/- 8.4587e-05 cm/us All: East = 5.52937 +/- 0.000129447
  row.laserDriftVelocityWest	 =   5.52944; // +/- 8.4587e-05 cm/us All: West = 5.5295 +/- 0.000111744
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.584363 +/- 0.0151635
  return (TDataSet *)tableSet;// West = 0.588934 +/- 0.0201475 East = 0.578392 +/- 0.0230292
};
