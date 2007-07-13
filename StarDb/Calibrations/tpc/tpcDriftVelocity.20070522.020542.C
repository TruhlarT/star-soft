TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 141108
  row.laserDriftVelocityEast	 =   5.57489; // +/- 1.97135e-05 cm/us All: East = -0.114771 +/- 0.0046205
  row.laserDriftVelocityWest	 =   5.57489; // +/- 1.97135e-05 cm/us All: West = -0.00819303 +/- 0.00549922
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57489 +/- 1.97135e-05
  return (TDataSet *)tableSet;// West = 5.57456 +/- 3.07636e-05 East = 5.57513 +/- 2.56785e-05
};
