TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 168107
  row.laserDriftVelocityEast	 =   5.56836; // +/- 2.40008e-05 cm/us East: Slope = 1.11101 +/- 0.00426475 DV = 5.56836 +/- 2.40008e-05
  row.laserDriftVelocityWest	 =   5.57268; // +/- 3.57028e-05 cm/us West: Slope = 0.338825 +/- 0.00643307 DV = 5.57268 +/- 3.57028e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
