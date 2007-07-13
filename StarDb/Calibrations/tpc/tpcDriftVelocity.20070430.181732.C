TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 120070
  row.laserDriftVelocityEast	 =   5.57898; // +/- 1.47319e-05 cm/us All: East = -0.784964 +/- 0.00315247
  row.laserDriftVelocityWest	 =   5.57898; // +/- 1.47319e-05 cm/us All: West = -0.829391 +/- 0.0047346
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57898 +/- 1.47319e-05
  return (TDataSet *)tableSet;// West = 5.57916 +/- 2.64776e-05 East = 5.5789 +/- 1.77297e-05
};
