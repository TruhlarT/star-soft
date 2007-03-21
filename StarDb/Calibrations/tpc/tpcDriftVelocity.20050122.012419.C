TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6021046
  row.laserDriftVelocityEast	 =   5.5529; // +/- 7.21724e-05 cm/us All: East = 5.55225 +/- 0.000148792
  row.laserDriftVelocityWest	 =   5.5529; // +/- 7.21724e-05 cm/us All: West = 5.5531 +/- 8.25314e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = -1.95661 +/- 0.0193339
  return (TDataSet *)tableSet;// West = -2.00907 +/- 0.021598 East = -1.74501 +/- 0.0433768
};
