TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 159076
  row.laserDriftVelocityEast	 =   5.57397; // +/- 1.99948e-05 cm/us All: East = 0.181794 +/- 0.00552696
  row.laserDriftVelocityWest	 =   5.57397; // +/- 1.99948e-05 cm/us All: West = 0.0347737 +/- 0.00470905
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57397 +/- 1.99948e-05
  return (TDataSet *)tableSet;// West = 5.57433 +/- 2.64188e-05 East = 5.57349 +/- 3.05919e-05
};
