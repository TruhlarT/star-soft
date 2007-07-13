TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 119089
  row.laserDriftVelocityEast	 =   5.57861; // +/- 2.24935e-05 cm/us All: East = -0.801003 +/- 0.00564194
  row.laserDriftVelocityWest	 =   5.57861; // +/- 2.24935e-05 cm/us All: West = -0.64605 +/- 0.00581418
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57861 +/- 2.24935e-05
  return (TDataSet *)tableSet;// West = 5.57812 +/- 3.2726e-05 East = 5.57904 +/- 3.09679e-05
};
