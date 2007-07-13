TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 113120
  row.laserDriftVelocityEast	 =   5.57746; // +/- 1.65768e-05 cm/us All: East = -0.53912 +/- 0.00406359
  row.laserDriftVelocityWest	 =   5.57746; // +/- 1.65768e-05 cm/us All: West = -0.50851 +/- 0.0043202
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57746 +/- 1.65768e-05
  return (TDataSet *)tableSet;// West = 5.57736 +/- 2.42036e-05 East = 5.57754 +/- 2.27501e-05
};
