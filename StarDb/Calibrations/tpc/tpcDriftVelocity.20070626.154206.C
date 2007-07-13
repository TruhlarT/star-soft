TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 177063
  row.laserDriftVelocityEast	 =   5.57064; // +/- 1.93678e-05 cm/us All: East = 0.974393 +/- 0.0075914
  row.laserDriftVelocityWest	 =   5.57064; // +/- 1.93678e-05 cm/us All: West = 0.627761 +/- 0.00388173
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57064 +/- 1.93678e-05
  return (TDataSet *)tableSet;// West = 5.57103 +/- 2.1654e-05 East = 5.56908 +/- 4.33063e-05
};
