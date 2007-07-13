TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 163008
  row.laserDriftVelocityEast	 =   5.57297; // +/- 2.11755e-05 cm/us All: East = 0.265039 +/- 0.00849089
  row.laserDriftVelocityWest	 =   5.57297; // +/- 2.11755e-05 cm/us All: West = 0.274592 +/- 0.00424061
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57297 +/- 2.11755e-05
  return (TDataSet *)tableSet;// West = 5.57298 +/- 2.368e-05 East = 5.57291 +/- 4.73097e-05
};
