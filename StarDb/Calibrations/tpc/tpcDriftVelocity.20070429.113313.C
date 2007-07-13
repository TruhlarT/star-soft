TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 119018
  row.laserDriftVelocityEast	 =   5.57831; // +/- 1.83516e-05 cm/us All: East = -0.730495 +/- 0.00417409
  row.laserDriftVelocityWest	 =   5.57831; // +/- 1.83516e-05 cm/us All: West = -0.598936 +/- 0.00533151
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57831 +/- 1.83516e-05
  return (TDataSet *)tableSet;// West = 5.57785 +/- 2.97201e-05 East = 5.5786 +/- 2.33307e-05
};
