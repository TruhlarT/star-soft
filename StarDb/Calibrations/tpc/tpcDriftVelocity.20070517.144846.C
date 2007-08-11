TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 137035
  row.laserDriftVelocityEast	 =   5.57433; // +/- 1.93681e-05 cm/us East: Slope = -17.7924 +/- 0.00339895 DV = 5.57433 +/- 1.93681e-05
  row.laserDriftVelocityWest	 =   5.57698; // +/- -1 cm/us West: Slope = -17.9721 +/- 0.00720101 DV = 5.57535 +/- 4.20261e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
