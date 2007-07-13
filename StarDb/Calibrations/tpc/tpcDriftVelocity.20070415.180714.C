TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 105064
  row.laserDriftVelocityEast	 =   5.5832; // +/- 1.29076e-05 cm/us All: East = -1.47505 +/- 0.00380292
  row.laserDriftVelocityWest	 =   5.5832; // +/- 1.29076e-05 cm/us All: West = -1.59699 +/- 0.00291588
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5832 +/- 1.29076e-05
  return (TDataSet *)tableSet;// West = 5.58345 +/- 1.62911e-05 East = 5.58279 +/- 2.1156e-05
};
