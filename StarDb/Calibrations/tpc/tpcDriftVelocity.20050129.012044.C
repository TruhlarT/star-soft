TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6028079
  row.laserDriftVelocityEast	 =   5.55317; // +/- 0.000129579 cm/us All: East = 5.55345 +/- 0.0039037
  row.laserDriftVelocityWest	 =   5.55317; // +/- 0.000129579 cm/us All: West = 5.55317 +/- 0.000129651
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 2.86424 +/- 0.0234571
  return (TDataSet *)tableSet;// West = 2.86429 +/- 0.0234701 East = 2.81627 +/- 0.705331
};
