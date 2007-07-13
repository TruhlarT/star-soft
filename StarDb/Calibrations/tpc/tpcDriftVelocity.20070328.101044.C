TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 87013
  row.laserDriftVelocityEast	 =   5.57552; // +/- 2.47545e-05 cm/us All: East = -1.41902 +/- 0.00541268
  row.laserDriftVelocityWest	 =   5.57552; // +/- 2.47545e-05 cm/us All: West = -1.6419 +/- 0.00795604
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57552 +/- 2.47545e-05
  return (TDataSet *)tableSet;// West = 5.57641 +/- 4.44938e-05 East = 5.57512 +/- 2.97908e-05
};
