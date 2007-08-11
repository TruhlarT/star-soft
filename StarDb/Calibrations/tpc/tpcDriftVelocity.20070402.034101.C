TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 91135
  row.laserDriftVelocityEast	 =   5.58167; // +/- 2.02704e-05 cm/us East: Slope = -2.58989 +/- 0.00365942 DV = 5.58167 +/- 2.02704e-05
  row.laserDriftVelocityWest	 =   5.58343; // +/- 2.61811e-05 cm/us West: Slope = -2.90065 +/- 0.00466246 DV = 5.58343 +/- 2.61811e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
