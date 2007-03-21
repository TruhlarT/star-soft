TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6029006
  row.laserDriftVelocityEast	 =   5.55541; // +/- 5.14561e-05 cm/us All: East = 5.55556 +/- 0.000345144
  row.laserDriftVelocityWest	 =   5.55541; // +/- 5.14561e-05 cm/us All: West = 5.5554 +/- 5.20376e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 2.46081 +/- 0.00929125
  return (TDataSet *)tableSet;// West = 2.46086 +/- 0.00939346 East = 2.4585 +/- 0.063153
};
