TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 133071
  row.laserDriftVelocityEast	 =   5.57128; // +/- 1.65856e-05 cm/us All: East = 0.619748 +/- 0.00349763
  row.laserDriftVelocityWest	 =   5.57128; // +/- 1.65856e-05 cm/us All: West = 0.49464 +/- 0.00576844
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57128 +/- 1.65856e-05
  return (TDataSet *)tableSet;// West = 5.57177 +/- 3.21466e-05 East = 5.5711 +/- 1.93616e-05
};
