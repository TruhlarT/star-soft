TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 96004
  row.laserDriftVelocityEast	 =   5.5769; // +/- 1.19712e-05 cm/us All: East = -1.71455 +/- 0.00248254
  row.laserDriftVelocityWest	 =   5.5769; // +/- 1.19712e-05 cm/us All: West = -1.77868 +/- 0.00416441
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5769 +/- 1.19712e-05
  return (TDataSet *)tableSet;// West = 5.57717 +/- 2.30388e-05 East = 5.5768 +/- 1.40112e-05
};
