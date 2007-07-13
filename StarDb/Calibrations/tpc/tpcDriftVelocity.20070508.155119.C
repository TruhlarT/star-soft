TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 128053
  row.laserDriftVelocityEast	 =   5.57661; // +/- 1.81509e-05 cm/us All: East = -0.367274 +/- 0.00403458
  row.laserDriftVelocityWest	 =   5.57661; // +/- 1.81509e-05 cm/us All: West = -0.397931 +/- 0.00568767
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57661 +/- 1.81509e-05
  return (TDataSet *)tableSet;// West = 5.57675 +/- 3.13023e-05 East = 5.57654 +/- 2.22789e-05
};
