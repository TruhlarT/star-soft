TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 145003
  row.laserDriftVelocityEast	 =   5.57097; // +/- -1 cm/us East: Slope = 0.456133 +/- 0.114756 DV = 5.57239 +/- 0.000594099
  row.laserDriftVelocityWest	 =   5.57381; // +/- 2.11719e-05 cm/us West: Slope = 0.132001 +/- 0.00379983 DV = 5.57381 +/- 2.11719e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
