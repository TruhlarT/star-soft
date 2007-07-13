TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 109018
  row.laserDriftVelocityEast	 =   5.57435; // +/- 1.20363e-05 cm/us All: East = 0.239654 +/- 0.00307552
  row.laserDriftVelocityWest	 =   5.57435; // +/- 1.20363e-05 cm/us All: West = -0.178091 +/- 0.0030456
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57435 +/- 1.20363e-05
  return (TDataSet *)tableSet;// West = 5.57552 +/- 1.70066e-05 East = 5.57319 +/- 1.70371e-05
};
