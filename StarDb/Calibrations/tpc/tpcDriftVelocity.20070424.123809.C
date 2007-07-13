TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 114033
  row.laserDriftVelocityEast	 =   5.57746; // +/- 1.78357e-05 cm/us All: East = -0.550414 +/- 0.00386514
  row.laserDriftVelocityWest	 =   5.57746; // +/- 1.78357e-05 cm/us All: West = -0.481202 +/- 0.00564087
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57746 +/- 1.78357e-05
  return (TDataSet *)tableSet;// West = 5.57722 +/- 3.13483e-05 East = 5.57758 +/- 2.16883e-05
};
