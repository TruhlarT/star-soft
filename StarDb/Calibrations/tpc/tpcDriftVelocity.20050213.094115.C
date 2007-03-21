TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6044023
  row.laserDriftVelocityEast	 =   5.52825; // +/- 3.62804e-05 cm/us All: East = 5.52804 +/- 7.83555e-05
  row.laserDriftVelocityWest	 =   5.52825; // +/- 3.62804e-05 cm/us All: West = 5.5283 +/- 4.09326e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.26531 +/- 0.00665565
  return (TDataSet *)tableSet;// West = 1.25716 +/- 0.0075184 East = 1.29483 +/- 0.0143096
};
