TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 154036
  row.laserDriftVelocityEast	 =   5.57308; // +/- 2.66748e-05 cm/us All: East = -0.585317 +/- 1.84272
  row.laserDriftVelocityWest	 =   5.57308; // +/- 2.66748e-05 cm/us All: West = 0.256554 +/- 0.0048096
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57308 +/- 2.66748e-05
  return (TDataSet *)tableSet;// West = 5.57308 +/- 2.66749e-05 East = 5.57788 +/- 0.0168651
};
