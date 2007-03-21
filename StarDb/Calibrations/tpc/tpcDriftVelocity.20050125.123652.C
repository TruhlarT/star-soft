TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6025051
  row.laserDriftVelocityEast	 =   5.5545; // +/- 0.000331837 cm/us All: East = 5.555 +/- 0.000513541
  row.laserDriftVelocityWest	 =   5.5545; // +/- 0.000331837 cm/us All: West = 5.55414 +/- 0.000434801
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.634 +/- 0.0662119
  return (TDataSet *)tableSet;// West = 1.66957 +/- 0.0896666 East = 1.59135 +/- 0.0981882
};
