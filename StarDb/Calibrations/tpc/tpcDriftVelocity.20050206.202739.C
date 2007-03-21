TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6037051
  row.laserDriftVelocityEast	 =   5.53423; // +/- 9.49705e-05 cm/us All: East = 5.53452 +/- 0.000248816
  row.laserDriftVelocityWest	 =   5.53423; // +/- 9.49705e-05 cm/us All: West = 5.53418 +/- 0.00010275
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 2.22481 +/- 0.0167171
  return (TDataSet *)tableSet;// West = 2.23798 +/- 0.0178838 East = 2.13364 +/- 0.0470542
};
