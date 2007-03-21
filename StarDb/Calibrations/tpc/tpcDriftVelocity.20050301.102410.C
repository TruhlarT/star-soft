TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6060015
  row.laserDriftVelocityEast	 =   5.53725; // +/- 7.19026e-05 cm/us All: East = 5.53955 +/- 0.000150313
  row.laserDriftVelocityWest	 =   5.53725; // +/- 7.19026e-05 cm/us All: West = 5.53657 +/- 8.18781e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.45534 +/- 0.0129628
  return (TDataSet *)tableSet;// West = 1.57953 +/- 0.0147428 East = 1.0322 +/- 0.0272142
};
