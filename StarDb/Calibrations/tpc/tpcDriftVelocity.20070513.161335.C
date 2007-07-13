TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 133038
  row.laserDriftVelocityEast	 =   5.57043; // +/- 2.38594e-05 cm/us All: East = 0.704144 +/- 0.00547192
  row.laserDriftVelocityWest	 =   5.57043; // +/- 2.38594e-05 cm/us All: West = 0.772327 +/- 0.00693456
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57043 +/- 2.38594e-05
  return (TDataSet *)tableSet;// West = 5.57022 +/- 3.86392e-05 East = 5.57057 +/- 3.03332e-05
};
