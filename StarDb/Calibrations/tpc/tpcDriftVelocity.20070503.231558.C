TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 123065
  row.laserDriftVelocityEast	 =   5.57753; // +/- 1.61703e-05 cm/us All: East = -0.518272 +/- 0.00300583
  row.laserDriftVelocityWest	 =   5.57753; // +/- 1.61703e-05 cm/us All: West = -0.783499 +/- 0.0105595
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57753 +/- 1.61703e-05
  return (TDataSet *)tableSet;// West = 5.57888 +/- 6.02009e-05 East = 5.57743 +/- 1.67872e-05
};
