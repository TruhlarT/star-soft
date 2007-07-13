TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 160028
  row.laserDriftVelocityEast	 =   5.57339; // +/- 2.10079e-05 cm/us All: East = 0.226091 +/- 0.00677213
  row.laserDriftVelocityWest	 =   5.57339; // +/- 2.10079e-05 cm/us All: West = 0.208161 +/- 0.00453175
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57339 +/- 2.10079e-05
  return (TDataSet *)tableSet;// West = 5.57341 +/- 2.55278e-05 East = 5.57333 +/- 3.69777e-05
};
