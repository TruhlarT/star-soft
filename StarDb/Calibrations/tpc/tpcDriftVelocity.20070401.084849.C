TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 91024
  row.laserDriftVelocityEast	 =   5.58138; // +/- -1 cm/us East: Slope = 0 +/- 0 DV = 0 +/- 0
  row.laserDriftVelocityWest	 =   5.58285; // +/- 2.02927e-05 cm/us West: Slope = -2.79632 +/- 0.00365531 DV = 5.58285 +/- 2.02927e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
