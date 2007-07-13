TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 114020
  row.laserDriftVelocityEast	 =   5.57773; // +/- 2.11072e-05 cm/us All: East = -0.75973 +/- 0.00720045
  row.laserDriftVelocityWest	 =   5.57773; // +/- 2.11072e-05 cm/us All: West = -0.509821 +/- 0.00446973
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57773 +/- 2.11072e-05
  return (TDataSet *)tableSet;// West = 5.57737 +/- 2.47143e-05 East = 5.57869 +/- 4.05754e-05
};
