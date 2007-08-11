TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 87013
  row.laserDriftVelocityEast	 =   5.57314; // +/- 2.97268e-05 cm/us East: Slope = -1.0666 +/- 0.00539836 DV = 5.57314 +/- 2.97268e-05
  row.laserDriftVelocityWest	 =   5.5745; // +/- -1 cm/us West: Slope = -1.64299 +/- 0.00798202 DV = 5.57641 +/- 4.49713e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
