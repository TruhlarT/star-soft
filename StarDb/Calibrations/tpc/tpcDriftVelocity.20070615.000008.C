TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 165044
  row.laserDriftVelocityEast	 =   5.56712; // +/- 2.32481e-05 cm/us East: Slope = 1.32666 +/- 0.00417864 DV = 5.56712 +/- 2.32481e-05
  row.laserDriftVelocityWest	 =   5.5705; // +/- -1 cm/us West: Slope = 0 +/- 0 DV = 0 +/- 0
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
