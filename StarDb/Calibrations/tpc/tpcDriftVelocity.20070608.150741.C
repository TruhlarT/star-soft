TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 159029
  row.laserDriftVelocityEast	 =   5.57383; // +/- 2.19851e-05 cm/us All: East = 0.326421 +/- 0.0229358
  row.laserDriftVelocityWest	 =   5.57383; // +/- 2.19851e-05 cm/us All: West = 0.116224 +/- 0.00400973
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57383 +/- 2.19851e-05
  return (TDataSet *)tableSet;// West = 5.57386 +/- 2.23129e-05 East = 5.57292 +/- 0.000128726
};
