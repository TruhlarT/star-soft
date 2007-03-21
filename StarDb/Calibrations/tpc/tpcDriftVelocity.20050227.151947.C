TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6058034
  row.laserDriftVelocityEast	 =   5.53684; // +/- 0.000855664 cm/us All: East = 5.5389 +/- 0.00360687
  row.laserDriftVelocityWest	 =   5.53684; // +/- 0.000855664 cm/us All: West = 5.53672 +/- 0.000880809
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.06149 +/- 0.188514
  return (TDataSet *)tableSet;// West = 1.09799 +/- 0.198303 East = 0.718995 +/- 0.607493
};
