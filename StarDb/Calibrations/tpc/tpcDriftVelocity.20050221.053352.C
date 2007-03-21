TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6052002
  row.laserDriftVelocityEast	 =   5.53392; // +/- 6.0017e-05 cm/us All: East = 5.53371 +/- 0.000103911
  row.laserDriftVelocityWest	 =   5.53392; // +/- 6.0017e-05 cm/us All: West = 5.53403 +/- 7.35201e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.21856 +/- 0.0109118
  return (TDataSet *)tableSet;// West = 1.18867 +/- 0.0132268 East = 1.28226 +/- 0.0193073
};
