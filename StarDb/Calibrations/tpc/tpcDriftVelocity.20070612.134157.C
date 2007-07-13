TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 163037
  row.laserDriftVelocityEast	 =   5.57286; // +/- 2.1854e-05 cm/us All: East = 0.35188 +/- 0.00878785
  row.laserDriftVelocityWest	 =   5.57286; // +/- 2.1854e-05 cm/us All: West = 0.288243 +/- 0.00426446
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57286 +/- 2.1854e-05
  return (TDataSet *)tableSet;// West = 5.57295 +/- 2.4498e-05 East = 5.57251 +/- 4.83615e-05
};
