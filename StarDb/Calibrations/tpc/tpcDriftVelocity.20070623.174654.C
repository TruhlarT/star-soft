TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 174057
  row.laserDriftVelocityEast	 =   5.57194; // +/- 2.16572e-05 cm/us All: East = 0.589372 +/- 0.00541198
  row.laserDriftVelocityWest	 =   5.57194; // +/- 2.16572e-05 cm/us All: West = 0.343488 +/- 0.00555754
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57194 +/- 2.16572e-05
  return (TDataSet *)tableSet;// West = 5.57263 +/- 3.0914e-05 East = 5.57128 +/- 3.03497e-05
};
