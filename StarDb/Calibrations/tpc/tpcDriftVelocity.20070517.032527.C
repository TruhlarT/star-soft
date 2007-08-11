TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 136094
  row.laserDriftVelocityEast	 =   5.57322; // +/- 2.14001e-05 cm/us East: Slope = 0.236032 +/- 0.00382752 DV = 5.57322 +/- 2.14001e-05
  row.laserDriftVelocityWest	 =   5.57586; // +/- -1 cm/us West: Slope = -0.223181 +/- 0.00777146 DV = 5.5758 +/- 4.2915e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
