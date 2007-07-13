TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 118018
  row.laserDriftVelocityEast	 =   5.57741; // +/- 1.9357e-05 cm/us All: East = -0.58903 +/- 0.00496522
  row.laserDriftVelocityWest	 =   5.57741; // +/- 1.9357e-05 cm/us All: West = -0.446405 +/- 0.00486018
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57741 +/- 1.9357e-05
  return (TDataSet *)tableSet;// West = 5.57702 +/- 2.70116e-05 East = 5.57783 +/- 2.77533e-05
};
