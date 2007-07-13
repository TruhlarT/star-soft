TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 138002
  row.laserDriftVelocityEast	 =   5.57472; // +/- 1.91257e-05 cm/us All: East = -0.0579527 +/- 0.00412439
  row.laserDriftVelocityWest	 =   5.57472; // +/- 1.91257e-05 cm/us All: West = 0.0347875 +/- 0.00646839
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57472 +/- 1.91257e-05
  return (TDataSet *)tableSet;// West = 5.57436 +/- 3.60678e-05 East = 5.57487 +/- 2.25584e-05
};
