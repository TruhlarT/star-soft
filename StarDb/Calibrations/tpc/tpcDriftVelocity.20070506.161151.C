TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 126050
  row.laserDriftVelocityEast	 =   5.57668; // +/- 2.33407e-05 cm/us All: East = -0.380599 +/- 0.00466494
  row.laserDriftVelocityWest	 =   5.57668; // +/- 2.33407e-05 cm/us All: West = -0.427305 +/- 0.00946244
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57668 +/- 2.33407e-05
  return (TDataSet *)tableSet;// West = 5.57696 +/- 5.22133e-05 East = 5.57662 +/- 2.6093e-05
};
