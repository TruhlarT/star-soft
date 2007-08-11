TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 128065
  row.laserDriftVelocityEast	 =   5.57546; // +/- 2.48816e-05 cm/us East: Slope = -0.163712 +/- 0.00445565 DV = 5.57546 +/- 2.48816e-05
  row.laserDriftVelocityWest	 =   5.57697; // +/- 2.89585e-05 cm/us West: Slope = -0.436245 +/- 0.00520045 DV = 5.57697 +/- 2.89585e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
