TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 102110
  row.laserDriftVelocityEast	 =   5.57507; // +/- 5.80208e-06 cm/us All: East = -0.0789907 +/- 0.00130884
  row.laserDriftVelocityWest	 =   5.57507; // +/- 5.80208e-06 cm/us All: West = -0.13152 +/- 0.00171457
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.57507 +/- 5.80208e-06
  return (TDataSet *)tableSet;// West = 5.57526 +/- 9.5583e-06 East = 5.57496 +/- 7.30108e-06
};
