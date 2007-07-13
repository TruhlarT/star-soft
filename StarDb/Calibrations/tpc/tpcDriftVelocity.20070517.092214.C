TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 137019
  row.laserDriftVelocityEast	 =   5.57511; // +/- 2.59249e-05 cm/us All: East = -0.114602 +/- 0.00530906
  row.laserDriftVelocityWest	 =   5.57511; // +/- 2.59249e-05 cm/us All: West = -0.0784863 +/- 0.00951391
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57511 +/- 2.59249e-05
  return (TDataSet *)tableSet;// West = 5.57498 +/- 5.30084e-05 East = 5.57515 +/- 2.9722e-05
};
