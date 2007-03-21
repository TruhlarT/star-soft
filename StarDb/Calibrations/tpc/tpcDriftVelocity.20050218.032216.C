TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6048078
  row.laserDriftVelocityEast	 =   5.52986; // +/- 9.70833e-05 cm/us All: East = 5.52985 +/- 0.000227206
  row.laserDriftVelocityWest	 =   5.52986; // +/- 9.70833e-05 cm/us All: West = 5.52986 +/- 0.000107379
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.0797 +/- 0.0177469
  return (TDataSet *)tableSet;// West = 1.06602 +/- 0.0199101 East = 1.13262 +/- 0.0391496
};
