TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6078010
  row.laserDriftVelocityEast	 =   5.5303; // +/- 4.72572e-05 cm/us All: East = 5.53078 +/- 7.3756e-05
  row.laserDriftVelocityWest	 =   5.5303; // +/- 4.72572e-05 cm/us All: West = 5.52997 +/- 6.15511e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.393707 +/- 0.00848897
  return (TDataSet *)tableSet;// West = 0.457583 +/- 0.0108948 East = 0.295 +/- 0.0135433
};
