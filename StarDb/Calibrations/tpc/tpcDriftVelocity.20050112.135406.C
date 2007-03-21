TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6012035
  row.laserDriftVelocityEast	 =   5.51455; // +/- 0.000102274 cm/us All: East = 5.51199 +/- 0.000363318
  row.laserDriftVelocityWest	 =   5.51455; // +/- 0.000102274 cm/us All: West = 5.51477 +/- 0.000106584
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = -16.7005 +/- 0.0182802
  return (TDataSet *)tableSet;// West = -16.7387 +/- 0.0190293 East = -16.2446 +/- 0.0657971
};
