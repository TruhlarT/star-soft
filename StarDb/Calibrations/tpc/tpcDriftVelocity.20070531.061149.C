TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 151012
  row.laserDriftVelocityEast	 =   5.57292; // +/- 2.26287e-05 cm/us All: East = 0.310762 +/- 1.41421
  row.laserDriftVelocityWest	 =   5.57292; // +/- 2.26287e-05 cm/us All: West = 0.290885 +/- 0.00406459
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57292 +/- 2.26287e-05
  return (TDataSet *)tableSet;// West = 5.57292 +/- 2.26287e-05 East = 4.45792 +/- 1.41421
};
