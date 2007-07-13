TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 177057
  row.laserDriftVelocityEast	 =   5.56814; // +/- 3.53713e-05 cm/us All: East = 1.15219 +/- 0.00630668
  row.laserDriftVelocityWest	 =   5.56814; // +/- 3.53713e-05 cm/us All: West = 0 +/- 0
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.56814 +/- 3.53713e-05
  return (TDataSet *)tableSet;// West = 0 +/- 0 East = 5.56814 +/- 3.53713e-05
};
