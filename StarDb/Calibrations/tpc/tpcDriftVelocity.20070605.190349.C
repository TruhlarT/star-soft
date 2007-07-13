TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 156058
  row.laserDriftVelocityEast	 =   5.57414; // +/- 2.62545e-05 cm/us All: East = -0.87897 +/- 0.724428
  row.laserDriftVelocityWest	 =   5.57414; // +/- 2.62545e-05 cm/us All: West = 0.073318 +/- 0.00467549
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57414 +/- 2.62545e-05
  return (TDataSet *)tableSet;// West = 5.57414 +/- 2.62545e-05 East = 5.58963 +/- 0.0450475
};
