TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 105012
  row.laserDriftVelocityEast	 =   5.58271; // +/- 1.87654e-05 cm/us All: East = 0 +/- 0
  row.laserDriftVelocityWest	 =   5.58271; // +/- 1.87654e-05 cm/us All: West = -1.4658 +/- 0.00331771
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.58271 +/- 1.87654e-05
  return (TDataSet *)tableSet;// West = 5.58271 +/- 1.87654e-05 East = 0 +/- 0
};
