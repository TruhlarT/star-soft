TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 155011
  row.laserDriftVelocityEast	 =   5.57319; // +/- 2.45558e-05 cm/us All: East = -0.353999 +/- 0.0286307
  row.laserDriftVelocityWest	 =   5.57319; // +/- 2.45558e-05 cm/us All: West = 0.257544 +/- 0.00437696
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57319 +/- 2.45558e-05
  return (TDataSet *)tableSet;// West = 5.57312 +/- 2.48108e-05 East = 5.57634 +/- 0.000171714
};
