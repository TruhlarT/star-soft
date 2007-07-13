TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 121120
  row.laserDriftVelocityEast	 =   5.57985; // +/- 1.95934e-05 cm/us All: East = -0.989366 +/- 0.00503994
  row.laserDriftVelocityWest	 =   5.57985; // +/- 1.95934e-05 cm/us All: West = -0.912994 +/- 0.00483437
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57985 +/- 1.95934e-05
  return (TDataSet *)tableSet;// West = 5.57965 +/- 2.74725e-05 East = 5.58005 +/- 2.79524e-05
};
