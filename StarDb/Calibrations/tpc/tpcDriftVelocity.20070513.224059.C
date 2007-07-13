TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 133065
  row.laserDriftVelocityEast	 =   5.57109; // +/- 1.59647e-05 cm/us All: East = 0.649577 +/- 0.00326428
  row.laserDriftVelocityWest	 =   5.57109; // +/- 1.59647e-05 cm/us All: West = 0.527769 +/- 0.00626926
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57109 +/- 1.59647e-05
  return (TDataSet *)tableSet;// West = 5.57159 +/- 3.45549e-05 East = 5.57096 +/- 1.80011e-05
};
