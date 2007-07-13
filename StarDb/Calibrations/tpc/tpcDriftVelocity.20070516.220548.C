TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 136056
  row.laserDriftVelocityEast	 =   5.57579; // +/- 2.07593e-05 cm/us All: East = -0.280002 +/- 0.00468331
  row.laserDriftVelocityWest	 =   5.57579; // +/- 2.07593e-05 cm/us All: West = -0.149272 +/- 0.00634576
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57579 +/- 2.07593e-05
  return (TDataSet *)tableSet;// West = 5.57535 +/- 3.50311e-05 East = 5.57602 +/- 2.57719e-05
};
