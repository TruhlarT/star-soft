TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 139074
  row.laserDriftVelocityEast	 =   5.57512; // +/- 1.95403e-05 cm/us All: East = -0.143604 +/- 0.00460735
  row.laserDriftVelocityWest	 =   5.57512; // +/- 1.95403e-05 cm/us All: West = -0.0543605 +/- 0.00548102
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57512 +/- 1.95403e-05
  return (TDataSet *)tableSet;// West = 5.57484 +/- 2.9761e-05 East = 5.57534 +/- 2.59066e-05
};
