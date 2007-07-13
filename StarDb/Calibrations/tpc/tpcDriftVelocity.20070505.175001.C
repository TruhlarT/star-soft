TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 125081
  row.laserDriftVelocityEast	 =   5.57883; // +/- 2.65696e-05 cm/us All: East = -0.761818 +/- 0.00652613
  row.laserDriftVelocityWest	 =   5.57883; // +/- 2.65696e-05 cm/us All: West = -0.794059 +/- 0.00731241
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57883 +/- 2.65696e-05
  return (TDataSet *)tableSet;// West = 5.57893 +/- 3.92534e-05 East = 5.57875 +/- 3.60951e-05
};
