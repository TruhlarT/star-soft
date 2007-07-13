TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 172095
  row.laserDriftVelocityEast	 =   5.57138; // +/- 2.19372e-05 cm/us All: East = 0.684308 +/- 0.00565625
  row.laserDriftVelocityWest	 =   5.57138; // +/- 2.19372e-05 cm/us All: West = 0.4431 +/- 0.00552452
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57138 +/- 2.19372e-05
  return (TDataSet *)tableSet;// West = 5.57205 +/- 3.08232e-05 East = 5.5707 +/- 3.12287e-05
};
