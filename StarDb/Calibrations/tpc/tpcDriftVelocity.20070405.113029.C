TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 95064
  row.laserDriftVelocityEast	 =   5.57824; // +/- 1.42635e-05 cm/us All: East = -2.00937 +/- 0.00319191
  row.laserDriftVelocityWest	 =   5.57824; // +/- 1.42635e-05 cm/us All: West = -1.90884 +/- 0.00410277
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57824 +/- 1.42635e-05
  return (TDataSet *)tableSet;// West = 5.57788 +/- 2.31588e-05 East = 5.57846 +/- 1.81049e-05
};
