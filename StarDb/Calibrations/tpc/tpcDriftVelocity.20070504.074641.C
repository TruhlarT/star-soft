TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 124011
  row.laserDriftVelocityEast	 =   5.57929; // +/- 1.9247e-05 cm/us All: East = -0.886298 +/- 0.00392874
  row.laserDriftVelocityWest	 =   5.57929; // +/- 1.9247e-05 cm/us All: West = -0.746911 +/- 0.00703626
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57929 +/- 1.9247e-05
  return (TDataSet *)tableSet;// West = 5.57868 +/- 3.97105e-05 East = 5.57947 +/- 2.20044e-05
};
