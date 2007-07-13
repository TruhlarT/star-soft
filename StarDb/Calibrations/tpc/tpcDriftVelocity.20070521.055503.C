TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 141015
  row.laserDriftVelocityEast	 =   5.57517; // +/- 2.64347e-05 cm/us All: East = -0.0891835 +/- 0.00748686
  row.laserDriftVelocityWest	 =   5.57517; // +/- 2.64347e-05 cm/us All: West = -0.134471 +/- 0.00613993
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57517 +/- 2.64347e-05
  return (TDataSet *)tableSet;// West = 5.57523 +/- 3.36481e-05 East = 5.57506 +/- 4.27256e-05
};
