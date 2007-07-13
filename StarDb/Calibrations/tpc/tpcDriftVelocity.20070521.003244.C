TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 140063
  row.laserDriftVelocityEast	 =   5.57545; // +/- 2.5126e-05 cm/us All: East = -0.228177 +/- 0.00635521
  row.laserDriftVelocityWest	 =   5.57545; // +/- 2.5126e-05 cm/us All: West = -0.104602 +/- 0.00638297
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57545 +/- 2.5126e-05
  return (TDataSet *)tableSet;// West = 5.57511 +/- 3.55793e-05 East = 5.5758 +/- 3.5488e-05
};
