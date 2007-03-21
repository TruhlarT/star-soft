TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6047041
  row.laserDriftVelocityEast	 =   5.52746; // +/- 8.08225e-05 cm/us All: East = 5.52892 +/- 0.000668818
  row.laserDriftVelocityWest	 =   5.52746; // +/- 8.08225e-05 cm/us All: West = 5.52744 +/- 8.14192e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.24425 +/- 0.015062
  return (TDataSet *)tableSet;// West = 1.24687 +/- 0.0151288 East = 0.949044 +/- 0.160494
};
