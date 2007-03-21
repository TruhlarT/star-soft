TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 6065040
  row.laserDriftVelocityEast	 =   5.54223; // +/- 0.000277695 cm/us All: East = 5.5455 +/- 0.000537759
  row.laserDriftVelocityWest	 =   5.54223; // +/- 0.000277695 cm/us All: West = 5.54104 +/- 0.000324277
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row);// 1e3*Delta: All = -0.0405889 +/- 0.0516828
  return (TDataSet *)tableSet;// West = 0.116626 +/- 0.0573147 East = -0.724676 +/- 0.119557
};
