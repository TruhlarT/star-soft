TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 139018
  row.laserDriftVelocityEast	 =   5.57431; // +/- 1.77567e-05 cm/us All: East = 0.0716225 +/- 0.00391948
  row.laserDriftVelocityWest	 =   5.57431; // +/- 1.77567e-05 cm/us All: West = -0.0341767 +/- 0.00547352
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57431 +/- 1.77567e-05
  return (TDataSet *)tableSet;// West = 5.57472 +/- 3.04841e-05 East = 5.57411 +/- 2.18454e-05
};
