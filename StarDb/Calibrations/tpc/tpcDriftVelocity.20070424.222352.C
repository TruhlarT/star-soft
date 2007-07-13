TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 114093
  row.laserDriftVelocityEast	 =   5.5779; // +/- 1.6939e-05 cm/us All: East = -0.623573 +/- 0.00415287
  row.laserDriftVelocityWest	 =   5.5779; // +/- 1.6939e-05 cm/us All: West = -0.572982 +/- 0.00435417
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5779 +/- 1.6939e-05
  return (TDataSet *)tableSet;// West = 5.57772 +/- 2.44368e-05 East = 5.57806 +/- 2.35013e-05
};
