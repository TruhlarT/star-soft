TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 166034
  row.laserDriftVelocityEast	 =   5.56907; // +/- 2.80153e-05 cm/us All: East = 0.978234 +/- 0.00505335
  row.laserDriftVelocityWest	 =   5.56907; // +/- 2.80153e-05 cm/us All: West = 0 +/- 0
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.56907 +/- 2.80153e-05
  return (TDataSet *)tableSet;// West = 0 +/- 0 East = 5.56907 +/- 2.80153e-05
};
