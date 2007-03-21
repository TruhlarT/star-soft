TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6076028
  row.laserDriftVelocityEast	 =   5.52994; // +/- 0.000106928 cm/us All: East = 5.52967 +/- 0.000150351
  row.laserDriftVelocityWest	 =   5.52994; // +/- 0.000106928 cm/us All: West = 5.53021 +/- 0.000152101
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 0.386554 +/- 0.018914
  return (TDataSet *)tableSet;// West = 0.334014 +/- 0.0259241 East = 0.446353 +/- 0.0276568
};
