TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 162009
  row.laserDriftVelocityEast	 =   5.5698; // +/- -1 cm/us East: Slope = 0.595032 +/- 0.00931598 DV = 5.57122 +/- 5.18947e-05
  row.laserDriftVelocityWest	 =   5.57308; // +/- 2.1689e-05 cm/us West: Slope = 0.2614 +/- 0.00389201 DV = 5.57308 +/- 2.1689e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
