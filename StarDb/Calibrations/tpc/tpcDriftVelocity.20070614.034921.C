TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 164046
  row.laserDriftVelocityEast	 =   5.5717; // +/- 2.26697e-05 cm/us All: East = 0.666515 +/- 0.00496138
  row.laserDriftVelocityWest	 =   5.5717; // +/- 2.26697e-05 cm/us All: West = 0.137613 +/- 0.00731862
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5717 +/- 2.26697e-05
  return (TDataSet *)tableSet;// West = 5.57378 +/- 4.04619e-05 East = 5.57075 +/- 2.73686e-05
};
