TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 174028
  row.laserDriftVelocityEast	 =   5.5715; // +/- 2.26104e-05 cm/us All: East = 0.709565 +/- 0.00600463
  row.laserDriftVelocityWest	 =   5.5715; // +/- 2.26104e-05 cm/us All: West = 0.390714 +/- 0.00550302
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.5715 +/- 2.26104e-05
  return (TDataSet *)tableSet;// West = 5.57236 +/- 3.09782e-05 East = 5.57052 +/- 3.30766e-05
};
