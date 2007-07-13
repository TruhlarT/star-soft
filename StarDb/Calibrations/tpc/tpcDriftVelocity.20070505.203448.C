TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 125094
  row.laserDriftVelocityEast	 =   5.57894; // +/- 2.50759e-05 cm/us All: East = -0.755176 +/- 0.00606593
  row.laserDriftVelocityWest	 =   5.57894; // +/- 2.50759e-05 cm/us All: West = -0.839576 +/- 0.00645163
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57894 +/- 2.50759e-05
  return (TDataSet *)tableSet;// West = 5.5792 +/- 3.63842e-05 East = 5.57871 +/- 3.46077e-05
};
