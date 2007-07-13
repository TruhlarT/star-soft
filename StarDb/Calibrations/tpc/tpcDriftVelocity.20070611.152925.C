TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 162038
  row.laserDriftVelocityEast	 =   5.57351; // +/- 2.18836e-05 cm/us All: East = 0.118375 +/- 0.00859305
  row.laserDriftVelocityWest	 =   5.57351; // +/- 2.18836e-05 cm/us All: West = 0.202901 +/- 0.00444994
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57351 +/- 2.18836e-05
  return (TDataSet *)tableSet;// West = 5.5734 +/- 2.47566e-05 East = 5.57391 +/- 4.68013e-05
};
