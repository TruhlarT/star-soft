TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 163044
  row.laserDriftVelocityEast	 =   5.57441; // +/- 4.23498e-05 cm/us All: East = -17.6821 +/- 0.0154299
  row.laserDriftVelocityWest	 =   5.57441; // +/- 4.23498e-05 cm/us All: West = -17.8451 +/- 0.00880253
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57441 +/- 4.23498e-05
  return (TDataSet *)tableSet;// West = 5.57464 +/- 4.91037e-05 East = 5.57373 +/- 8.36734e-05
};
