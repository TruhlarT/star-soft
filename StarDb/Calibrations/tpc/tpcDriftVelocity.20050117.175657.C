TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6017059
  row.laserDriftVelocityEast	 =   5.54217; // +/- 8.59333e-05 cm/us All: East = 5.54282 +/- 0.000152856
  row.laserDriftVelocityWest	 =   5.54217; // +/- 8.59333e-05 cm/us All: West = 5.54187 +/- 0.000103908
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.08281 +/- 0.0163755
  return (TDataSet *)tableSet;// West = 1.15901 +/- 0.0201406 East = 0.934184 +/- 0.0281279
};
