TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 113064
  row.laserDriftVelocityEast	 =   5.57672; // +/- 1.61936e-05 cm/us All: East = -0.386717 +/- 0.00381993
  row.laserDriftVelocityWest	 =   5.57672; // +/- 1.61936e-05 cm/us All: West = -0.409494 +/- 0.00446383
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57672 +/- 1.61936e-05
  return (TDataSet *)tableSet;// West = 5.57682 +/- 2.48593e-05 East = 5.57666 +/- 2.13433e-05
};
