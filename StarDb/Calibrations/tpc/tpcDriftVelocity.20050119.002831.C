TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6018043
  row.laserDriftVelocityEast	 =   5.54583; // +/- 7.02594e-05 cm/us All: East = 5.5465 +/- 0.000142717
  row.laserDriftVelocityWest	 =   5.54583; // +/- 7.02594e-05 cm/us All: West = 5.54561 +/- 8.07184e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.15457 +/- 0.0130399
  return (TDataSet *)tableSet;// West = 1.22568 +/- 0.0150459 East = 0.939978 +/- 0.0261383
};
