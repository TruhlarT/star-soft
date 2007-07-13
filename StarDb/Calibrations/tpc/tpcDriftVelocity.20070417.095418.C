TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 107018
  row.laserDriftVelocityEast	 =   5.57793; // +/- 1.48825e-05 cm/us All: East = -0.632839 +/- 0.00326607
  row.laserDriftVelocityWest	 =   5.57793; // +/- 1.48825e-05 cm/us All: West = -0.561578 +/- 0.00461004
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57793 +/- 1.48825e-05
  return (TDataSet *)tableSet;// West = 5.57766 +/- 2.59224e-05 East = 5.57806 +/- 1.81765e-05
};
