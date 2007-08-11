TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 137025
  row.laserDriftVelocityEast	 =   5.57308; // +/- 2.05281e-05 cm/us East: Slope = 0.261293 +/- 0.00369083 DV = 5.57308 +/- 2.05281e-05
  row.laserDriftVelocityWest	 =   5.57471; // +/- 3.36136e-05 cm/us West: Slope = -0.0303858 +/- 0.00597045 DV = 5.57471 +/- 3.36136e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
