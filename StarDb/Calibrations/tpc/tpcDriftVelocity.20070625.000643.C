TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 175073
  row.laserDriftVelocityEast	 =   5.57203; // +/- 2.40816e-05 cm/us All: East = 0.651477 +/- 0.00720869
  row.laserDriftVelocityWest	 =   5.57203; // +/- 2.40816e-05 cm/us All: West = 0.31035 +/- 0.00563171
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57203 +/- 2.40816e-05
  return (TDataSet *)tableSet;// West = 5.57278 +/- 3.06825e-05 East = 5.57082 +/- 3.88624e-05
};
