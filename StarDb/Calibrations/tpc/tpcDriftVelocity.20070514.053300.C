TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 134012
  row.laserDriftVelocityEast	 =   5.57202; // +/- 2.61693e-05 cm/us All: East = 0.437283 +/- 0.00754282
  row.laserDriftVelocityWest	 =   5.57202; // +/- 2.61693e-05 cm/us All: West = 0.454508 +/- 0.00600562
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57202 +/- 2.61693e-05
  return (TDataSet *)tableSet;// West = 5.57198 +/- 3.34936e-05 East = 5.57207 +/- 4.19293e-05
};
