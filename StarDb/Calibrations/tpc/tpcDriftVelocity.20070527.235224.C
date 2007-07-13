TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 147093
  row.laserDriftVelocityEast	 =   5.57489; // +/- 2.06899e-05 cm/us All: East = 0.0472767 +/- 0.0628114
  row.laserDriftVelocityWest	 =   5.57489; // +/- 2.06899e-05 cm/us All: West = -0.0648576 +/- 0.00368727
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57489 +/- 2.06899e-05
  return (TDataSet *)tableSet;// West = 5.57489 +/- 2.07327e-05 East = 5.57457 +/- 0.000322276
};
