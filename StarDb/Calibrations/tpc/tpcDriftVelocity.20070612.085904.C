TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 163016
  row.laserDriftVelocityEast	 =   5.57357; // +/- 2.71083e-05 cm/us All: East = 0 +/- 0
  row.laserDriftVelocityWest	 =   5.57357; // +/- 2.71083e-05 cm/us All: West = 0.173809 +/- 0.00488557
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57357 +/- 2.71083e-05
  return (TDataSet *)tableSet;// West = 5.57357 +/- 2.71083e-05 East = 0 +/- 0
};
