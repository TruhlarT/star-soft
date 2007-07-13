TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 173087
  row.laserDriftVelocityEast	 =   5.57154; // +/- 2.06882e-05 cm/us All: East = 0.727414 +/- 0.00532053
  row.laserDriftVelocityWest	 =   5.57154; // +/- 2.06882e-05 cm/us All: West = 0.354545 +/- 0.00519348
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57154 +/- 2.06882e-05
  return (TDataSet *)tableSet;// West = 5.57255 +/- 2.89974e-05 East = 5.57049 +/- 2.95249e-05
};
