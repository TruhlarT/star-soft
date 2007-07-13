TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 126031
  row.laserDriftVelocityEast	 =   5.57852; // +/- 1.8342e-05 cm/us All: East = -0.765789 +/- 0.0040201
  row.laserDriftVelocityWest	 =   5.57852; // +/- 1.8342e-05 cm/us All: West = -0.618849 +/- 0.00575336
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57852 +/- 1.8342e-05
  return (TDataSet *)tableSet;// West = 5.57798 +/- 3.21837e-05 East = 5.57879 +/- 2.2322e-05
};
