TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 91135
  row.laserDriftVelocityEast	 =   5.5836; // +/- 1.60343e-05 cm/us All: East = -2.95315 +/- 0.0036308
  row.laserDriftVelocityWest	 =   5.5836; // +/- 1.60343e-05 cm/us All: West = -2.89886 +/- 0.00471942
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5836 +/- 1.60343e-05
  return (TDataSet *)tableSet;// West = 5.58343 +/- 2.62613e-05 East = 5.5837 +/- 2.02463e-05
};
