TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 156111
  row.laserDriftVelocityEast	 =   5.57362; // +/- 2.81238e-05 cm/us All: East = 0 +/- 0
  row.laserDriftVelocityWest	 =   5.57362; // +/- 2.81238e-05 cm/us All: West = 0.15987 +/- 0.00504195
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57362 +/- 2.81238e-05
  return (TDataSet *)tableSet;// West = 5.57362 +/- 2.81238e-05 East = 0 +/- 0
};
