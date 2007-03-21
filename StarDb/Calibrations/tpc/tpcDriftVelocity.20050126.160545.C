TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6026063
  row.laserDriftVelocityEast	 =   5.55412; // +/- 8.73515e-05 cm/us All: East = 5.55309 +/- 0.000253986
  row.laserDriftVelocityWest	 =   5.55412; // +/- 8.73515e-05 cm/us All: West = 5.55426 +/- 9.30263e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = -15.83 +/- 0.0155218
  return (TDataSet *)tableSet;// West = -15.8545 +/- 0.0164947 East = -15.6401 +/- 0.0458741
};
