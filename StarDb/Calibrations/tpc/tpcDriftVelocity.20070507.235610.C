TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 127077
  row.laserDriftVelocityEast	 =   5.5749; // +/- 2.49706e-05 cm/us East: Slope = -0.0669394 +/- 0.0045011 DV = 5.5749 +/- 2.49706e-05
  row.laserDriftVelocityWest	 =   5.57602; // +/- 3.22191e-05 cm/us West: Slope = -0.270832 +/- 0.00572686 DV = 5.57602 +/- 3.22191e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
