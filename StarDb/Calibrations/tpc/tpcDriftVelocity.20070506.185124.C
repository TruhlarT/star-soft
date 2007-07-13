TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 126072
  row.laserDriftVelocityEast	 =   5.57625; // +/- 2.06089e-05 cm/us All: East = -0.267983 +/- 0.00425427
  row.laserDriftVelocityWest	 =   5.57625; // +/- 2.06089e-05 cm/us All: West = -0.418404 +/- 0.00721141
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57625 +/- 2.06089e-05
  return (TDataSet *)tableSet;// West = 5.57684 +/- 4.04252e-05 East = 5.57604 +/- 2.39558e-05
};
