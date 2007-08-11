TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 110046
  row.laserDriftVelocityEast	 =   5.57189; // +/- 1.7699e-05 cm/us East: Slope = 0.477736 +/- 0.00318624 DV = 5.57189 +/- 1.7699e-05
  row.laserDriftVelocityWest	 =   5.57485; // +/- 1.83675e-05 cm/us West: Slope = -0.0582079 +/- 0.00329165 DV = 5.57485 +/- 1.83675e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
