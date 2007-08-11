TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 140016
  row.laserDriftVelocityEast	 =   5.5734; // +/- 2.64051e-05 cm/us East: Slope = 0.202503 +/- 0.00477773 DV = 5.5734 +/- 2.64051e-05
  row.laserDriftVelocityWest	 =   5.57612; // +/- -1 cm/us West: Slope = -0.0997439 +/- 0.00790658 DV = 5.57513 +/- 4.4734e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
