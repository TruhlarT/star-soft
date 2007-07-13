TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 127003
  row.laserDriftVelocityEast	 =   5.57625; // +/- 1.82141e-05 cm/us All: East = -0.339025 +/- 0.00385471
  row.laserDriftVelocityWest	 =   5.57625; // +/- 1.82141e-05 cm/us All: West = -0.233312 +/- 0.00624219
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57625 +/- 1.82141e-05
  return (TDataSet *)tableSet;// West = 5.57583 +/- 3.40781e-05 East = 5.57641 +/- 2.15506e-05
};
