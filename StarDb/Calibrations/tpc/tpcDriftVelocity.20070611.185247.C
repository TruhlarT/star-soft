TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 162049
  row.laserDriftVelocityEast	 =   5.57358; // +/- 2.55726e-05 cm/us All: East = 0.144766 +/- 0.0111243
  row.laserDriftVelocityWest	 =   5.57358; // +/- 2.55726e-05 cm/us All: West = 0.170617 +/- 0.00502236
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57358 +/- 2.55726e-05
  return (TDataSet *)tableSet;// West = 5.57354 +/- 2.80054e-05 East = 5.57378 +/- 6.27285e-05
};
