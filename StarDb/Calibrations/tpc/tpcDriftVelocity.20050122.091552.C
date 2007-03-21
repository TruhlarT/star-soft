TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6022008
  row.laserDriftVelocityEast	 =   5.55378; // +/- 3.10184e-05 cm/us All: East = 5.55409 +/- 5.54273e-05
  row.laserDriftVelocityWest	 =   5.55378; // +/- 3.10184e-05 cm/us All: West = 5.55364 +/- 3.7428e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 1.29874 +/- 0.00672604
  return (TDataSet *)tableSet;// West = 1.31873 +/- 0.00824449 East = 1.25895 +/- 0.0116307
};
