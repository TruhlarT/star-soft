TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 112066
  row.laserDriftVelocityEast	 =   5.57443; // +/- 2.7282e-05 cm/us East: Slope = 0.0217277 +/- 0.00501335 DV = 5.57443 +/- 2.7282e-05
  row.laserDriftVelocityWest	 =   5.57577; // +/- 2.29502e-05 cm/us West: Slope = -0.222736 +/- 0.00419521 DV = 5.57577 +/- 2.29502e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
