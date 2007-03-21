TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6041019
  row.laserDriftVelocityEast	 =   5.52913; // +/- 3.74981e-05 cm/us All: East = 5.52854 +/- 8.03678e-05
  row.laserDriftVelocityWest	 =   5.52913; // +/- 3.74981e-05 cm/us All: West = 5.52929 +/- 4.23957e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 2.41752 +/- 0.00682611
  return (TDataSet *)tableSet;// West = 2.38437 +/- 0.00772998 East = 2.53494 +/- 0.0145471
};
