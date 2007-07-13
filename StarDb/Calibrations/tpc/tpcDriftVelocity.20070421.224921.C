TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 111090
  row.laserDriftVelocityEast	 =   5.57545; // +/- 1.54585e-05 cm/us All: East = -0.13798 +/- 0.00361237
  row.laserDriftVelocityWest	 =   5.57545; // +/- 1.54585e-05 cm/us All: West = -0.205291 +/- 0.00437208
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57545 +/- 1.54585e-05
  return (TDataSet *)tableSet;// West = 5.57567 +/- 2.42832e-05 East = 5.5753 +/- 2.00447e-05
};
