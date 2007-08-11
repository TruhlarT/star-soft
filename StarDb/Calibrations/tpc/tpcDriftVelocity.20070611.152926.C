TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 162038
  row.laserDriftVelocityEast	 =   5.57011; // +/- -1 cm/us East: Slope = 0.464664 +/- 0.00844189 DV = 5.57193 +/- 4.68991e-05
  row.laserDriftVelocityWest	 =   5.5734; // +/- 2.47566e-05 cm/us West: Slope = 0.202901 +/- 0.00444994 DV = 5.5734 +/- 2.47566e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
