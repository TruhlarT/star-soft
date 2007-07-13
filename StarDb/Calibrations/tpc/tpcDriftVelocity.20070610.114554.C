TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 161038
  row.laserDriftVelocityEast	 =   5.57331; // +/- 2.61442e-05 cm/us All: East = 0.6265 +/- 1.41421
  row.laserDriftVelocityWest	 =   5.57331; // +/- 2.61442e-05 cm/us All: West = 0.219236 +/- 0.00472407
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57331 +/- 2.61442e-05
  return (TDataSet *)tableSet;// West = 5.57331 +/- 2.61442e-05 East = 11.1456 +/- 1.41421
};
