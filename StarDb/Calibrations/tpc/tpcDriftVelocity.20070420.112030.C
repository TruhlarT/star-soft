TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 110046
  row.laserDriftVelocityEast	 =   5.57403; // +/- 1.40084e-05 cm/us All: East = 0.268046 +/- 0.00346151
  row.laserDriftVelocityWest	 =   5.57403; // +/- 1.40084e-05 cm/us All: West = -0.125304 +/- 0.00367203
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57403 +/- 1.40084e-05
  return (TDataSet *)tableSet;// West = 5.57523 +/- 2.06303e-05 East = 5.573 +/- 1.90818e-05
};
