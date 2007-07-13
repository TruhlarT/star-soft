TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 134018
  row.laserDriftVelocityEast	 =   5.57268; // +/- 2.5282e-05 cm/us All: East = 0.107625 +/- 0.00795067
  row.laserDriftVelocityWest	 =   5.57268; // +/- 2.5282e-05 cm/us All: West = 0.440252 +/- 0.0054684
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57268 +/- 2.5282e-05
  return (TDataSet *)tableSet;// West = 5.57206 +/- 3.07465e-05 East = 5.57396 +/- 4.4425e-05
};
