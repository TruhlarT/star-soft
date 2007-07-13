TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 159068
  row.laserDriftVelocityEast	 =   5.57395; // +/- 2.23504e-05 cm/us All: East = 0.0265647 +/- 0.00762436
  row.laserDriftVelocityWest	 =   5.57395; // +/- 2.23504e-05 cm/us All: West = 0.141357 +/- 0.00467533
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57395 +/- 2.23504e-05
  return (TDataSet *)tableSet;// West = 5.57378 +/- 2.61104e-05 East = 5.57442 +/- 4.32324e-05
};
