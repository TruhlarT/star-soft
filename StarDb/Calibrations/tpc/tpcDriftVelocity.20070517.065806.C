TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 137010
  row.laserDriftVelocityEast	 =   5.57337; // +/- 2.50808e-05 cm/us East: Slope = 0.202109 +/- 0.00453671 DV = 5.57337 +/- 2.50808e-05
  row.laserDriftVelocityWest	 =   5.575; // +/- 3.26357e-05 cm/us West: Slope = -0.0880702 +/- 0.0058793 DV = 5.575 +/- 3.26357e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
