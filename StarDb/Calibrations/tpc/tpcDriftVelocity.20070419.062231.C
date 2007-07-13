TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 109026
  row.laserDriftVelocityEast	 =   5.57436; // +/- 1.53164e-05 cm/us All: East = 0.175762 +/- 0.00373586
  row.laserDriftVelocityWest	 =   5.57436; // +/- 1.53164e-05 cm/us All: West = -0.14244 +/- 0.00399993
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57436 +/- 1.53164e-05
  return (TDataSet *)tableSet;// West = 5.57532 +/- 2.25775e-05 East = 5.57353 +/- 2.08471e-05
};
