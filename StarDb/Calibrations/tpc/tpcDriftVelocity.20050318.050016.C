TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6076120
  row.laserDriftVelocityEast	 =   5.53024; // +/- 8.9291e-05 cm/us All: East = 5.53002 +/- 0.000129997
  row.laserDriftVelocityWest	 =   5.53024; // +/- 8.9291e-05 cm/us All: West = 5.53044 +/- 0.000122859
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.417214 +/- 0.0160642
  return (TDataSet *)tableSet;// West = 0.385113 +/- 0.0219523 East = 0.454221 +/- 0.0235701
};
