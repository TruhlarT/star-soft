TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 146028
  row.laserDriftVelocityEast	 =   5.57412; // +/- 1.60725e-05 cm/us All: East = 0.117168 +/- 1.41421
  row.laserDriftVelocityWest	 =   5.57412; // +/- 1.60725e-05 cm/us All: West = 0.0785338 +/- 0.00285819
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57412 +/- 1.60725e-05
  return (TDataSet *)tableSet;// West = 5.57412 +/- 1.60725e-05 East = 4.45896 +/- 1.41421
};
