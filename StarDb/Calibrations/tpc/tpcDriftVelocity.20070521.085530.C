TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 141028
  row.laserDriftVelocityEast	 =   5.57282; // +/- 1.47904e-05 cm/us East: Slope = 0.30302 +/- 0.00265371 DV = 5.57282 +/- 1.47904e-05
  row.laserDriftVelocityWest	 =   5.57501; // +/- 2.20998e-05 cm/us West: Slope = -0.0847388 +/- 0.00398251 DV = 5.57501 +/- 2.20998e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
