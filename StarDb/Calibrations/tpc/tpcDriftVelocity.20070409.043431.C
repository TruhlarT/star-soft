TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 99004
  row.laserDriftVelocityEast	 =   5.57346; // +/- 2.41894e-05 cm/us All: East = 0.746163 +/- 0.00801816
  row.laserDriftVelocityWest	 =   5.57346; // +/- 2.41894e-05 cm/us All: West = 0.782308 +/- 0.00650217
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57346 +/- 2.41894e-05
  return (TDataSet *)tableSet;// West = 5.57343 +/- 3.17885e-05 East = 5.57349 +/- 3.72828e-05
};
