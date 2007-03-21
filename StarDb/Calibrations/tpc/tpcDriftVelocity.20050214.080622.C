TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6045032
  row.laserDriftVelocityEast	 =   5.52836; // +/- 3.87691e-05 cm/us All: East = 5.52726 +/- 9.02831e-05
  row.laserDriftVelocityWest	 =   5.52836; // +/- 3.87691e-05 cm/us All: West = 5.52861 +/- 4.29286e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.779547 +/- 0.00714289
  return (TDataSet *)tableSet;// West = 0.737793 +/- 0.00788565 East = 0.970388 +/- 0.0168589
};
