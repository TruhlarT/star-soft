TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 112031
  row.laserDriftVelocityEast	 =   5.57548; // +/- 1.61298e-05 cm/us All: East = -0.217709 +/- 0.00362309
  row.laserDriftVelocityWest	 =   5.57548; // +/- 1.61298e-05 cm/us All: West = -0.097812 +/- 0.00486782
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57548 +/- 1.61298e-05
  return (TDataSet *)tableSet;// West = 5.57508 +/- 2.70414e-05 East = 5.5757 +/- 2.00963e-05
};
