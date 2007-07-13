TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 138018
  row.laserDriftVelocityEast	 =   5.57465; // +/- 2.47254e-05 cm/us All: East = -0.0156363 +/- 0.004906
  row.laserDriftVelocityWest	 =   5.57465; // +/- 2.47254e-05 cm/us All: West = -0.108292 +/- 0.010126
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57465 +/- 2.47254e-05
  return (TDataSet *)tableSet;// West = 5.57514 +/- 5.4471e-05 East = 5.57452 +/- 2.77488e-05
};
