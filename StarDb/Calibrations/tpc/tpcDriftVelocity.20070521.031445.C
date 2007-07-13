TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 140075
  row.laserDriftVelocityEast	 =   5.57557; // +/- 2.37395e-05 cm/us All: East = -0.460987 +/- 0.00727941
  row.laserDriftVelocityWest	 =   5.57557; // +/- 2.37395e-05 cm/us All: West = -0.0539249 +/- 0.00512332
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57557 +/- 2.37395e-05
  return (TDataSet *)tableSet;// West = 5.57481 +/- 2.89542e-05 East = 5.57712 +/- 4.14656e-05
};
