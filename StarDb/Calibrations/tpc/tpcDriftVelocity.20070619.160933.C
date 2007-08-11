TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 170047
  row.laserDriftVelocityEast	 =   5.56678; // +/- 1.96226e-05 cm/us East: Slope = 1.39006 +/- 0.00349004 DV = 5.56678 +/- 1.96226e-05
  row.laserDriftVelocityWest	 =   5.5709; // +/- 2.22703e-05 cm/us West: Slope = 0.651883 +/- 0.00398525 DV = 5.5709 +/- 2.22703e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
