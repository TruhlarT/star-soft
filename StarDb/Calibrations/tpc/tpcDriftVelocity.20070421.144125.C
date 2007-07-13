TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 111067
  row.laserDriftVelocityEast	 =   5.57457; // +/- 1.65035e-05 cm/us All: East = -0.0524924 +/- 0.00378587
  row.laserDriftVelocityWest	 =   5.57457; // +/- 1.65035e-05 cm/us All: West = 0.0649854 +/- 0.00476884
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57457 +/- 1.65035e-05
  return (TDataSet *)tableSet;// West = 5.57418 +/- 2.6279e-05 East = 5.57482 +/- 2.12071e-05
};
