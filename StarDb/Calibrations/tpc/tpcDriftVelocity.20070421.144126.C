TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 111067
  row.laserDriftVelocityEast	 =   5.57283; // +/- 2.12229e-05 cm/us East: Slope = 0.305587 +/- 0.00379066 DV = 5.57283 +/- 2.12229e-05
  row.laserDriftVelocityWest	 =   5.57416; // +/- 2.62509e-05 cm/us West: Slope = 0.0641085 +/- 0.00469613 DV = 5.57416 +/- 2.62509e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
