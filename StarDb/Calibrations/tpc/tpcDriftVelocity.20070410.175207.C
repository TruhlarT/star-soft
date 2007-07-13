TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 100169
  row.laserDriftVelocityEast	 =   5.57266; // +/- 1.76443e-05 cm/us All: East = 0.795272 +/- 0.00447219
  row.laserDriftVelocityWest	 =   5.57266; // +/- 1.76443e-05 cm/us All: West = 0.707926 +/- 0.0044549
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57266 +/- 1.76443e-05
  return (TDataSet *)tableSet;// West = 5.57289 +/- 2.50143e-05 East = 5.57243 +/- 2.48918e-05
};
