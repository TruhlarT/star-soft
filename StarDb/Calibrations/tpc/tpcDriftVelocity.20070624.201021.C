TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 175056
  row.laserDriftVelocityEast	 =   5.57267; // +/- 2.14082e-05 cm/us All: East = 0.510972 +/- 0.006137
  row.laserDriftVelocityWest	 =   5.57267; // +/- 2.14082e-05 cm/us All: West = 0.215024 +/- 0.00513349
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57267 +/- 2.14082e-05
  return (TDataSet *)tableSet;// West = 5.57334 +/- 2.78304e-05 East = 5.57171 +/- 3.35045e-05
};
