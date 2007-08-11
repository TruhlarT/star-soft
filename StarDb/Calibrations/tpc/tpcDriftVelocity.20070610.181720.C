TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 161064
  row.laserDriftVelocityEast	 =   5.56995; // +/- -1 cm/us East: Slope = 0.586787 +/- 1.41421 DV = 11.1458 +/- 1.41421
  row.laserDriftVelocityWest	 =   5.57322; // +/- 2.51849e-05 cm/us West: Slope = 0.23773 +/- 0.00453368 DV = 5.57322 +/- 2.51849e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
