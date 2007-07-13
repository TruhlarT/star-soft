TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 104079
  row.laserDriftVelocityEast	 =   5.58219; // +/- 1.26526e-05 cm/us All: East = -1.33445 +/- 0.00333701
  row.laserDriftVelocityWest	 =   5.58219; // +/- 1.26526e-05 cm/us All: West = -1.40438 +/- 0.00307943
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.58219 +/- 1.26526e-05
  return (TDataSet *)tableSet;// West = 5.58237 +/- 1.72736e-05 East = 5.58199 +/- 1.85854e-05
};
