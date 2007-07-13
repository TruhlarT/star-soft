TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 144022
  row.laserDriftVelocityEast	 =   5.57368; // +/- 1.62851e-05 cm/us All: East = -0.216421 +/- 5.54599
  row.laserDriftVelocityWest	 =   5.57368; // +/- 1.62851e-05 cm/us All: West = 0.152677 +/- 0.00291697
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57368 +/- 1.62851e-05
  return (TDataSet *)tableSet;// West = 5.57368 +/- 1.62851e-05 East = 5.57575 +/- 0.0309669
};
