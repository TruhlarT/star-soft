TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 161074
  row.laserDriftVelocityEast	 =   5.57345; // +/- 2.51385e-05 cm/us All: East = 0.17794 +/- 0.00953289
  row.laserDriftVelocityWest	 =   5.57345; // +/- 2.51385e-05 cm/us All: West = 0.198219 +/- 0.00502514
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57345 +/- 2.51385e-05
  return (TDataSet *)tableSet;// West = 5.57342 +/- 2.84378e-05 East = 5.57358 +/- 5.37701e-05
};
