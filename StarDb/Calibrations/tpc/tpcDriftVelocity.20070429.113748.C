TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 119019
  row.laserDriftVelocityEast	 =   5.57805; // +/- 1.59592e-05 cm/us All: East = -0.622608 +/- 0.00367353
  row.laserDriftVelocityWest	 =   5.57805; // +/- 1.59592e-05 cm/us All: West = -0.646262 +/- 0.00458847
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57805 +/- 1.59592e-05
  return (TDataSet *)tableSet;// West = 5.57813 +/- 2.55592e-05 East = 5.57799 +/- 2.04316e-05
};
