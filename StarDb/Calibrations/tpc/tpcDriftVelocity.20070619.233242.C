TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 170083
  row.laserDriftVelocityEast	 =   5.57047; // +/- 2.08306e-05 cm/us All: East = 0.96038 +/- 0.0053417
  row.laserDriftVelocityWest	 =   5.57047; // +/- 2.08306e-05 cm/us All: West = 0.519916 +/- 0.00516873
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57047 +/- 2.08306e-05
  return (TDataSet *)tableSet;// West = 5.57164 +/- 2.87371e-05 East = 5.56919 +/- 3.02381e-05
};
