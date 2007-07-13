TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 110011
  row.laserDriftVelocityEast	 =   5.57474; // +/- 1.93368e-05 cm/us All: East = 0.0648289 +/- 0.00552032
  row.laserDriftVelocityWest	 =   5.57474; // +/- 1.93368e-05 cm/us All: West = -0.101563 +/- 0.00441651
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57474 +/- 1.93368e-05
  return (TDataSet *)tableSet;// West = 5.57509 +/- 2.4661e-05 East = 5.57418 +/- 3.11568e-05
};
