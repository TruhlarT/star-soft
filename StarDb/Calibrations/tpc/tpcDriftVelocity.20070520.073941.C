TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 140016
  row.laserDriftVelocityEast	 =   5.5753; // +/- 2.30183e-05 cm/us All: East = -0.158949 +/- 0.00472633
  row.laserDriftVelocityWest	 =   5.5753; // +/- 2.30183e-05 cm/us All: West = -0.103402 +/- 0.00805559
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5753 +/- 2.30183e-05
  return (TDataSet *)tableSet;// West = 5.57509 +/- 4.43384e-05 East = 5.57537 +/- 2.69319e-05
};
