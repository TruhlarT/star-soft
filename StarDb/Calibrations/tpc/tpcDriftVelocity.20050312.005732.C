TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6070082
  row.laserDriftVelocityEast	 =   5.53184; // +/- 0.000635059 cm/us All: East = 5.53192 +/- 0.00145482
  row.laserDriftVelocityWest	 =   5.53184; // +/- 0.000635059 cm/us All: West = 5.53183 +/- 0.000705861
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.371665 +/- 0.108207
  return (TDataSet *)tableSet;// West = 0.356409 +/- 0.118945 East = 0.444898 +/- 0.260605
};
