TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 128065
  row.laserDriftVelocityEast	 =   5.57723; // +/- 1.86733e-05 cm/us All: East = -0.519174 +/- 0.00443078
  row.laserDriftVelocityWest	 =   5.57723; // +/- 1.86733e-05 cm/us All: West = -0.435466 +/- 0.00517209
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57723 +/- 1.86733e-05
  return (TDataSet *)tableSet;// West = 5.57696 +/- 2.87278e-05 East = 5.57743 +/- 2.45726e-05
};
