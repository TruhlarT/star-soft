TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6046021
  row.laserDriftVelocityEast	 =   5.52719; // +/- 3.81171e-05 cm/us All: East = 5.52652 +/- 8.7742e-05
  row.laserDriftVelocityWest	 =   5.52719; // +/- 3.81171e-05 cm/us All: West = 5.52734 +/- 4.2319e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.55539 +/- 0.00814159
  return (TDataSet *)tableSet;// West = 1.51671 +/- 0.00916279 East = 1.70046 +/- 0.0177461
};
