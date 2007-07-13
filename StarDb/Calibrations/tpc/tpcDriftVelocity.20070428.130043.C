TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 118049
  row.laserDriftVelocityEast	 =   5.57771; // +/- 1.68862e-05 cm/us All: East = -0.598256 +/- 0.00347921
  row.laserDriftVelocityWest	 =   5.57771; // +/- 1.68862e-05 cm/us All: West = -0.473028 +/- 0.00589896
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57771 +/- 1.68862e-05
  return (TDataSet *)tableSet;// West = 5.57717 +/- 3.31735e-05 East = 5.5779 +/- 1.96179e-05
};
