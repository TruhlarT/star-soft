TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6050014
  row.laserDriftVelocityEast	 =   5.53347; // +/- 7.01504e-05 cm/us All: East = 5.53354 +/- 0.00014239
  row.laserDriftVelocityWest	 =   5.53347; // +/- 7.01504e-05 cm/us All: West = 5.53344 +/- 8.06123e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.751775 +/- 0.0126221
  return (TDataSet *)tableSet;// West = 0.758668 +/- 0.014291 East = 0.727324 +/- 0.0269157
};
