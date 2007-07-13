TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 139019
  row.laserDriftVelocityEast	 =   5.57407; // +/- 1.71031e-05 cm/us All: East = 0.141957 +/- 0.00360219
  row.laserDriftVelocityWest	 =   5.57407; // +/- 1.71031e-05 cm/us All: West = -0.0870063 +/- 0.00598562
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57407 +/- 1.71031e-05
  return (TDataSet *)tableSet;// West = 5.57501 +/- 3.27825e-05 East = 5.57372 +/- 2.00476e-05
};
