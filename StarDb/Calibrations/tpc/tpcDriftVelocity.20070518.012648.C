TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 137073
  row.laserDriftVelocityEast	 =   5.57509; // +/- 2.24688e-05 cm/us All: East = -0.220326 +/- 0.00548597
  row.laserDriftVelocityWest	 =   5.57509; // +/- 2.24688e-05 cm/us All: West = 0.0405378 +/- 0.00598742
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57509 +/- 2.24688e-05
  return (TDataSet *)tableSet;// West = 5.5743 +/- 3.36489e-05 East = 5.57572 +/- 3.0184e-05
};
