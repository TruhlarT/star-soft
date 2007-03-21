TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6012001
  row.laserDriftVelocityEast	 =   5.51158; // +/- 4.88288e-05 cm/us All: East = 5.51179 +/- 8.1245e-05
  row.laserDriftVelocityWest	 =   5.51158; // +/- 4.88288e-05 cm/us All: West = 5.51146 +/- 6.10937e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 2.45893 +/- 0.00886484
  return (TDataSet *)tableSet;// West = 2.48078 +/- 0.0110916 East = 2.42029 +/- 0.0147499
};
