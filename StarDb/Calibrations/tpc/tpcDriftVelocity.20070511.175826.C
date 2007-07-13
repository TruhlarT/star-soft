TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 131056
  row.laserDriftVelocityEast	 =   5.56354; // +/- 2.0566e-05 cm/us All: East = 1.89479 +/- 0.00464823
  row.laserDriftVelocityWest	 =   5.56354; // +/- 2.0566e-05 cm/us All: West = 2.07358 +/- 0.00599067
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = 5.56354 +/- 2.0566e-05
  return (TDataSet *)tableSet;// West = 5.56298 +/- 3.34458e-05 East = 5.56388 +/- 2.6079e-05
};
