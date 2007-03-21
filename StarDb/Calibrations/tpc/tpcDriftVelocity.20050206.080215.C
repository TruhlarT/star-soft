TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6037012
  row.laserDriftVelocityEast	 =   5.53488; // +/- 4.29023e-05 cm/us All: East = 5.5346 +/- 9.54119e-05
  row.laserDriftVelocityWest	 =   5.53488; // +/- 4.29023e-05 cm/us All: West = 5.53495 +/- 4.80319e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 2.29871 +/- 0.00792856
  return (TDataSet *)tableSet;// West = 2.2911 +/- 0.00882431 East = 2.33061 +/- 0.0180608
};
