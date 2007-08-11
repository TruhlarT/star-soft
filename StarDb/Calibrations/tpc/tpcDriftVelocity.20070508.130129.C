TDataSet *CreateTable() {
  if (!gROOT->GetClass("St_tpcDriftVelocity")) return 0;
  St_tpcDriftVelocity *tableSet = new St_tpcDriftVelocity("tpcDriftVelocity",1);
  tpcDriftVelocity_st row;// Laser Run 128040
  row.laserDriftVelocityEast	 =   5.57398; // +/- 1.36852e-05 cm/us East: Slope = 0.103938 +/- 0.00245418 DV = 5.57398 +/- 1.36852e-05
  row.laserDriftVelocityWest	 =   5.5765; // +/- 2.33439e-05 cm/us West: Slope = -0.352172 +/- 0.00420382 DV = 5.5765 +/- 2.33439e-05
  row.cathodeDriftVelocityEast	 =          0; // cm/us : from cathode emission  ;
  row.cathodeDriftVelocityWest	 =          0; // cm/us : from cathode emission  ;
  tableSet->AddAt(&row); 
  return (TDataSet *)tableSet;
};
