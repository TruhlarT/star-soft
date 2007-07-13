TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 156011
  row.laserDriftVelocityEast	 =   5.5739; // +/- 2.42957e-05 cm/us All: East = -0.411416 +/- 0.0177706
  row.laserDriftVelocityWest	 =   5.5739; // +/- 2.42957e-05 cm/us All: West = 0.14455 +/- 0.00447389
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5739 +/- 2.42957e-05
  return (TDataSet *)tableSet;// West = 5.57372 +/- 2.50283e-05 East = 5.57676 +/- 0.000101156
};
