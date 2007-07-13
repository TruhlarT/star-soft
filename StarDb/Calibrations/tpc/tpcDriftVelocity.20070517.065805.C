TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 137010
  row.laserDriftVelocityEast	 =   5.57555; // +/- 3.30544e-05 cm/us All: East = -0.321983 +/- 0.00898987
  row.laserDriftVelocityWest	 =   5.57555; // +/- 3.30544e-05 cm/us All: West = -0.0822133 +/- 0.00774321
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57555 +/- 3.30544e-05
  return (TDataSet *)tableSet;// West = 5.57499 +/- 4.32513e-05 East = 5.57633 +/- 5.12526e-05
};
