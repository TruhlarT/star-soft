TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 162049
  row.laserDriftVelocityEast	 =   5.57045; // +/- -1 cm/us East: Slope = 0.49579 +/- 0.0108619 DV = 5.57179 +/- 6.15418e-05
  row.laserDriftVelocityWest	 =   5.57375; // +/- 2.30262e-05 cm/us West: Slope = 0.141165 +/- 0.00412645 DV = 5.57375 +/- 2.30262e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
