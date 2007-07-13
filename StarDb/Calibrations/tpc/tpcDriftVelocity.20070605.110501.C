TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 156032
  row.laserDriftVelocityEast	 =   5.57417; // +/- 2.15299e-05 cm/us All: East = 0.295264 +/- 0.0104578
  row.laserDriftVelocityWest	 =   5.57417; // +/- 2.15299e-05 cm/us All: West = 0.0290278 +/- 0.00415221
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57417 +/- 2.15299e-05
  return (TDataSet *)tableSet;// West = 5.57438 +/- 2.31674e-05 East = 5.57288 +/- 5.83041e-05
};
