TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 139043
  row.laserDriftVelocityEast	 =   5.57455; // +/- 2.33801e-05 cm/us All: East = 0.0300045 +/- 0.00499805
  row.laserDriftVelocityWest	 =   5.57455; // +/- 2.33801e-05 cm/us All: West = -0.0821738 +/- 0.00732618
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57455 +/- 2.33801e-05
  return (TDataSet *)tableSet;// West = 5.57504 +/- 4.2148e-05 East = 5.57434 +/- 2.80997e-05
};
