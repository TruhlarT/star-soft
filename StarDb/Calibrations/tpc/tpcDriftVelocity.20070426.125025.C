TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 116059
  row.laserDriftVelocityEast	 =   5.57664; // +/- 1.56839e-05 cm/us All: East = -0.363381 +/- 0.00353142
  row.laserDriftVelocityWest	 =   5.57664; // +/- 1.56839e-05 cm/us All: West = -0.405785 +/- 0.00461644
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57664 +/- 1.56839e-05
  return (TDataSet *)tableSet;// West = 5.57679 +/- 2.59627e-05 East = 5.57655 +/- 1.96808e-05
};
