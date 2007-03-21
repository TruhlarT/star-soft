TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6026099
  row.laserDriftVelocityEast	 =   5.55333; // +/- 9.35259e-05 cm/us All: East = 5.5522 +/- 0.000217759
  row.laserDriftVelocityWest	 =   5.55333; // +/- 9.35259e-05 cm/us All: West = 5.55358 +/- 0.000103564
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 2.35261 +/- 0.017158
  return (TDataSet *)tableSet;// West = 2.30187 +/- 0.0188787 East = 2.59348 +/- 0.0411348
};
