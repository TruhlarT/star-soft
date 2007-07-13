TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 111089
  row.laserDriftVelocityEast	 =   5.5754; // +/- 1.58317e-05 cm/us All: East = -0.114444 +/- 0.00384298
  row.laserDriftVelocityWest	 =   5.5754; // +/- 1.58317e-05 cm/us All: West = -0.207564 +/- 0.00420075
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5754 +/- 1.58317e-05
  return (TDataSet *)tableSet;// West = 5.57568 +/- 2.33572e-05 East = 5.57516 +/- 2.15327e-05
};
