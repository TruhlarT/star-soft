TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 106074
  row.laserDriftVelocityEast	 =   5.57972; // +/- 2.38801e-05 cm/us All: East = -0.963777 +/- 0.00543224
  row.laserDriftVelocityWest	 =   5.57972; // +/- 2.38801e-05 cm/us All: West = -0.875048 +/- 0.00692639
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57972 +/- 2.38801e-05
  return (TDataSet *)tableSet;// West = 5.57941 +/- 3.88913e-05 East = 5.57991 +/- 3.02551e-05
};
