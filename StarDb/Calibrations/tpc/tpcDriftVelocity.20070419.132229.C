TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 109057
  row.laserDriftVelocityEast	 =   5.57427; // +/- 1.40567e-05 cm/us All: East = 0.225065 +/- 0.00374905
  row.laserDriftVelocityWest	 =   5.57427; // +/- 1.40567e-05 cm/us All: West = -0.106466 +/- 0.00342045
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57427 +/- 1.40567e-05
  return (TDataSet *)tableSet;// West = 5.57512 +/- 1.90687e-05 East = 5.57326 +/- 2.08028e-05
};
