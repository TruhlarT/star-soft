TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 177057
  row.laserDriftVelocityEast	 =   5.56661; // +/- 2.72196e-05 cm/us East: Slope = 1.42555 +/- 0.00493056 DV = 5.56661 +/- 2.72196e-05
  row.laserDriftVelocityWest	 =   5.57103; // +/- 2.15406e-05 cm/us West: Slope = 0.627665 +/- 0.00388722 DV = 5.57103 +/- 2.15406e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
