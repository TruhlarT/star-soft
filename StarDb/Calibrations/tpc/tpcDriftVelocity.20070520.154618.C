TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 140041
  row.laserDriftVelocityEast	 =   5.57532; // +/- 1.78824e-05 cm/us All: East = -0.160797 +/- 0.00390889
  row.laserDriftVelocityWest	 =   5.57532; // +/- 1.78824e-05 cm/us All: West = -0.101468 +/- 0.00567616
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57532 +/- 1.78824e-05
  return (TDataSet *)tableSet;// West = 5.57509 +/- 3.11204e-05 East = 5.57543 +/- 2.185e-05
};
