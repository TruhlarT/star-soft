TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 102058
  row.laserDriftVelocityEast	 =   5.57235; // +/- 1.2524e-05 cm/us All: East = 0.949167 +/- 0.00284594
  row.laserDriftVelocityWest	 =   5.57235; // +/- 1.2524e-05 cm/us All: West = 0.553304 +/- 0.00378214
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57235 +/- 1.2524e-05
  return (TDataSet *)tableSet;// West = 5.57372 +/- 2.06482e-05 East = 5.57155 +/- 1.57524e-05
};
