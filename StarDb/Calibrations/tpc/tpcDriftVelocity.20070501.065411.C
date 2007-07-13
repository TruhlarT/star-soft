TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 121013
  row.laserDriftVelocityEast	 =   5.57897; // +/- 1.75748e-05 cm/us All: East = -0.788894 +/- 0.00385379
  row.laserDriftVelocityWest	 =   5.57897; // +/- 1.75748e-05 cm/us All: West = -0.808979 +/- 0.00561018
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57897 +/- 1.75748e-05
  return (TDataSet *)tableSet;// West = 5.57905 +/- 3.10499e-05 East = 5.57894 +/- 2.13184e-05
};
