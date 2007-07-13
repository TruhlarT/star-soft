TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 139094
  row.laserDriftVelocityEast	 =   5.57497; // +/- 2.70672e-05 cm/us All: East = -0.105016 +/- 0.00607215
  row.laserDriftVelocityWest	 =   5.57497; // +/- 2.70672e-05 cm/us All: West = -0.0209432 +/- 0.00779423
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57497 +/- 2.70672e-05
  return (TDataSet *)tableSet;// West = 5.57465 +/- 4.39292e-05 East = 5.57516 +/- 3.43656e-05
};
