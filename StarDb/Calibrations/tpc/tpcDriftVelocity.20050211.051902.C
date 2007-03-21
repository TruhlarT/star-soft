TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6042002
  row.laserDriftVelocityEast	 =   5.52798; // +/- 3.71151e-05 cm/us All: East = 5.52711 +/- 9.05739e-05
  row.laserDriftVelocityWest	 =   5.52798; // +/- 3.71151e-05 cm/us All: West = 5.52815 +/- 4.06881e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.34645 +/- 0.00684397
  return (TDataSet *)tableSet;// West = 1.3185 +/- 0.00753134 East = 1.47897 +/- 0.0163974
};
