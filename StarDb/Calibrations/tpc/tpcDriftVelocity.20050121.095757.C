TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6021008
  row.laserDriftVelocityEast	 =   5.55296; // +/- 4.01313e-05 cm/us All: East = 5.55296 +/- 4.01313e-05
  row.laserDriftVelocityWest	 =   5.55296; // +/- 4.01313e-05 cm/us All: West = 1.70835 +/- 1.41421
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.39245 +/- 0.00728216
  return (TDataSet *)tableSet;// West = 0.475918 +/- 1.41421 East = 1.39245 +/- 0.00728216
};
